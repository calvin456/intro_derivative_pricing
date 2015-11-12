//caplet_lmm_ql.h

//test caplet

#ifndef CAPLET_LMM_QL_H
#define CAPLET_LMM_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double caplet_lmm(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Rate spot_,
	Rate strike,
	Rate Numeraire, //zero-coupon bond
	//Volatility volatility

	double correl,
	double a,
	double b,
	double c,
	double d
	);

#endif