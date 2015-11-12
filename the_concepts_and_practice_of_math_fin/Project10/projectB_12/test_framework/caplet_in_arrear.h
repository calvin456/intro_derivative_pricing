//caplet_in_arrear.h

//test in-arrear libor forward FRA

#ifndef CAPLET_IN_ARREAR_QL_H
#define CAPLET_IN_ARREAR_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double in_arrear_caplet(const Date& todaysDate_,
	double start,
	double length,
	Rate spot_,
	Rate strike,
	Volatility volatility
	);

double in_arrear_floorlet(const Date& todaysDate_,
	double start,
	double length,
	Rate spot_,
	Rate strike,
	Volatility volatility
	);

#endif