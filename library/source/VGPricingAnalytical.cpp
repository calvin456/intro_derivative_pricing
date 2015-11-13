//VGPricingAnalytical .cpp

#include "VGPricingAnalytical.h"

#include <cmath>

#include "VGIntegrand.h"

#include<NumericalIntegration.h>
#include<NumericalRule.h>

#include<Terminator.h>

using namespace std;

double VGVanillaCallAnalytical(double Spot,
	double Strike,
	double r,
	double Expiry,
	double Vol,
	double nu,
	double theta
	)
{

	double Tolerance(1e-3); //1e-6
	double Low(1e-7);
	double High(1e2); 
	unsigned long Steps(static_cast<unsigned long>(1e4)); //1e4

	bool type(true);

	VGIntegrand  myFunc(Spot, Strike, r, Expiry, Vol, nu, theta);

	Trapezium_rule<VGIntegrand> rule(Low, High, myFunc);
	//Simpson_rule<VGIntegrand> rule(Low, High, myFunc);

	//evaluate semi-definite integral p.99 
	Terminator terminator(10, Steps); //5 sec, 100 max iter

	return Numerical_integration1<Trapezium_rule, VGIntegrand>(Tolerance, Steps, rule, terminator);
	//return Numerical_integration<Simpson_rule, VGIntegrand>(Tolerance, Steps, rule);
}

double VGVanillaPutAnalytical(double Spot,
	double Strike,
	double r,
	double Expiry,
	double Vol,
	double nu,
	double theta
	)
{
	//can deduce put price using put-call parity

	return VGVanillaCallAnalytical(Spot, Strike, r, Expiry, Vol, nu, theta)
		+ Strike * exp(-r * Expiry) - Spot;
}