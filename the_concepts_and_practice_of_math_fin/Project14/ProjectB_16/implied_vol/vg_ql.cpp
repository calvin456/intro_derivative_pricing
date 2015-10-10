//vg_ql.cpp
//Wrapper function. Computes analytical variance-gamma w/ QuantLib
//ref. variancegamma.cpp, test suite ql

#include "vg_ql.h"

using namespace std;

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
	)
{

	// set up dates
	Calendar calendar = TARGET();
	//Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	// our options

	Real underlying = underlying_;
	Real strike = strike_;
	Spread dividendYield = dividendYield_;
	Rate riskFreeRate = riskFreeRate_;
	//Volatility volatility = volatility_;

	//DayCounter dayCounter = ActualActual();
	DayCounter dayCounter = Actual360();

	boost::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));

	Handle<Quote> underlyingH(boost::shared_ptr<Quote>(new SimpleQuote(underlying)));

	// bootstrap the yield/dividend
	Handle<YieldTermStructure> flatTermStructure(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, riskFreeRate, dayCounter)));

	Handle<YieldTermStructure> flatDividendTS(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, dividendYield, dayCounter)));

	boost::shared_ptr<StrikedTypePayoff> payoffCall(new PlainVanillaPayoff(Option::Call, strike));

	// options
	VanillaOption europeanOptionCall(payoffCall, europeanExercise);

	boost::shared_ptr<VarianceGammaProcess> stochProcess(new VarianceGammaProcess(underlyingH, flatDividendTS, flatTermStructure, sigma_, nu_, theta_));

	// Analytic engine
	boost::shared_ptr<PricingEngine> analyticEngine(new VarianceGammaEngine(stochProcess));

	europeanOptionCall.setPricingEngine(analyticEngine);

	return  europeanOptionCall.NPV();
}