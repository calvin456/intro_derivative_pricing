

//barrier_ql.h

#ifndef BARRIER_QL_H
#define BARRIER_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double do_call_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Real barrier_,
	Real rebate_,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

double di_call_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Real barrier_,
	Real rebate_,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

double do_put_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Real barrier_,
	Real rebate_,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

double uo_call_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Real barrier_,
	Real rebate_,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

double uo_put_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Real barrier_,
	Real rebate_,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	);

#endif