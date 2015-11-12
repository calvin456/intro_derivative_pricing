//test in-arrear fra
//ref. test suite, swap.cpp, testInArrears() 

//use swap with no reset date. ie price one fra

#include "fwd_in_arrear.h"

namespace{

	struct CommonVars {
		// global data
		Date today, settlement;
		VanillaSwap::Type type;
		Real nominal;
		Rate rate;
		Calendar calendar;
		BusinessDayConvention fixedConvention, floatingConvention;
		Frequency fixedFrequency, floatingFrequency;
		DayCounter fixedDayCount;
		boost::shared_ptr<IborIndex> index;
		Natural settlementDays;
		RelinkableHandle<YieldTermStructure> termStructure;

		// cleanup
		SavedSettings backup;

		CommonVars() {
			type = VanillaSwap::Receiver;
			settlementDays = 2;
			nominal = 1.0;
			fixedConvention = Unadjusted;
			floatingConvention = ModifiedFollowing;
			fixedFrequency = Annual;
			floatingFrequency = Semiannual;
			fixedDayCount = Actual360();
		}

		void makeIndex(Date todaysDate_, Rate rate)
		{

			index = boost::shared_ptr<IborIndex>(new Euribor6M(termStructure));

			calendar = index->fixingCalendar();

			today = calendar.adjust(todaysDate_);

			Settings::instance().evaluationDate() = today;

			settlement = calendar.advance(today, settlementDays, Days);

			boost::shared_ptr<YieldTermStructure> flatRate(new FlatForward(settlement, rate, fixedDayCount));

			termStructure.linkTo(flatRate);
		}

		boost::shared_ptr<Swap> makeSwap(Real start, Real length, Rate fixedRate, Volatility volatility)
		{
			Date startDate = calendar.advance(today, start, Years, floatingConvention);

			Date maturity = calendar.advance(startDate, length * 12, Months, floatingConvention);

			Schedule fixedSchedule(startDate, maturity, Period(fixedFrequency), calendar, fixedConvention, fixedConvention, DateGeneration::Forward, false);

			Schedule floatSchedule(startDate, maturity, Period(floatingFrequency), calendar, floatingConvention, floatingConvention, DateGeneration::Forward, false);

			Leg fixedLeg = FixedRateLeg(fixedSchedule)
				.withNotionals(nominal)
				.withCouponRates(fixedRate, fixedDayCount);

			Handle<OptionletVolatilityStructure> vol(boost::shared_ptr<OptionletVolatilityStructure>(new ConstantOptionletVolatility(startDate, calendar, Following, volatility, fixedDayCount)));

			boost::shared_ptr<IborCouponPricer> pricer(new BlackIborCouponPricer(vol));

			Leg floatingLeg = IborLeg(floatSchedule, index)
				.withNotionals(nominal)
				.withPaymentDayCounter(fixedDayCount)
				.withFixingDays(settlementDays)
				.withGearings(1.0)
				.withSpreads(0.0)
				.inArrears();

			setCouponPricer(floatingLeg, pricer);

			boost::shared_ptr<Swap> swap(new Swap(floatingLeg, fixedLeg));

			swap->setPricingEngine(boost::shared_ptr<PricingEngine>(new DiscountingSwapEngine(termStructure)));

			return swap;
		}


	};

};

double in_arrear_fra(const Date& todaysDate_,
	double start,
	double length,
	Rate spot_,
	Rate strike,
	Volatility volatility
	)

{
	CommonVars vars;

	try{
		vars.makeIndex(todaysDate_, spot_);

		boost::shared_ptr<Swap> swap_ = vars.makeSwap(start,length, strike, volatility) ;
	
		return swap_->NPV();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	
}