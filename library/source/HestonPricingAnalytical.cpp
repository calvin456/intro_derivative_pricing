//HestonPricingAnalytical.cpp

#define _USE_MATH_DEFINES
#include<cmath>

#include "HestonPricingAnalytical.h"

#include<NumericalIntegration.h>
#include<NumericalRule.h>

using namespace std;

//Do not use Fast Fourrier Transform and Carr-Madan inversion. Use Heston original formula

double HestonVanillaCalltAnalytical(const ParametersHeston& p){

	double Tolerance(1e-04);
	double Low(1e-07);
	double High(1e02);
	unsigned long Steps(static_cast<unsigned long>(1e04));

	HestonIntegrand  myFunc(p, true);
	

	Trapezium_rule<HestonIntegrand> rule(Low, High, myFunc);

	//compute probability using numerical integration - trapezoidal rule

	double prob1 = Numerical_integration<Trapezium_rule, HestonIntegrand>(Tolerance, Steps, rule);
	prob1 /= M_PI; prob1 += 0.5;

	HestonIntegrand  myFunc1(p, false);
	

	Trapezium_rule<HestonIntegrand> rule1(Low, High, myFunc1);

	double prob2 = Numerical_integration<Trapezium_rule, HestonIntegrand>(Tolerance, Steps, rule1);
	prob2 /=  M_PI; prob2 += 0.5;

	double ft(exp(p.GetRate() * p.GetExpiry()) * p.GetSpot());
	double x(log(p.GetStrike() / ft));
	
	return p.GetStrike() * (exp(x) * prob2 - prob1);
	
}

double HestonVanillaPutAnalytical(const ParametersHeston& p){
	//can deduce put price using put-call parity

	return HestonVanillaCalltAnalytical(p) + p.GetStrike() * exp(-p.GetRate() * p.GetExpiry()) - p.GetSpot();
}
