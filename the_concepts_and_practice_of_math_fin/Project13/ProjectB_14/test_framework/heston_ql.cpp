//hestonql.cpp
//Wrapper function. Computes semi-analytical heston w/ QuantLib
//ref. quantlib equity option projeect

#include "heston_ql.h"

using namespace std;

Real heston_ql_call(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real underlying_,
	Real strike_,
	Spread dividendYield_,
	Rate riskFreeRate_,
	Volatility volatility_,
	Real kappa_,
	Real sigma_,
	Real rho_)
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
	Volatility volatility = volatility_;

	DayCounter dayCounter = ActualActual();

	boost::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));

	Handle<Quote> underlyingH(boost::shared_ptr<Quote>(new SimpleQuote(underlying)));

	// bootstrap the yield/dividend
	Handle<YieldTermStructure> flatTermStructure(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, riskFreeRate, dayCounter)));

	Handle<YieldTermStructure> flatDividendTS(boost::shared_ptr<YieldTermStructure>(new FlatForward(settlementDate, dividendYield, dayCounter)));

	boost::shared_ptr<StrikedTypePayoff> payoffCall(new PlainVanillaPayoff(Option::Call, strike));

	// options
	VanillaOption europeanOptionCall(payoffCall, europeanExercise);

	// Analytic formulas:
	// semi-analytic Heston for European
	//Cannot set kappa to 0. Gen exception

	Real v0 = volatility*volatility, kappa = kappa_, theta = v0, sigma = sigma_, rho = rho_;
	boost::shared_ptr < HestonProcess > hestonProcess(new HestonProcess(flatTermStructure, flatDividendTS, underlyingH, v0, kappa, theta, sigma, rho));

	boost::shared_ptr<HestonModel> hestonModel(new HestonModel(hestonProcess));

	europeanOptionCall.setPricingEngine(boost::shared_ptr<PricingEngine>(new AnalyticHestonEngine(hestonModel)));

	return  europeanOptionCall.NPV();
}