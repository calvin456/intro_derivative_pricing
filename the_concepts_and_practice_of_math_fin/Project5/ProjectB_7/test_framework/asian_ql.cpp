//asian_ql.cpp
//Wrapper function. Computes semi-analytical heston w/ QuantLib
//ref. quantlib asianoption.cpp

#include "asian_ql.h"

double asian_geo_call_ql(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real spot_,
	Real strike,
	Size m,
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

	boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new BlackScholesMertonProcess(spot,qTS, rTS, volTS));

	boost::shared_ptr<PricingEngine> engine(
		new AnalyticDiscreteGeometricAveragePriceAsianEngine(stochProcess));

	Average::Type averageType = Average::Geometric;
	Real runningAccumulator = 1.0;
	Size pastFixings = 0;
	Size futureFixings = m;
	Option::Type type = Option::Call;

	boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

	boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));

	std::vector<Date> fixingDates(futureFixings);
	Integer dt = Integer(360 / futureFixings + 0.5);
	fixingDates[0] = todaysDate + dt;
	for (Size j = 1; j<futureFixings; j++)
		fixingDates[j] = fixingDates[j - 1] + dt;

	DiscreteAveragingAsianOption option(averageType, runningAccumulator,
		pastFixings, fixingDates,
		payoff, exercise);

	option.setPricingEngine(engine);

	return option.NPV();
}


