#include "VGIntegrand.h"

#include <cmath>
#include <Normals.h>

using namespace std;

VGIntegrand::VGIntegrand(double Spot,
	double Strike,
	double r,
	double Expiry,
	double sigma,
	double nu,
	double theta)
	:Spot(Spot), Strike(Strike), r(r), Expiry(Expiry), sigma(sigma), nu(nu), theta(theta)
{}

double VGIntegrand::operator()(double x) const
{
	double gamma(Expiry / nu);

	double zeta(-theta / (sigma * sigma));

	double s(sigma / sqrt(1.0 + (theta / sigma) * (theta / sigma) * nu / 2.0));

	double alpha(zeta * s);

	double c1(nu* (alpha + s) * (alpha + s) / 2.0);

	double c2(nu * alpha * alpha / 2.0);

	//double d(1.0 / s * (log(Spot * exp(r * Expiry) / Strike)
	//	+ gamma * log((1.0 - c1) / (1.0 - c2))));

	double d(log(Spot * exp(r * Expiry) / Strike) / s + gamma / s * log((1 - c1) / (1 - c2)));

	double z1(d / sqrt(nu) / sqrt(x) + (alpha + s) * sqrt(nu) * sqrt(x));

	double z2(z1 - s * sqrt(nu) * sqrt(x));

	double tmp = Spot * pow(1.0 - c1, gamma) * exp(c1 * x) * CumulativeNormal(z1)
		- Strike * exp(-r * Expiry) * pow(1.0 - c2, gamma) * exp(c2 * x)  *  CumulativeNormal(z2);

	tmp *= pow(x, gamma - 1.0)	* exp(-x) / tgamma(gamma);

	return tmp;

}