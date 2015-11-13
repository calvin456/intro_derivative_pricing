//VGPricingAnalytical.h

//price vanilla options using analytical for VG model

//ref. The variance gamma process and option pricing, Madan, Carr, Chang, 1998

//S(t) = S(0) * exp( r * t + X(t,sigma,nu,theta) + omega * t; X := Lévy process

#ifndef VG_PRICING_ANALYTICAL_H
#define VG_PRICING_ANALYTICAL_H



double VGVanillaCallAnalytical(double Spot,
	double Strike,
	double r,
	double Expiry,
	double Vol,
	double nu,
	double theta
	);

double VGVanillaPutAnalytical(double Spot,
	double Strike,
	double r,
	double Expiry,
	double Vol,
	double nu,
	double theta
	);

#endif