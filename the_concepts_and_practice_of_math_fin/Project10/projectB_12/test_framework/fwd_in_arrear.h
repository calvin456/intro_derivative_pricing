//fwd_in_arrear.h

//test in-arrear libor forward FRA

#ifndef FWD_IN_ARREAR_QL_H
#define FWD_IN_ARREAR_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double in_arrear_fra(const Date& todaysDate_,
	double start,
	double length,
	Rate spot_,
	Rate strike,
	Volatility volatility
	);

#endif