
#include"cppinterface.h"
#pragma warning (disable : 4996)


double _BlackScholesCall(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	return  BlackScholesCall(Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry);
}

double _BlackScholesPut(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	return BlackScholesPut(Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry);
}

double _BlackScholesDigitalCall(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	return BlackScholesDigitalCall(Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry);
}

double _BlackScholesDigitalPut(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	return BlackScholesDigitalPut(Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry);

}



double _BlackScholesCallVega(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry){

	return BlackScholesCallVega(Spot,
		Strike,
		r,
		d,
		Vol,
		Expiry);
}
