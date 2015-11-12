//swaption_lmm_ql.h

//test caplet, swaption, trigger swap up & out

#ifndef SWAPTION_LMM_QL_H
#define SWAPTION_LMM_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double swaption_lmm(const Date& todaysDate_,
	unsigned long start,
	unsigned long length,
	Rate spot,
	Rate strike,
	double correl,
	double a,
	double b,
	double c,
	double d
	);

double swaption_iv_lmm(const Date& todaysDate_,
	unsigned long start,
	unsigned long length,
	Real price,
	Rate spot,
	Rate strike,
	double correl,
	double a,
	double b,
	double c,
	double d
	);

#endif