//HestonPricingAnalytical.cpp

#define _USE_MATH_DEFINES
#include<cmath>

#include "HestonPricingAnalytical.h"

#include<NumericalIntegration.h>
#include<NumericalRule.h>

using namespace std;

//Do not use Fast Fourrier Transform and Carr-Madan inversion. Use Heston original formula

double HestonVanillaCalltAnalytical(const ParametersHeston& p){

	double Tolerance(1e-6);
	double Low(1e-7);
	double High(1e2);
	unsigned long Steps(static_cast<unsigned long>(1e4));


	bool type(true);

	HestonIntegrand  myFunc(p, type);

	Trapezium_rule<HestonIntegrand> rule(Low, High, myFunc);

	//compute probability using numerical integration - trapezoidal rule

	double prob1 = Numerical_integration<Trapezium_rule, HestonIntegrand>(Tolerance, Steps, rule);
	prob1 *= 1 /M_PI; prob1 += 0.5;
	//cout << prob1 << endl;

	type = false;

	HestonIntegrand  myFunc1(p, type);

	Trapezium_rule<HestonIntegrand> rule1(Low, High, myFunc1);

	double prob2 = Numerical_integration<Trapezium_rule, HestonIntegrand>(Tolerance, Steps, rule1);
	prob2 *= 1 / M_PI; prob2 += 0.5;
	//cout << prob2 << endl;

	return p.GetSpot() * prob1 - p.GetStrike() * exp(-p.GetRate() * p.GetExpiry()) * prob2;
}

double HestonVanillaPutAnalytical(const ParametersHeston& p){
	//can deduce put price using put-call parity

	return HestonVanillaCalltAnalytical(p) + p.GetStrike() * exp(-p.GetRate() * p.GetExpiry()) - p.GetSpot();
}
