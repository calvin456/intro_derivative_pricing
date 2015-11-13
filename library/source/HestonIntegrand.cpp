#include <cmath>

#include "HestonIntegrand.h"

using namespace std;

//ref. for c++ code http://volopta.com/C.html

//ref. Efficient MC simul w/ stochastic vol, T. Odelman, KTH, MSc Thesis, 2009

HestonIntegrand::HestonIntegrand(const ParametersHeston& p, bool type)
	:p(p), type(type)
{}


//Characteristic function Heston model
//Helper function
complex<double> HestonIntegrand::HestonCharacteristicFunc(double u) const
{

	double ft(exp(p.GetRate() * p.GetExpiry()) * p.GetSpot());
	double x(log(p.GetStrike() / ft));
	
	complex<double> alpha = type ? complex<double>(-.5 * u * u, -.5 * u) : complex<double>(-.5 * u * u, .5 * u);

	complex<double> beta = type ? complex<double>(p.GetKappa(), -p.GetCorrel() * p.GetSigma() * u) : complex<double>(p.GetKappa() - p.GetCorrel() * p.GetSigma(), -p.GetCorrel() * p.GetSigma() * u);

	double gamma(.5 * p.GetSigma() * p.GetSigma());

	complex<double> d(sqrt(beta * beta - 4.0 * alpha * gamma));

	double s2 = p.GetSigma() * p.GetSigma();

	complex<double> r_minus((beta - d) / s2);
	complex<double> r_plus((beta + d) / s2);

	complex<double> g(r_minus / r_plus);

	complex<double> tmp(1.0 - g * exp(-d * p.GetExpiry()));

	complex<double> D(r_minus * (1.0 - exp(-d * p.GetExpiry())) / tmp);

	complex<double> C(p.GetKappa() * (r_minus * p.GetExpiry() - 2.0 / s2 * log(tmp/(1.0 - g))));

	complex<double> tmp1 = complex<double>(0.0, u * x);

	return exp(C * p.GetTheta()  + D * p.GetVol() + tmp1);

}

//Function Heston integrand
//returns real part of integrand
double HestonIntegrand::operator()(double u) const
{

	complex<double> tmp2 = HestonCharacteristicFunc(u);

	complex<double> tmp3 = complex<double>(0, u);

	return (tmp2 / tmp3).real();

}
