//HestonIntegrand.h

#ifndef HESTON_INTEGRAND_H
#define HESTON_INTEGRAND_H

//#include "parameters_heston.h"

#include <complex>

using namespace std;

//Parameters class
class ParametersHeston{
	// dSt = mu * St * dt + sqrt(Vt) * St * dW1(t)
	// dVt = kappa * (theta - Vt) * dt + sigma * sqrt(Vt) * dW2(t)
	//dW1(t) * dW2(t) = correl * dt
public:
	ParametersHeston(double mu,
		double Spot,
		double Vol,
		double r,
		double kappa,
		double theta,
		double sigma,
		double correl,
		double Strike,
		double Expiry)
		:mu(mu), Spot(Spot), Vol(Vol), r(r), kappa(kappa), theta(theta), sigma(sigma), correl(correl), Strike(Strike), Expiry(Expiry)
	{}

	~ParametersHeston(){}

	double GetMu() const { return mu; }
	double GetSpot() const { return Spot; }
	double GetVol() const { return Vol; }
	double GetRate() const { return r; }
	double GetKappa() const { return kappa; }
	double GetTheta() const { return theta; }
	double GetSigma() const { return sigma; }
	double GetCorrel() const { return correl; }
	double GetStrike() const { return Strike; }
	double GetExpiry() const { return Expiry; }

	complex<double> GetMuComplex() const { return complex<double>(mu, 0); }
	complex<double> GetSpotComplex() const { return complex<double>(Spot, 0); }
	complex<double> GetVolComplex() const { return complex<double>(Vol, 0); }
	complex<double> GetRateComplex() const { return complex<double>(r, 0); }
	complex<double> GetKappaComplex() const { return complex<double>(kappa, 0); }
	complex<double> GetThetaComplex() const { return complex<double>(theta, 0); }
	complex<double> GetSigmaComplex() const { return complex<double>(sigma, 0); }
	complex<double> GetCorrelComplex() const { return complex<double>(correl, 0); }
	complex<double> GetStrikeComplex() const { return complex<double>(Strike, 0); }
	complex<double> GetExpiryComplex() const { return complex<double>(Expiry, 0); }

private:
	double mu;
	double Spot;
	double Vol;
	double r;
	double kappa;
	double theta;
	double sigma;
	double correl;
	double Strike;
	double Expiry;

};

class HestonIntegrand{

public:

	HestonIntegrand(const ParametersHeston& p, bool type);

	double operator()(double x) const;

protected:
	complex<double> HestonCharacteristicFunc(double x) const;

private:
	ParametersHeston p;
	double x;
	bool type; //if true Prob1 otherwise Prob2
};


#endif
