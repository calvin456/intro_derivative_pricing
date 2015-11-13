// implied_vol_ql.cpp
//Wrapper function. Computes implied vol w/ QuantLib

#include "implied_vol_ql.h"

using namespace std;

double implied_vol_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real underlying,
	Real strike,
	Real px,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	)
{

	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	boost::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));

	Handle<Quote> underlyingH(boost::shared_ptr<Quote>(new SimpleQuote(underlying)));

	Calendar calendar = TARGET();
	DayCounter dayCounter = ActualActual();

	// bootstrap the yield/dividend/vol curves
	Handle<YieldTermStructure> flatTermStructure(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, riskFreeRate, dayCounter)));

	Handle<YieldTermStructure> flatDividendTS(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, dividendYield, dayCounter)));

	Handle<BlackVolTermStructure> flatVolTS(boost::shared_ptr<BlackVolTermStructure>(new BlackConstantVol(settlementDate, calendar, volatility, dayCounter)));

	boost::shared_ptr<StrikedTypePayoff> payoffCall(new PlainVanillaPayoff(Option::Call, strike));

	// options
	VanillaOption europeanOptionCall(payoffCall, europeanExercise);


	Handle < BlackVolTermStructure > volHandle(flatVolTS);
	boost::shared_ptr < BlackScholesMertonProcess > bsmProcess(
		new BlackScholesMertonProcess(underlyingH, flatTermStructure, flatDividendTS, volHandle));

	return europeanOptionCall.impliedVolatility(px, bsmProcess,1.0e-4,100,1.0e-7,10.0);

}