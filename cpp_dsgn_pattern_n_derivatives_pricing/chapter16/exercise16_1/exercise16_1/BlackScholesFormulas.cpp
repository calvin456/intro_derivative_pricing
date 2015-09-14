//
//
//                        BlackScholesFormulas.cpp
//
//


#include "BlackScholesFormulas.h"
#include "Normals.h"
#include <cmath>

using namespace std;

/*
#if !defined(_MSC_VER)
using namespace std;
#endif
*/
double BlackScholesCall(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry)
{
	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	double d2 = d1 - standardDeviation;
	return Spot*exp(-d*Expiry) * CumulativeNormal(d1) - Strike*exp(-r*Expiry)*CumulativeNormal(d2);
}


double BlackScholesPut(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry)
{
	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	double d2 = d1 - standardDeviation;
	return Strike*exp(-r*Expiry)*(1.0 - CumulativeNormal(d2)) - Spot*exp(-d*Expiry) * (1 - CumulativeNormal(d1));
}

double BlackScholesDigitalCall(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry)
{
	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d2 = (moneyness + (r - d)*Expiry - 0.5* standardDeviation*standardDeviation) / standardDeviation;
	return exp(-r*Expiry)*CumulativeNormal(d2);
}

double BlackScholesDigitalPut(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry)
{
	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d2 = (moneyness + (r - d)*Expiry - 0.5* standardDeviation*standardDeviation) / standardDeviation;
	return exp(-r*Expiry)*(1.0 - CumulativeNormal(d2));
}


double BlackScholesCallVega(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry)
{
	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	return Spot*exp(-d*Expiry) * sqrt(Expiry)*NormalDensity(d1);


}


//B.3 Project 1: Vanilla options in a Black-Scholes world
double Forward(double Spot,
	double Strike,
	double r,
	double d,
	double Expiry){


	return std::exp(-r*Expiry) * (Spot * std::exp((r - d)*Expiry) - Strike);

}


double ZeroCoupon(double r,
	double Expiry){

	return 1.0 / std::exp(r* Expiry);

}

double BlackScholesCallDelta(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	return exp(-d*Expiry)*CumulativeNormal(d1);

}

double BlackScholesGamma(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	return exp(-d*Expiry)*NormalDensity(d1) / (Spot * standardDeviation);

}

double BlackScholesCallRho(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	double d2 = d1 - standardDeviation;
	return Strike * Expiry * exp(-r*Expiry) * CumulativeNormal(d2);

}

double BlackScholesCallTheta(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	double d2 = d1 - standardDeviation;

	return -Spot * exp(-d*Expiry) * NormalDensity(d1)* Vol / (2 * sqrt(Expiry))
		- r * Strike * exp(-r*Expiry) * CumulativeNormal(d2)
		+ d * Spot * exp(-d*Expiry) * CumulativeNormal(d1);

}

/*
*
* Copyright (c) 2002
* Mark Joshi
*
* Permission to use, copy, modify, distribute and sell this
* software for any purpose is hereby
* granted without fee, provided that the above copyright notice
* appear in all copies and that both that copyright notice and
* this permission notice appear in supporting documentation.
* Mark Joshi makes no representations about the
* suitability of this software for any purpose. It is provided
* "as is" without express or implied warranty.
*/

