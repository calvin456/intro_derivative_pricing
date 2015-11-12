//caplet_lmm_ql.h

//ref. test suite, libormarketmodel.cpp

#include "caplet_lmm_ql.h"

namespace {

	boost::shared_ptr<IborIndex> makeIndex(std::vector<Date> dates, std::vector<Rate> rates) {
		DayCounter dayCounter = Actual360();

		RelinkableHandle<YieldTermStructure> termStructure;

		boost::shared_ptr<IborIndex> index(new Euribor6M(termStructure));

		Date todaysDate =
			index->fixingCalendar().adjust(Date(4, September, 2005));
		Settings::instance().evaluationDate() = todaysDate;

		dates[0] = index->fixingCalendar().advance(todaysDate,
			index->fixingDays(), Days);

		termStructure.linkTo(boost::shared_ptr<YieldTermStructure>(
			new ZeroCurve(dates, rates, dayCounter)));

		return index;
	}


	boost::shared_ptr<IborIndex> makeIndex() {
		std::vector<Date> dates;
		std::vector<Rate> rates;
		dates.push_back(Date(4, September, 2005));
		dates.push_back(Date(4, September, 2018));
		rates.push_back(0.039);
		rates.push_back(0.041);

		return makeIndex(dates, rates);
	}


	boost::shared_ptr<OptionletVolatilityStructure> makeCapVolCurve(const Date& todaysDate) {
		Volatility vols[] = { 14.40, 17.15, 16.81, 16.64, 16.17,
			15.78, 15.40, 15.21, 14.86 };

		std::vector<Date> dates;
		std::vector<Volatility> capletVols;
		boost::shared_ptr<LiborForwardModelProcess> process(
			new LiborForwardModelProcess(10, makeIndex()));

		for (Size i = 0; i < 9; ++i) {
			capletVols.push_back(vols[i] / 100);
			dates.push_back(process->fixingDates()[i + 1]);
		}

		return boost::shared_ptr<CapletVarianceCurve>(
			new CapletVarianceCurve(todaysDate, dates,
			capletVols, Actual360()));
	}

}


double caplet_lmm(const Date& todaysDate_,
	const Date& settlementDate_,
	const Date& maturity_,
	Rate spot_,
	Rate strike,
	Rate Numeraire, //zero-coupon bond
	//Volatility volatility

	double correl,
	double a,
	double b,
	double c,
	double d
	)

{

	//SavedSettings backup;

	const Size size = 10;

	#if defined(QL_USE_INDEXED_COUPON)
		const Real tolerance = 1e-5;
	#else
		const Real tolerance = 1e-12;
	#endif

	boost::shared_ptr<IborIndex> index = makeIndex();

	boost::shared_ptr<LiborForwardModelProcess> process(new LiborForwardModelProcess(size, index));

	// set-up pricing engine
	const boost::shared_ptr<OptionletVolatilityStructure> capVolCurve = makeCapVolCurve(Settings::instance().evaluationDate());

	Array variances = LfmHullWhiteParameterization(process, capVolCurve).covariance(0.0).diagonal();

	boost::shared_ptr<LmVolatilityModel> volaModel(new LmFixedVolatilityModel(Sqrt(variances),process->fixingTimes()));

	boost::shared_ptr<LmCorrelationModel> corrModel(new LmExponentialCorrelationModel(size, correl));

	boost::shared_ptr<AffineModel> model(new LiborForwardModel(process, volaModel, corrModel));

	const Handle<YieldTermStructure> termStructure = process->index()->forwardingTermStructure();

	boost::shared_ptr<AnalyticCapFloorEngine> engine1(new AnalyticCapFloorEngine(model, termStructure));

	boost::shared_ptr<Cap> cap1(new Cap(process->cashFlows(),std::vector<Rate>(size, strike)));

	cap1->setPricingEngine(engine1);

	return cap1->NPV();

}
