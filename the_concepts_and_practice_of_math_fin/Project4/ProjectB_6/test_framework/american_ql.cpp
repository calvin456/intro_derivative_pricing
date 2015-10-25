//american_ql.cpp
//Wrapper function. 
//ref. equityoption.cpp

#include "american_ql.h"

double am_put_ls_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Spread dividendYield,
	Rate riskFreeRate,
	Volatility volatility
	)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = Actual360();

	Handle <Quote > spot(boost::shared_ptr<SimpleQuote>(new SimpleQuote(spot_)));

	Handle<YieldTermStructure> qTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, riskFreeRate, dc)));

	Handle<BlackVolTermStructure> volTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility, dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new BlackScholesMertonProcess(spot, qTS, rTS, volTS));

	Size mcSeed = 42;

	boost::shared_ptr<PricingEngine> engine;
	engine = MakeMCAmericanEngine<PseudoRandom>(stochProcess)
		.withSteps(100)
		.withAntitheticVariate()
		.withCalibrationSamples(4096)
		.withAbsoluteTolerance(0.02)
		.withSeed(mcSeed);

	Option::Type type = Option::Put;

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

	boost::shared_ptr<Exercise> exercise(new AmericanExercise(settlementDate, maturity));

	VanillaOption option(payoff, exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}