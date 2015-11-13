//VGIntegrand.h

#ifndef VG_INTEGRAND_H
#define VG_INTEGRAND_H

class VGIntegrand{

public:

	VGIntegrand(double Spot,
		double Strike,
		double r,
		double Expiry,
		double sigma,
		double nu,
		double theta);

	double operator()(double x) const;

private:

	double Spot;
	double Strike;
	double r;
	double Expiry;
	double sigma;
	double nu;
	double theta;
	double x;

};

#endif