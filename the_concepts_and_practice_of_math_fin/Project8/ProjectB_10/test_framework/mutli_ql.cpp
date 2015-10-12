//jdp_ql.cpp
//Wrapper function. Computes semi-analytical heston w/ QuantLib
//ref. quantlib margrabeoption.cpp & quantooption.cpp

#include "multi_ql.h"

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
	Real rho)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = ActualActual();

	Handle <Quote > spot1(boost::shared_ptr<SimpleQuote> (new SimpleQuote(spot1_)));
	Handle <Quote > spot2(boost::shared_ptr<SimpleQuote>(new SimpleQuote(spot2_)));

	Handle<YieldTermStructure> qTS1(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield1, dc)));

	Handle<YieldTermStructure> qTS2(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield2, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, riskFreeRate1, dc)));

	Handle<BlackVolTermStructure> volTS1(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility1,dc)));
	
	Handle<BlackVolTermStructure> volTS2(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility2,dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess1(new BlackScholesMertonProcess(spot1,
		qTS1,rTS,volTS1));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess2(new BlackScholesMertonProcess(spot2,
		qTS2,rTS,volTS2));

	boost::shared_ptr<PricingEngine> engine(new AnalyticEuropeanMargrabeEngine(stochProcess1,
		stochProcess2,rho));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	MargrabeOption margrabeOption(1, 1, exercise);

	margrabeOption.setPricingEngine(engine);

	return margrabeOption.NPV();
}



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
	)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = ActualActual();

	Handle<Quote> spot(boost::shared_ptr<SimpleQuote> (new SimpleQuote(spot_)));
	
	Handle<YieldTermStructure> qTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(todaysDate, dividendYield, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(todaysDate, riskFreeRate, dc)));

	Handle<BlackVolTermStructure> volTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(todaysDate, calendar, volatility, dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new
		BlackScholesMertonProcess(spot,qTS,rTS,volTS));

	Handle<YieldTermStructure> fxrTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(todaysDate, fxr, dc)));

	Handle<BlackVolTermStructure> fxVolTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(todaysDate, calendar, fxVol, dc)));

	Handle<Quote> correlation(boost::shared_ptr<SimpleQuote> (new SimpleQuote(correlation_)));

	boost::shared_ptr<PricingEngine> engine(new QuantoEngine<VanillaOption, AnalyticEuropeanEngine>(
		stochProcess, fxrTS, fxVolTS,correlation));

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(Option::Call, strike));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	QuantoVanillaOption option(payoff, exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}

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
	)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = ActualActual();

	Handle<Quote> spot(boost::shared_ptr<SimpleQuote>(new SimpleQuote(spot_)));

	Handle<YieldTermStructure> qTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(todaysDate, dividendYield, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(todaysDate, riskFreeRate, dc)));

	Handle<BlackVolTermStructure> volTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(todaysDate, calendar, volatility, dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new
		BlackScholesMertonProcess(spot, qTS, rTS, volTS));

	Handle<YieldTermStructure> fxrTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(todaysDate, fxr, dc)));

	Handle<BlackVolTermStructure> fxVolTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(todaysDate, calendar, fxVol, dc)));

	Handle<Quote> correlation(boost::shared_ptr<SimpleQuote>(new SimpleQuote(correlation_)));

	boost::shared_ptr<PricingEngine> engine(new QuantoEngine<VanillaOption, AnalyticEuropeanEngine>(
		stochProcess, fxrTS, fxVolTS, correlation));

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(Option::Put, strike));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	QuantoVanillaOption option(payoff, exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}