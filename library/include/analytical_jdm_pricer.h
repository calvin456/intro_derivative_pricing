//analytical_jdm_pricer

/*
Compute jump difusion model using Merton formula
*/


#include <MyFunctions.h>
#include <cmath>

using namespace std;

template<class T>
double analytical_jdm_pricer(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry,

	double kappa,
	double m,
	double nu,
	T* option) 
{

	option->SetStrike(Strike);
	option->Setr(r);
	option->Setd(d);
	option->SetVol(Vol);
	option->SetExpiry(Expiry);

	unsigned long i(0);

	double sum(0.0);

	double prob(1.0);

	double kappa_prime(kappa * m);

	do{

		double sigma_i = sqrt(option->GetVol() * option->GetVol() + i * nu * nu / option->GetExpiry());

		double r_i = option->Getr() - kappa * (m - 1.0) + i * log(m) / option->GetExpiry();

		prob = (exp(-kappa_prime * option->GetExpiry()) *  pow(kappa_prime * option->GetExpiry(), (double)(i))) / factorial(i);

		sum += prob  * option->GetValue(Spot, r_i, sigma_i, option->GetExpiry());

		++i;

	} while (prob > 1e-6);

	return sum;

};