//asian_options.cpp

//Assumption BSM world

//ref. Pricing Asian Options using MC methods, Hong Bin Zhang, MSc Thesis, Uppsala University, 2009

#include "asian_option.h"
#include <cmath>
#include <Normals.h>

using namespace std;

//discrete Asian call option - Geometric average
double asian_geo_call(double Spot,
	unsigned long m_, // # of observation dates
	double Strike,
	double r_,
	double d_,
	double Vol,
	double Expiry)
{
	double m(m_);
	double r(r_ - d_);
	
	//double sigma_z(Vol * sqrt((2 * m + 1) / (6 * (m + 1))));
	
	//double rho(.5 * ((r - .5 * Vol * Vol ) + sigma_z * sigma_z));
	
	double sigma_z(Vol * sqrt(((m + 1) * (2 * m + 1) / (6 * m * m))));

	double standardDeviation = sigma_z * sqrt(Expiry);

	double rho(0.5 * standardDeviation * standardDeviation + (r - .5 * Vol * Vol) * Expiry * (m + 1) / (2 * m));

	double moneyness = log(Spot / Strike);

	double d1 = (moneyness + rho * Expiry + 0.5 * standardDeviation * standardDeviation) / standardDeviation;
	
	double d2 = d1 - standardDeviation;
	
	return exp(-r * Expiry) * (Spot * exp(rho  * Expiry) * CumulativeNormal(d1) - Strike * CumulativeNormal(d2));
}

//discrete Asian put option - Geometric average
double asian_geo_put(double Spot,
	unsigned long m_, // # of observation dates
	double Strike,
	double r_,
	double d_,
	double Vol,
	double Expiry)
{
	double m(m_);
	double r(r_ - d_);

	//double sigma_z(Vol * sqrt((2 * m + 1) / (6 * (m + 1))));

	//double rho(.5 * ((r - .5 * Vol * Vol) + sigma_z * sigma_z));

	double sigma_z(Vol * sqrt(((m + 1) * (2 * m + 1) / (6 * m * m))));

	double standardDeviation = sigma_z * sqrt(Expiry);

	double rho(0.5 * standardDeviation * standardDeviation + (r - .5 * Vol * Vol) * Expiry * (m + 1) / (2 * m));

	double moneyness = log(Spot / Strike);

	double d1 = (moneyness + rho * Expiry + 0.5 * standardDeviation * standardDeviation) / standardDeviation;

	double d2 = d1 - standardDeviation;

	return exp(-r * Expiry) * (Strike * (1.0 - CumulativeNormal(d2)) - Spot * exp(rho * Expiry) * (1.0 - CumulativeNormal(d1)));
}