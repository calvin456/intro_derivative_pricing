//jdp_ql.cpp
//Wrapper function. Computes semi-analytical heston w/ QuantLib
//ref. quantlib equity option projeect

#include "jdp_ql.h"

#include <ql/time/daycounters/actual360.hpp>
#include <ql/instruments/europeanoption.hpp>
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp>
#include <ql/pricingengines/vanilla/jumpdiffusionengine.hpp>
#include <ql/processes/merton76process.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/utilities/dataformatters.hpp>

using namespace std;

Real jdp_ql_call(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Real underlying_,
	Real strike_,
	Spread dividendYield_,
	Rate riskFreeRate_,
	Volatility volatility_,
	Real kappa,
	Real m,
	Real nu)
{

	// set up dates
	Calendar calendar = TARGET();
	Date todaysDate = todaysDate_;
	Date settlementDate = settlementDate_;
	Date maturity = maturity_;

	Settings::instance().evaluationDate() = todaysDate_;

	DayCounter dc = ActualActual();

	boost::shared_ptr<SimpleQuote> spot(new SimpleQuote(underlying_));
	
	Handle<Quote> underlyingH(boost::shared_ptr<Quote>(new SimpleQuote(underlying_)));

	Handle<YieldTermStructure> flatTermStructure(
		boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, riskFreeRate_, dc)));
	Handle<YieldTermStructure> flatDividendTS(
		boost::shared_ptr<YieldTermStructure>(
		new FlatForward(settlementDate, dividendYield_, dc)));
	Handle<BlackVolTermStructure> flatVolTS(
		boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(settlementDate, calendar, volatility_,
		dc)));

	boost::shared_ptr<SimpleQuote> jumpIntensity(new SimpleQuote(0.0));
	boost::shared_ptr<SimpleQuote> meanLogJump(new SimpleQuote(0.0));
	boost::shared_ptr<SimpleQuote> jumpVol(new SimpleQuote(0.0));

	

	boost::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));

	boost::shared_ptr<StrikedTypePayoff> payoffCall(new PlainVanillaPayoff(Option::Call, strike_));

	boost::shared_ptr<Merton76Process> stochProcess(
		new Merton76Process(underlyingH,
		flatDividendTS,
		flatTermStructure,
		flatVolTS,
		Handle<Quote>(jumpIntensity),
		Handle<Quote>(meanLogJump),
		Handle<Quote>(jumpVol)));

	boost::shared_ptr<PricingEngine> engine(
		new JumpDiffusionEngine(stochProcess));

	EuropeanOption option(payoffCall, europeanExercise);
	option.setPricingEngine(engine);

	return option.NPV();


}