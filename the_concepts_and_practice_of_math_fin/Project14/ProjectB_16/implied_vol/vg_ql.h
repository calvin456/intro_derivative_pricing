
//vg_ql.h

#ifndef HESTON_QL_H
#define HESTON_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

Real vg_ql_call(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real underlying_,
	Real strike_,
	Spread dividendYield_,
	Rate riskFreeRate_,
	Real sigma_,
	Real nu_,
	Real theta_
	);

#endif