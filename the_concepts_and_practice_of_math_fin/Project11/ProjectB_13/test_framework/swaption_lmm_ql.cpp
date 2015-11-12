//swaption_lmm_ql.cpp

//ref. test suite, libormarketmodel.cpp

#include "swaption_lmm_ql.h"

namespace {

	struct CommonVars{
		//global data
		Size size; // { 1, 2, 5, 10, 20 };

		BusinessDayConvention fixedConvention, floatingConvention;
		Frequency  fixedFrequency, floatingFrequency;
		Natural settlementDays;
		RelinkableHandle<YieldTermStructure> termStructure;
		DayCounter dayCounter;
		Date todaysDate, settlementDate;
		Calendar calendar; 
		VanillaSwap::Type type;

		boost::shared_ptr<IborIndex> index;

		boost::shared_ptr<LiborForwardModelProcess> process;

		void makeIndex(std::vector<Date> dates, std::vector<Rate> rates) {

			index = boost::shared_ptr<IborIndex>(new Euribor(Period(floatingFrequency), termStructure));

			todaysDate = index->fixingCalendar().adjust(dates[0]);

			Settings::instance().evaluationDate() = todaysDate;

			dates[0] = index->fixingCalendar().advance(todaysDate, index->fixingDays(), Days);

			termStructure.linkTo(boost::shared_ptr<YieldTermStructure>(new ZeroCurve(dates, rates, dayCounter)));

			calendar = index->fixingCalendar();

			settlementDate = calendar.advance(todaysDate, settlementDays, Days);

			process = boost::shared_ptr<LiborForwardModelProcess>(new LiborForwardModelProcess(size, index));
		}

		boost::shared_ptr<LiborForwardModel> makeModel(Real a, Real b, Real c, Real d, Real correl){

			boost::shared_ptr<LmCorrelationModel> corrModel(new LmExponentialCorrelationModel(size, correl));

			boost::shared_ptr<LmVolatilityModel> volaModel(new LmLinearExponentialVolatilityModel(process->fixingTimes(), a, b, c, d));

			process->setCovarParam(boost::shared_ptr<LfmCovarianceParameterization>(new LfmCovarianceProxy(volaModel, corrModel)));

			return boost::shared_ptr<LiborForwardModel>(new LiborForwardModel(process, volaModel, corrModel));

		}

		boost::shared_ptr<VanillaSwap> makeSwap(Size start,Rate strike) {

			Date startDate = calendar.advance(settlementDate, start, Years, floatingConvention);
			
			Date maturity = calendar.advance(startDate, size, Years, floatingConvention);

			Schedule fixedSchedule(startDate, maturity, Period(fixedFrequency), calendar, fixedConvention, fixedConvention, DateGeneration::Forward, false);

			Schedule floatSchedule(startDate, maturity, Period(floatingFrequency), calendar, floatingConvention, floatingConvention, DateGeneration::Forward, false);

			boost::shared_ptr<VanillaSwap> swap(new VanillaSwap(type, 1.0, fixedSchedule, strike, dayCounter, floatSchedule, index, 0.0, index->dayCounter()));
			
			// set-up pricing engine
			swap->setPricingEngine(boost::shared_ptr<PricingEngine>(new DiscountingSwapEngine(termStructure)));

			return swap;
		}

		boost::shared_ptr<Swaption> makeSwaption(const boost::shared_ptr<VanillaSwap>& swap, boost::shared_ptr<LiborForwardModel>& liborModel) {

			boost::shared_ptr<PricingEngine> engine(new LfmSwaptionEngine(liborModel, index->forwardingTermStructure()));

			boost::shared_ptr<Exercise> exercise(new EuropeanExercise(process->fixingDates()[1]));

			boost::shared_ptr<Swaption> swaption(new Swaption(swap, exercise));

			swaption->setPricingEngine(engine);

			return swaption;
		}

		CommonVars(Size length){

			size = length; // { 1, 2, 5, 10, 20 };

			fixedConvention = Unadjusted;
			floatingConvention = ModifiedFollowing;
			fixedFrequency = Annual;
			floatingFrequency = Semiannual;

			settlementDays = 2;
			
			dayCounter = Actual360();
			type = VanillaSwap::Receiver;
		}

	};

}

//Compute price of European swaption using LMM
double swaption_lmm(const Date& todaysDate_,
	unsigned long start,
	unsigned long length,
	Rate spot,
	Rate strike,
	double correl,
	double a,
	double b,
	double c,
	double d
	)
{
	//5-yr semi-annual swap

	CommonVars vars(length);

	std::vector<Date> dates;
	std::vector<Rate> rates;

	dates.push_back(todaysDate_);
	dates.push_back(todaysDate_ + (length + 1)* Years); 
	rates.push_back(spot);
	rates.push_back(spot);

	try {

		vars.makeIndex(dates, rates);

		boost::shared_ptr<LiborForwardModel> liborModel_ = vars.makeModel(a,b,c,d,correl);

		boost::shared_ptr<VanillaSwap> swap_ = vars.makeSwap(start,strike);

		boost::shared_ptr<Swaption> swaption_ = vars.makeSwaption(swap_, liborModel_);

		return swaption_->NPV();

	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

//Compute implied volatility for European swaption using Black model
double swaption_iv_lmm(const Date& todaysDate_,
	unsigned long start,
	unsigned long length,
	Real price,
	Rate spot,
	Rate strike,
	double correl,
	double a,
	double b,
	double c,
	double d
	)
{
	//5-yr semi-annual swap

	CommonVars vars(length);

	std::vector<Date> dates;
	std::vector<Rate> rates;

	dates.push_back(todaysDate_);
	dates.push_back(todaysDate_ + (length + 1)* Years);
	rates.push_back(spot);
	rates.push_back(spot);

	try {

		vars.makeIndex(dates, rates);

		boost::shared_ptr<LiborForwardModel> liborModel_ = vars.makeModel(a, b, c, d, correl);

		boost::shared_ptr<VanillaSwap> swap_ = vars.makeSwap(start,strike);

		boost::shared_ptr<Swaption> swaption_ = vars.makeSwaption(swap_, liborModel_);

		return swaption_->impliedVolatility(price, vars.termStructure, 1.0);

	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}