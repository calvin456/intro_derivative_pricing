#include <cmath>

#include "HestonIntegrand.h"

using namespace std;

//ref. for c++ code http://volopta.com/C.html

//ref. The Heston Model: A practical Approach w/ Matlab code, Nimalin Moodley, 2005

HestonIntegrand::HestonIntegrand(const ParametersHeston& p, bool type)
	:p(p), type(type)
{}


//Characteristic function Heston model
//Helper function
complex<double> HestonIntegrand::HestonCharacteristicFunc(double x_) const
{

	complex<double> x = complex<double>(x_, 0);

	complex<double> kappa = p.GetKappaComplex();
	complex<double> theta = p.GetThetaComplex();
	complex<double> sigma = p.GetSigmaComplex();
	complex<double> correl = p.GetCorrelComplex();
	complex<double> Vol = p.GetVolComplex();
	complex<double> r = p.GetRateComplex();
	complex<double> Expiry = p.GetExpiryComplex();
	complex<double> Spot = p.GetSpotComplex();

	complex<double> u = complex<double>(0.5, 0);
	complex<double> b = kappa;

	complex<double> one = complex<double>(1, 0);
	complex<double> two = complex<double>(2, 0);
	complex<double> sig2 = sigma * sigma;

	type ? b = kappa - correl * sigma : u *= -1.0;

	complex<double> a = kappa * theta;
	complex<double> z = complex<double>(log(p.GetSpot()), 0);

	complex<double> tmp1 = complex<double>(0, (correl * sigma * x).real());

	complex<double> tmp2 = complex<double>(0, (two * u * x).real());

	complex<double> d = sqrt((tmp1 - b) * (tmp1 - b) - sig2 * (tmp2 - x * x));
	complex<double> g = (b - tmp1 + d) / (b - tmp1 - d);

	tmp2 = complex<double>(0, (r * x * Expiry).real());

	complex<double> C = tmp2 + a / sig2 * ((b - tmp1 + d) * Expiry - two * log((one - g * exp(d * Expiry)) / (one - g)));

	complex<double> D = (b - tmp1 + d) / sig2 * ((one - exp(d * Expiry)) / (one - g * exp(d * Expiry)));

	tmp2 = complex<double>(0, (x * z).real());

	return exp(C + D * Vol + tmp2);

}

//Function Heston integrand
//returns real part of integrand
double HestonIntegrand::operator()(double x) const
{
	complex<double> tmp1 = complex<double>(0, - x * log(p.GetStrike()));

	complex<double> tmp2 = HestonCharacteristicFunc(x);

	complex<double> tmp3 = complex<double>(0, x);

	return (exp(tmp1)*tmp2 / tmp3).real();

}
