//function_to_eval.cpp


// ref. Drift approx in a fwd-rate-based LMM, Hunter, Jaeckel, Joshi, 2001

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include <algorithm>

#include"function_to_eval.h"

using namespace std;

FuncToEval::FuncToEval(double f0_, double strike_, double vol_, double t1_, double t2_, product product_)
	:f0(f0_), strike(strike_), vol(vol_), t1(t1_), t2(t2_), _product(product_)
{}

// p.4

double FuncToEval::operator()(double fwd_rte) const
{
	double tau(t2 - t1);
	double vol_square(vol * vol * t1);

	double payoff(0.0);

	if (_product == fwd)
		payoff = fwd_rte - strike, 0.0;
	else if(_product == caplet)
		payoff = max(fwd_rte - strike, 0.0);
	else
		payoff = max(strike - fwd_rte, 0.0);

	payoff *= (1.0 + fwd_rte * tau) * tau;

	double a((1.0 + fwd_rte * tau) / (1.0 + f0 * tau));

	double b(log(fwd_rte / f0) + .5 * vol_square);

	double in_arrear_density(1.0 / sqrt(2.0*M_PI) * exp((-.5 * b * b) / vol_square) * 1.0 / (fwd_rte * sqrt(vol_square)));

	in_arrear_density *= a;

	return payoff * in_arrear_density;

}