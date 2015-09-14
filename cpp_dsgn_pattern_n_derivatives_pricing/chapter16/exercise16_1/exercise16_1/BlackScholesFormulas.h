//
//
//                      BlackScholesFormulas.h
//
//

#ifndef BLACK_SCHOLES_FORMULAS_H
#define BLACK_SCHOLES_FORMULAS_H



double BlackScholesCall(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);


double BlackScholesPut(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double BlackScholesDigitalCall(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double BlackScholesDigitalPut(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);


double BlackScholesCallVega(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

//B.3 Project 1: Vanilla options in a Black-Scholes world
double Forward(double Spot,
	double Strike,
	double r,
	double d,
	double Expiry);


double ZeroCoupon(double r,
	double Expiry);


double BlackScholesCallDelta(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double BlackScholesGamma(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double BlackScholesCallRho(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double BlackScholesCallTheta(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

#endif

/*
*
* Copyright (c) 2002
* Mark Joshi
*
* Permission to use, copy, modify, distribute and sell this
* software for any purpose is hereby
* granted without fee, provided that the above copyright notice
* appear in all copies and that both that copyright notice and
* this permission notice appear in supporting documentation.
* Mark Joshi makes no representations about the
* suitability of this software for any purpose. It is provided
* "as is" without express or implied warranty.
*/

