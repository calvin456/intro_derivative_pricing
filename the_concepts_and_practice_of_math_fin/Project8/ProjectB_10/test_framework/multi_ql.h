
//multi_ql.h

#ifndef HESTON_QL_H
#define HESTON_QL_H

#include <ql\quantlib.hpp>

using namespace QuantLib;

double margrabe_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot1_,
	Real spot2_,
	Spread dividendYield1,
	Rate riskFreeRate1,
	Spread dividendYield2,
	Rate riskFreeRate2,
	Volatility volatility1,
	Volatility volatility2,
	Real rho);

double quanto_ql_call(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Spread dividendYield,
	Rate riskFreeRate,
	Spread fxr, 
	Volatility volatility,
	Volatility fxVol,
	Real correlation_
	);

double quanto_ql_put(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Spread dividendYield,
	Rate riskFreeRate,
	Spread fxr,
	Volatility volatility,
	Volatility fxVol,
	Real correlation_
	);


#endif