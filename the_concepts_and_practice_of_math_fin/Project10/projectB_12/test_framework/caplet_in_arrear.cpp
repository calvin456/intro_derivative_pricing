//test in-arrear caplet
//ref. test suite, capfloor.cpp, testInArrears() 

//use cap with no reset date. ie price one single optionlet

/*
--------------------------------------------------------------
Does not work properly. Not possible to price in arrear product.

*/


#include "caplet_in_arrear.h"

namespace{

	struct CommonVars {
		// common data
		Date today, settlement;
		std::vector<Real> nominals;
		BusinessDayConvention fixedConvention, floatingConvention;
		Frequency fixedFrequency, floatingFrequency;
		boost::shared_ptr<IborIndex> index;
		DayCounter dayCounter;
		Calendar calendar;
		Natural fixingDays;
		RelinkableHandle<YieldTermStructure> termStructure;

		// cleanup
		SavedSettings backup;

		// setup
		CommonVars() : nominals(1, 1)
		{
			dayCounter = Actual365Fixed();
			fixedConvention = Unadjusted;
			floatingConvention = ModifiedFollowing;
			fixedFrequency = Annual;
			floatingFrequency = Semiannual;
			fixingDays = 2;
		}

		void makeIndex(Date todaysDate_, Rate rate)
		{
			index = boost::shared_ptr<IborIndex>(new Euribor6M(termStructure));

			calendar = index->fixingCalendar();

			today = calendar.adjust(todaysDate_);

			Settings::instance().evaluationDate() = today;

			settlement = calendar.advance(today, fixingDays, Days);

			boost::shared_ptr<YieldTermStructure> flatRate(new FlatForward(settlement, rate, dayCounter));

			termStructure.linkTo(flatRate);
		}

		// utilities
		Leg makeLeg(Integer start, Real length)
		{
			Date startDate = calendar.advance(today, start, Years, floatingConvention);

			Date endDate = calendar.advance(startDate, length * 12,Months, floatingConvention);

			Schedule floatSchedule(startDate, endDate, Period(floatingFrequency), calendar, floatingConvention, floatingConvention, DateGeneration::Forward, false);

			return IborLeg(floatSchedule, index)
				.withNotionals(nominals)
				.withPaymentDayCounter(dayCounter)
				.withPaymentAdjustment(floatingConvention)
				.withFixingDays(fixingDays)
				.withGearings(1.0)
				.withSpreads(0.0);
				//.inArrears(); //in arrear 
		}

		boost::shared_ptr<PricingEngine> makeEngine(Volatility volatility)
		{
			Handle<Quote> vol(boost::shared_ptr<Quote>(new SimpleQuote(volatility)));

			return boost::shared_ptr<PricingEngine>(new BlackCapFloorEngine(termStructure, vol));
		}

		boost::shared_ptr<CapFloor> makeCapFloor(CapFloor::Type type,
			const Leg& leg,
			Rate strike,
			Volatility volatility)
		{
			boost::shared_ptr<CapFloor> result;

			switch (type) {
			case CapFloor::Cap:
				result = boost::shared_ptr<CapFloor>(new Cap(leg, std::vector<Rate>(1, strike)));
				break;
			case CapFloor::Floor:
				result = boost::shared_ptr<CapFloor>(new Floor(leg, std::vector<Rate>(1, strike)));
				break;
			default:
				QL_FAIL("unknown cap/floor type");
			}
			result->setPricingEngine(makeEngine(volatility));

			return result;
		}

	};

};

double in_arrear_caplet(const Date& todaysDate_,
	double start,
	double length,
	Rate spot_,
	Rate strike,
	Volatility volatility
	)
{
	CommonVars vars;
	
	try{
		vars.makeIndex(todaysDate_,spot_);
	
		Leg leg = vars.makeLeg(start,length);

		boost::shared_ptr<Instrument> cap = vars.makeCapFloor(CapFloor::Cap, leg, strike, volatility);
	
		return cap->NPV();	
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

double in_arrear_floorlet(const Date& todaysDate_,
	double start,
	double length,
	Rate spot_,
	Rate strike,
	Volatility volatility
	)
{
	CommonVars vars;

	try{
		vars.makeIndex(todaysDate_,spot_);
	
		Leg leg = vars.makeLeg(start,length);

		boost::shared_ptr<Instrument> floor = vars.makeCapFloor(CapFloor::Floor, leg, strike, volatility);
	
		return floor->NPV();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}