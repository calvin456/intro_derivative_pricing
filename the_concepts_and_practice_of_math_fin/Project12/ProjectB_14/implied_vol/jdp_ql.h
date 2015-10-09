
//jdp_ql.h

#ifndef HESTON_QL_H
#define HESTON_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double jdp_ql_call(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real underlying,
	Real strike,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility,
	Real kappa,
	Real m,
	Real nu);

#endif