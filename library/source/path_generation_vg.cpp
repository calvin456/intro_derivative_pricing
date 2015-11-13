//path_generation_vg.cpp

#include <iostream>

#include <cmath>

#include <path_generation_vg.h>

using namespace std;

PathGenerationVG::PathGenerationVG(shared_ptr<RandomBase>& TheGenerator_,
																		double Spot0_,
																		double T_,
																		const Parameters& drift_,
																		const Parameters& vol_,
																		double nu_,
																		double theta_,
																		unsigned long steps_)
	: PathGeneration(TheGenerator_, Spot0_, T_, steps_), drift(drift_), vol(vol_), nu(nu_), theta(theta_)
{
	omega = log(1.0 - theta * nu - .5 * vol.IntegralSquare(0.0, 1.0 ) * nu )/nu;

	TheGenerator->ResetDimensionality(steps);
}

//VG and MC, Michael C. Fu, University of Maryland
//Efficient simul of gamma and VG processes, Avramidis et al., Université de Montréal, Proceedings of the 2003 Winter Simulation Conference
//S.Chick, P.J.Sanchez, D.Ferrin, and D.J.Morrice, eds

double PathGenerationVG::GetOnePath(args& args_) const{

	//Variates  simul Gamma distr
	//Variates1 simul Gaussian distr

	double log_stock_spot = log(Spot0);

	double deltaT(T / steps);

	double a(drift.Integral(0.0, deltaT) + omega * deltaT);

	TheGenerator->GetGammas(deltaT / nu, nu , args_[0]);
	TheGenerator->GetGaussians(args_[1]);

	//p.26 simulating VG as Gamma time-changed Brownian motion
	double x(0.0);

	for (size_t j(0); j < steps; ++j){

		double deltaG(max(args_[0][j],0.0)); 

		x = theta * deltaG + sqrt(vol.IntegralSquare(0.0,deltaG)) * args_[1][j];
		
		log_stock_spot += (a + x);
	}

	return exp(log_stock_spot);
}

MJArray PathGenerationVG::GetWholePath(args& args_) {

	//Variates  simul Gamma distr
	//Variates1 simul Gaussian distr

	MJArray stock_path(steps + 1);
	stock_path[0] = Spot0;

	double deltaT(T / steps);

	double a(exp(drift.Integral(0.0, deltaT) + omega * deltaT));

	TheGenerator->GetGammas(deltaT / nu, nu, args_[0]);
	TheGenerator->GetGaussians(args_[1]);

	//p.26 simulating VG as Gamma time-changed Brownian motion
	double x(0.0);

	for (size_t j(1); j <= steps; ++j){

		double deltaG(max(args_[0][j], 0.0)); 

		x = theta * deltaG + sqrt(vol.IntegralSquare(0.0, deltaG)) * args_[1][j];

		stock_path[j] = stock_path[j - 1] * a * exp(x);
	}

	return stock_path;
}

//VG and MC Michael C. Fu, University of Maryland
//Efficient simul of gamma and VG processes, Avramidis et al., Université de Montréal, Proceedings of the 2003 Winter Simulation Conference
//S.Chick, P.J.Sánchez, D.Ferrin, and D.J.Morrice, eds

//Simulating VG via Brownian Bridge (Gamma time-changed)
MJArray PathGenerationVG::GetOnePathBB(args& args_) {

	//Variates Gamma tn, Beta
	//Variates1  Gaussian  tn, Gaussian

	unsigned long m(static_cast<unsigned long>(log2(steps))); //def m as # of bridges : n = 2^m

	MJArray stock_path(steps+1); 
	stock_path[0] = Spot0;

	double deltaT(T / steps);

	double a(exp(drift.Integral(0.0, deltaT) + omega * deltaT));

	//p.28 simulating VG as Gamma time-changed Brownian bridge

	//initialize gamma_tn and x_tn
	TheGenerator->GetGammas(T / nu, nu, args_[0]);
	TheGenerator->GetGaussians(args_[1]);

	args_[1][0] = theta * args_[0][0] + sqrt(vol.IntegralSquare(0.0, args_[0][0])) * args_[1][0];

	MJArray gamma(steps);
	gamma[0] = 0.0;
	gamma[steps - 1] = args_[0][0];

	MJArray x(steps);
	x[0] = 0.0;
	x[steps - 1] = args_[1][0];

	for (size_t k(1); k <= m; ++k){

		unsigned long n(static_cast<unsigned long>(exp2(m - k)));

		for (size_t j(1); j <= exp2(k - 1); ++j){

			unsigned long i((2 * j - 1)*n);

			double t_i(deltaT*i), t_i_n_minus(deltaT*(i - n)), t_i_n_plus(deltaT*(i + n));

			TheGenerator->GetBetas((t_i - t_i_n_minus) / nu, (t_i_n_plus - t_i) / nu, args_[0]);

			gamma[i - 1] = gamma[i - n] + (gamma[i + n - 1] - gamma[i - n]) * args_[0][0];

			double b(gamma[i + n - 1] - gamma[i - 1] == 0 ? 1 : gamma[i + n - 1] - gamma[i - 1]);

			TheGenerator->GetGaussians(args_[1]);

			args_[1][0] =  sqrt(vol.IntegralSquare(0.0, 1.0)) * b * args_[0][0] * args_[1][0];

			x[i - 1] = args_[0][0] * x[i + n - 1] + (1.0 - args_[0][0]) * x[i - n] + args_[1][0];

		}
	}

	for (size_t i(0);i < stock_path.size() - 1;++i)
		stock_path[i + 1] = stock_path[i] * a * exp(x[i]);

	return stock_path;
}
