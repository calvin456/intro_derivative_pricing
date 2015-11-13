//path_generation_jdp.cpp

#include <cmath>

#include "path_generation_jdp.h"

using namespace std;

PathGenerationJDP::PathGenerationJDP(shared_ptr<RandomBase> TheGenerator_,
																			double Spot0_,
																			double T_,
																			const Parameters& drift_,
																			const Parameters& vol_,
																			double kappa_,
																			double m_,
																			double nu_,
																			unsigned long steps_)
	: PathGeneration(TheGenerator_, Spot0_, T_, steps_), drift(drift_), vol(vol_),
			kappa(kappa_), m(m_), nu(nu_)
{
	TheGenerator->ResetDimensionality(steps);
}

double PathGenerationJDP::GetOnePath(args& args_) const
{

		//var. rng Poisson
		//var. rng Gaussian

		double log_stock_spot(log(Spot0));

		double deltaT(T / steps);
		double alpha(drift.Integral(0.0, deltaT) - .5 * vol.IntegralSquare(0.0, deltaT));
		double beta(sqrt(vol.IntegralSquare(0.0, deltaT)));

		double gamma(kappa * (exp(0.0) - 1.0) );

		TheGenerator->GetPoissons(kappa, args_[0]);
		TheGenerator->GetGaussians(args_[2]);

		double a(0.0 - .5 * nu * nu);
		double b(log(m));

		for (size_t j(0); j < steps; ++j){
			//log_stock_spot += alpha + args_[0][j] * (log(m) - .5 * nu * nu) + sqrt(beta * beta + args_[0][j] * nu * nu) * args_[1][j];

			double u(0.0);

			for(size_t k(0);k < args_[0][j];++k){
				TheGenerator->GetGaussians(args_[1]);
				u += b * (a + nu *args_[1][0]);
			}

			log_stock_spot += alpha + gamma + beta * args_[2][j] + u ;

		}

		return exp(log_stock_spot);
}


MJArray PathGenerationJDP::GetWholePath(args& args_)
{

	//var. rng Poisson
	//var. rng Gaussian

	MJArray stock_path(steps + 1);
	stock_path[0] = Spot0;

	double deltaT(T / steps);
	double alpha(drift.Integral(0.0, deltaT) - .5 * vol.IntegralSquare(0.0, deltaT));
	double beta(sqrt(vol.IntegralSquare(0.0, deltaT)));

	double gamma(kappa * (exp(0.0) - 1.0));

	TheGenerator->GetPoissons(kappa, args_[0]);
	TheGenerator->GetGaussians(args_[2]);

	double a(0.0 - .5 * nu * nu);
	double b(log(m));

	for (size_t j(0); j < steps; ++j){
		//stock_path[j + 1] = stock_path[j] * exp(alpha + args_[0][j] * (log(m) - .5 * nu * nu) + sqrt(beta * beta + args_[0][j] * nu * nu) * args_[1][j]);

		double u(0.0);

		for(size_t k(0);k < args_[0][j];++k){
			TheGenerator->GetGaussians(args_[1]);
			u += b * (a + nu *args_[1][0]);
		}

		stock_path[j + 1] = stock_path[j] * exp(alpha + gamma + beta * args_[2][j] + u);
	}

	return stock_path;
}
