
//american_ql.h

//American put option priced through LS algo


#ifndef AMERICAN_QL_H
#define AMERICAN_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double am_put_ls_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

#endif