//engine.cpp - lmm

//bgm engine


#include<cmath>
#include <cholesky.hpp>  
#include <stochastic_term.h>
#include <normals.h>
#include "engine.h"
#include "dsct_factor.h"

std::vector<double> TheEngine::drifts(const std::vector<double>& times, const std::vector<double>& fwd_rtes, size_t p) {
	//take from hunter,jaeckel, joshi, 2001, drift approximations in a fwd_rte_bsd LIBOR mkt model

	std::vector<double> drifts(fwd_rtes.size());

	std::vector<double> tau(times.size() - 1);
	for (size_t i(0); i < fwd_rtes.size() - 1; ++i)	tau[i] = times[i + 1] - times[i];
	
	for (size_t k(0); k < drifts.size(); ++k){

		double tmp(0.0);
	
		if (k < p){
			for (size_t j(k+1); j < p; ++j)
				tmp -= (cov(k,j) * tau[j] * fwd_rtes[j]) / (1.0 + tau[j] * fwd_rtes[j]);
			
		}else if (k > p){
			for (size_t j(p); j <= k; ++j)
				tmp += (cov(k,j) * tau[j] * fwd_rtes[j]) / (1.0 + tau[j] * fwd_rtes[j]);
		}

		drifts[k] = tmp;
	}

	return drifts;
}

//constructor
TheEngine::TheEngine(shared_ptr<BGMProducts>& the_product_,
					FwdVolStructure& term_structure,
					shared_ptr<RandomBase>& the_generator_,
					const std::vector<double>& fwd_rtes_,
					const std::vector<double>& times_,
					double sub_stepping_,
					unsigned int numeraire_,
					double initial_numeraire_)
	:the_product(the_product_), the_generator(the_generator_), times(times_), sub_stepping(sub_stepping_), numeraire(numeraire_), initial_numeraire(initial_numeraire_), M(fwd_rtes_.size())
{
	//matrix - m rates, n times. m x n mat 
	fwd_rtes.resize(M, std::vector<double>(the_product->GetEvolutionTimes().size()+1));
	
	for (size_t i(0); i <fwd_rtes.size(); ++i)	fwd_rtes[i][0] = fwd_rtes_[i];
	
	//compute covariance matrix	
	cov.resize(M, M); //resize cov mat

	std::vector<double> K(cov.size1(), 1.0); //K = 1

	term_structure.covariance(cov, K, times, 0, sub_stepping);

	//precompute  pseudo_square root of cov-var using Cholesky decomposition 
	A = zero_matrix<double>(cov.size1(), cov.size2());
	size_t res = cholesky_decompose(cov, A);
	if (res != 0)
		throw("cholesky decomposition fails ");

	//precompute initial drift
	mu = drifts(times, fwd_rtes_, numeraire);

}

matrix<double> TheEngine::getCovariance() const { return cov; }

void TheEngine::setCovariance(const matrix<double> & cov_) { cov = cov_; }

void TheEngine::setNumeraire(unsigned int numeraire_, double initial_numeraire_){
	numeraire = numeraire_, initial_numeraire = initial_numeraire_;

	std::vector<double> _fwd_rtes(fwd_rtes.size());
	for (size_t j(0); j < fwd_rtes.size(); ++j)	_fwd_rtes[j] = fwd_rtes[j][0];

	mu = drifts(times, _fwd_rtes, numeraire);

}

void  TheEngine::GetOnePath(std::vector<std::vector<double>>& fwd_rtes, MJArray& z, method m){
	//Generate log of fwd rate, yt = log(ft)
	//correlated normal distr. of perturbations
	//plain mc. no acceleration technique.

	//substepping
	//unsigned int p((unsigned long) (the_product->GetEvolutionTimes()[0] / sub_stepping)); //assume time interval equally spaced
	
	unsigned int p(the_product->GetEvolutionTimes().size() / sub_stepping);
	
	

	for (size_t i(0); i < the_product->GetEvolutionTimes().size(); ++i){
		//log-Euler scheme
		// taken from hunter, jaeckel, joshi, 2001, drift approx. in a fwd-rte bsd libor mkt model

		for (size_t j(0); j < fwd_rtes.size(); ++j){

			double tmp(fwd_rtes[j][i]);

			for (size_t k(0); k < p; ++k){//sub stepping
				the_generator->GetGaussians(z);
				tmp *= exp(mu[j] - .5 * cov(j, j) + StochasticTerm(A, j, z));
			}

			fwd_rtes[j][i + 1] = tmp;
		}
		
		if (m == PC){
			//predictor-corrector method
			//two steps 1)prediction, 2) correction
			//fwd rte prediction  step, use Euler results

			the_generator->GetGaussians(z);

			//assign rates time i to vector
			std::vector<double> _fwd_rtes(fwd_rtes.size());
			for (size_t j(0); j < fwd_rtes.size(); ++j)	_fwd_rtes[j] = fwd_rtes[j][i+1];

			std::vector<double> mu_t = drifts(times, _fwd_rtes, numeraire);

			for (size_t j(0); j < fwd_rtes.size(); ++j)
				fwd_rtes[j][i + 1] = fwd_rtes[j][i] * exp(.5*(mu[j] + mu_t[j] - cov(j, j)) + StochasticTerm(A, j, z));
		}
	}
}

double  TheEngine::DoOnePath(const std::vector<std::vector<double>>& fwd_rtes) {

	double payoff(0.0);

	cashflows.clear();

	cashflows.resize(0);

	//assign final rates to vector
	std::vector<double> _fwd_rtes(fwd_rtes.size());

	for (size_t i(0); i < the_product->GetEvolutionTimes().size(); ++i){

		//assign rates time i to vector
		for (size_t j(0); j < fwd_rtes.size(); ++j)	_fwd_rtes[j] = fwd_rtes[j][i+1];

		//bool tmp = the_product->DoNextStep(_fwd_rtes, cashflows); //if true, terminates computation 
			
		if (the_product->DoNextStep(_fwd_rtes, cashflows)){
			the_product->reset();
			break;
		}	
		
	}

	//compute ratio of payoff to numéraire
	
	if (!(cashflows.size() >=1))	payoff = cashflows[0].amount;
	else{
		for (size_t i(0); i < cashflows.size(); ++i)
			payoff += cashflows[i].amount * dsct_factor(_fwd_rtes, times, 0, i);
	}

	return payoff / dsct_factor(_fwd_rtes, times, 0, numeraire);

}

double TheEngine::DoSimulation(unsigned int number_paths, method m){

	//value of simulation	
	double sum(0.0);

	MJArray z(M);

	for (size_t i(0); i < number_paths; ++i){
		this->GetOnePath(fwd_rtes, z, m);
		sum += this->DoOnePath(fwd_rtes);
	}

	the_generator->Reset();

	return initial_numeraire * sum / number_paths;
}
