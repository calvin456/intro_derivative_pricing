//quanto_margrabe.cpp

#include "quanto_margrabe.h"
#include <Normals.h>
#include <cmath>

using namespace std;

//closed-form formula in BSM world

//ref. Mark H.A.Davis,Mathematical Option Pricing,MSc Course in Mathematics and Finance
//Imperial College London,11 January 2006

//quanto options - currency-protected options

//the option value at maturity is A0 max[ST −K, 0] units of domestic currency, where A0 is an
//arbitrary exchange factor, for example the time-zero exchange rate.

//quanto options not equal to FX quanto options - 2 assets not 3.

double QuantCallOption(double Spot,
	double Strike,
	double rd, //interest rate of domestic currency
	double rf, //interest rate of foreign currency
	double d, //dvd yield
	double VolS, //vol stock price 
	double VolQ, //vol foreign currency
	double correl, // correl
	double Expiry)
{
	double _d(d - rd - rf + correl * VolS * VolQ);
	double r(rd);

	double standardDeviation = VolS*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - _d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	double d2 = d1 - standardDeviation;
	return Spot*exp(-_d*Expiry) * CumulativeNormal(d1) - Strike*exp(-r*Expiry)*CumulativeNormal(d2);

}

double QuantPutOption(double Spot,
	double Strike,
	double rd, //interest rate of domestic currency
	double rf, //interest rate of foreign currency
	double d, //dvd yield
	double VolS, //vol stock price 
	double VolQ, //vol foreign currency
	double correl, // correl
	double Expiry)
{
	double _d(d - rd - rf + correl * VolS * VolQ);
	double r(rd);

	double standardDeviation = VolS*sqrt(Expiry);
	double moneyness = log(Spot / Strike);
	double d1 = (moneyness + (r - _d)*Expiry + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	double d2 = d1 - standardDeviation;
	return Strike*exp(-r*Expiry)*(1.0 - CumulativeNormal(d2)) - Spot*exp(-_d*Expiry) * (1 - CumulativeNormal(d1));

}



//Margrabe options aka outperformance options, exchange options : max(S1 - S2,0)

//Not equal to spread options : max(S1 - S2 - K,0) 

double MargrabeOptions(double Spot1,
	double Spot2,
	double Vol1,
	double Vol2,
	double correl, // correl
	double Expiry)
{
	double Vol(sqrt(Vol1 * Vol1 + Vol2 * Vol2 - 2.0 * correl * Vol1 * Vol2));

	double standardDeviation = Vol*sqrt(Expiry);
	double moneyness = log(Spot1 / Spot2);
	double d1 = (moneyness + 0.5* standardDeviation*standardDeviation) / standardDeviation;
	double d2 = d1 - standardDeviation;
	return Spot1 * CumulativeNormal(d1) - Spot2*CumulativeNormal(d2);
}