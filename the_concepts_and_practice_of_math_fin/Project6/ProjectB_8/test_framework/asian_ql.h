
//asian_ql.h

#ifndef ASIAN_QL_H
#define ASIAN_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double asian_geo_call_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Size m,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

double asian_arm_call_qmc_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Size m,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

#endif