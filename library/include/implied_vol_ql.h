// implied_vol_ql.h

#ifndef IMPLIED_VOL_QL_H
#define IMPLIED_VOL_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;


double implied_vol_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real underlying,
	Real strike,
	Real px,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

#endif