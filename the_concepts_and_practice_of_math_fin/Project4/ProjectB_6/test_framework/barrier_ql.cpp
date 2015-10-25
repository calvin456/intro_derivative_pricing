//barrier_ql.cpp
//Wrapper function. Computes semi-analytical heston w/ QuantLib
//ref. barrieroption.cpp

#include "barrier_ql.h"

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
	)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = Actual360();

	Real barrier = barrier_;
	Real rebate = rebate_;

	Handle <Quote > spot(boost::shared_ptr<SimpleQuote>(new SimpleQuote(spot_)));

	Handle<YieldTermStructure> qTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, riskFreeRate, dc)));

	Handle<BlackVolTermStructure> volTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility, dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new BlackScholesMertonProcess(spot, qTS, rTS, volTS));

	boost::shared_ptr<PricingEngine> engine(
		new AnalyticBarrierEngine(stochProcess));

	Option::Type type = Option::Call;

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	BarrierOption option(
		Barrier::DownOut,
		barrier,
		rebate,
		payoff,
		exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}

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
	)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = Actual360();

	Real barrier = barrier_;
	Real rebate = rebate_;

	Handle <Quote > spot(boost::shared_ptr<SimpleQuote>(new SimpleQuote(spot_)));

	Handle<YieldTermStructure> qTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, riskFreeRate, dc)));

	Handle<BlackVolTermStructure> volTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility, dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new BlackScholesMertonProcess(spot, qTS, rTS, volTS));

	boost::shared_ptr<PricingEngine> engine(
		new AnalyticBarrierEngine(stochProcess));

	Option::Type type = Option::Call;

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	BarrierOption option(
		Barrier::DownIn,
		barrier,
		rebate,
		payoff,
		exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}

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
	)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = Actual360();

	Real barrier = barrier_;
	Real rebate = rebate_;

	Handle <Quote > spot(boost::shared_ptr<SimpleQuote>(new SimpleQuote(spot_)));

	Handle<YieldTermStructure> qTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, riskFreeRate, dc)));

	Handle<BlackVolTermStructure> volTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility, dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new BlackScholesMertonProcess(spot, qTS, rTS, volTS));

	boost::shared_ptr<PricingEngine> engine(
		new AnalyticBarrierEngine(stochProcess));


	Option::Type type = Option::Put;

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	BarrierOption option(
		Barrier::DownOut,
		barrier,
		rebate,
		payoff,
		exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}

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
	)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = Actual360();

	Real barrier = barrier_;
	Real rebate = rebate_;

	Handle <Quote > spot(boost::shared_ptr<SimpleQuote>(new SimpleQuote(spot_)));

	Handle<YieldTermStructure> qTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, riskFreeRate, dc)));

	Handle<BlackVolTermStructure> volTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility, dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new BlackScholesMertonProcess(spot, qTS, rTS, volTS));

	boost::shared_ptr<PricingEngine> engine(
		new AnalyticBarrierEngine(stochProcess));


	Option::Type type = Option::Call;

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	BarrierOption option(
		Barrier::UpOut,
		barrier,
		rebate,
		payoff,
		exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}

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
	)
{
	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = Actual360();

	Real barrier = barrier_;
	Real rebate = rebate_;

	Handle <Quote > spot(boost::shared_ptr<SimpleQuote>(new SimpleQuote(spot_)));

	Handle<YieldTermStructure> qTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield, dc)));

	Handle<YieldTermStructure> rTS(boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, riskFreeRate, dc)));

	Handle<BlackVolTermStructure> volTS(boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility, dc)));

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new BlackScholesMertonProcess(spot, qTS, rTS, volTS));

	boost::shared_ptr<PricingEngine> engine(
		new AnalyticBarrierEngine(stochProcess));


	Option::Type type = Option::Put;

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	BarrierOption option(
		Barrier::UpOut,
		barrier,
		rebate,
		payoff,
		exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}