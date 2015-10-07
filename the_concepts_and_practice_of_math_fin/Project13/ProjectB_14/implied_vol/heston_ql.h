
//hestonql.h

#ifndef HESTON_QL_H
#define HESTON_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double heston_ql_call(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real underlying,
	Real strike,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility,
	Real kappa,
	Real sigma,
	Real rho);

#endif