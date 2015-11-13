//path_generation_mutli.cpp

#include <path_generation_multi.h>
#include <cholesky.hpp>
#include <cmath>

#include <stochastic_term.h>

using namespace std;

PathGenerationMulti::PathGenerationMulti(shared_ptr<RandomBase>& TheGenerator_,
										const MJArray& Spot0_,
										double T_,
										const MJArray& r0_,
										unsigned long steps_,
										matrix<double> cov_)
	:PathGeneration(TheGenerator_, 0.0, T_, steps_), Spot0(Spot0_), r(r0_), cov(cov_)
{
	SetSteps(steps_);
}

void PathGenerationMulti::SetSteps(unsigned long steps_){

	PathGeneration::SetSteps(steps_);

	TheGenerator->ResetDimensionality(GetSize());

	double deltaT(T / steps);

	matrix<double> cov1 = zero_matrix<double>(cov.size1(), cov.size2());
	
	for (size_t i(0); i < cov.size1(); ++i)
		for (size_t j(0); j < cov.size2(); ++j)
			cov1(i, j) = cov(i, j) * deltaT;
	
	drift.resize(Spot0.size());

	for (size_t i(0); i < drift.size(); ++i)
		drift[i] = (r[i] - .5 * cov(i, i)) * deltaT;

	A = zero_matrix<double>(cov.size1(), cov.size2());
	size_t res = cholesky_decompose(cov1, A);
	if (res != 0)
		throw("cholesky decomposition fails ");


}

double PathGenerationMulti::GetOnePath(args& args_) const {
	cout << "derived class PayOffMulti : use GetOnePathMulti() instead" << endl;

	return 0.0;
}

MJArray PathGenerationMulti::GetWholePath(args& args_) {
	cout << "derived class PayOffMulti : use GetWholePathMulti() instead" << endl;

	return MJArray(0);
}


MJArray PathGenerationMulti::GetOnePathMulti(args& args_) const
{
	MJArray stocks_path(Spot0.size());

	stocks_path = Spot0.apply(std::log);

	for (size_t i(0); i < steps; ++i)
		TheGenerator->GetGaussians(args_[i]);

	for (size_t i(0); i < steps; ++i)
		for (size_t j(0); j < Spot0.size(); ++j)
			stocks_path[j] += drift[j] + StochasticTerm(A, j, args_[i]);
	
	return stocks_path.apply(std::exp);
}

matrix<double> PathGenerationMulti::GetWholePathMulti(args& args_) {

	matrix<double> stocks_path(steps + 1,Spot0.size());

	for (size_t i(0); i < Spot0.size(); ++i)
		stocks_path(0,i) = Spot0[i];

	for (size_t i(0); i < args_.size(); ++i)
		TheGenerator->GetGaussians(args_[i]);

	MJArray tmp(Spot0.size());

	for (size_t i(0); i < steps; ++i){
		for (size_t j(0); j < Spot0.size(); ++j){

			for (size_t k(0); k < tmp.size(); ++k)
				tmp[k] = args_[k][i];

			stocks_path(i + 1, j) = stocks_path(i, j) * exp(drift[j] + StochasticTerm(A, j, tmp));
		}
	}

	return stocks_path;
}
