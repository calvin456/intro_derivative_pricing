// unit_test_asian.cpp

/*
Use google test to validate framework and QuantLib as benchmark.

Do the following test

1. analytical vs mc

2. analytical vs ql analytical

3. ms vs ql analytical

*/

#include "gtest/gtest.h"

#include "asian_ql.h"
#include "asian_option.h"

#include "barrier_ql.h"
#include <barrier_options_analytical.h>

#include <Parameters.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>

#include<ParametersPWC.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>

#include<PathDependentAsianGeo.h>

#include<PathDependentDiscrete.h>
#include<PathDependentDiscreteDO.h>
#include<PathDependentDiscreteDI.h>
#include <PathDependentDiscreteKnockOut.h>

#include<ExoticBSEngine.h>


using namespace std;
using namespace QuantLib;

double absolute_range(5e-02);
double mc_simul_asian, mc_simul_doc, mc_simul_dic, mc_simul_dop, mc_simul_dop1, mc_simul_uoc;
double analytical_asian, analytical_doc, analytical_dic, analytical_dop, analytical_dop1, analytical_uoc;
Real ql_analytical_asian, ql_analytical_doc, ql_analytical_dic, ql_analytical_dop, ql_analytical_dop1, ql_analytical_uoc;

//Asian
TEST(AsianGeoTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_asian, ql_analytical_asian, absolute_range);
}

TEST(AsianGeoTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_asian, mc_simul_asian, absolute_range);
}

TEST(AsianGeoTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_asian, ql_analytical_asian, absolute_range);
}
/*
//Both cannot be equal since analytical and ql are continuous barrier

//DOC
TEST(DOCTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_doc, ql_analytical_doc, absolute_range);
}

TEST(DOCTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_doc, mc_simul_doc, absolute_range);
}

TEST(DOCTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_doc, ql_analytical_doc, absolute_range);
}

//DIC
TEST(DICTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_dic, ql_analytical_dic, absolute_range);
}

TEST(DICTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_dic, mc_simul_dic, absolute_range);
}

TEST(DICTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_dic, ql_analytical_dic, absolute_range);
}

//DOP
TEST(DOPTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_dop, ql_analytical_dop, absolute_range);
}

TEST(DOPTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_dop, mc_simul_dop, absolute_range);
}

TEST(DOPTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_dop, ql_analytical_dop, absolute_range);
}

//DOP1
TEST(DOP1Test, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_dop1, ql_analytical_dop1, absolute_range);
}

TEST(DOP1Test, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_dop1, mc_simul_dop1, absolute_range);
}

TEST(DOP1Test, MCvsQL) {
	EXPECT_NEAR(mc_simul_dop1, ql_analytical_dop1, absolute_range);
}

//UOC
TEST(UOCTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_uoc, ql_analytical_uoc, absolute_range);
}

TEST(UOCTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_uoc, mc_simul_uoc, absolute_range);
}

TEST(UOCTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_uoc, ql_analytical_uoc, absolute_range);
}
*/

int main(int argc, char **argv) {

	try {

		double Spot(100.0);
		double Vol(0.1);
		double r(.05);
		double d(.03);
		double Strike(103.0);
		double Expiry(1.0);
		unsigned long NumberOfDates(12);

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, Dec, 2000);

		//Asian

		ql_analytical_asian = asian_geo_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, NumberOfDates, d, r, Vol);

		RandomMersenneTwister generator(NumberOfDates);

		AntiThetic GenTwo(generator);
		
		ParametersConstant VolParam(Vol), rParam(r), dParam(d);

		//Assume flat struture for Vol,r, and d
		MJArray times(NumberOfDates);

		for (unsigned long i = 0; i < NumberOfDates; i++)
			times[i] = (i + 1.0)*Expiry / NumberOfDates;

		PathDependentAsianGeo theOption(times, Expiry, PayOffCall(Strike));

		ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot);

		StatisticsMean gatherer_mean;

		ConvergenceTable gatherer(gatherer_mean);

		theEngine.DoSimulation(gatherer, static_cast<unsigned long>(1e6));

		mc_simul_asian = gatherer.GetResultsSoFar()[19][0];

		analytical_asian = asian_geo_call(Spot, NumberOfDates, Strike, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------
		/*
		double BarrierDown = 80.0;

		//DOC

		ql_analytical_doc = do_call_ql(todaysDate, settlementDate, maturity, Spot, Strike,BarrierDown, 0.0, d, r, Vol);

		PathDependentDiscreteDO theOption1(times, Expiry, BarrierDown, PayOffCall(Strike));

		ExoticBSEngine theEngine1(theOption1, rParam, dParam, VolParam, GenTwo, Spot);

		StatisticsMean gatherer_mean1;

		ConvergenceTable gatherer1(gatherer_mean1);

		theEngine1.DoSimulation(gatherer1, static_cast<unsigned long>(1e6));

		mc_simul_doc = gatherer1.GetResultsSoFar()[19][0];

		analytical_doc = down_out_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//DIC

		ql_analytical_dic = di_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		PathDependentDiscreteDI theOption2(times, Expiry, BarrierDown, PayOffCall(Strike));

		ExoticBSEngine theEngine2(theOption2, rParam, dParam, VolParam, GenTwo, Spot);

		StatisticsMean gatherer_mean2;

		ConvergenceTable gatherer2(gatherer_mean2);

		theEngine2.DoSimulation(gatherer2, static_cast<unsigned long>(1e6));

		mc_simul_dic = gatherer2.GetResultsSoFar()[19][0];

		analytical_dic = down_in_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//DOP

		ql_analytical_dop = do_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		PathDependentDiscreteDO theOption3(times, Expiry, BarrierDown, PayOffPut(Strike));

		ExoticBSEngine theEngine3(theOption3, rParam, dParam, VolParam, GenTwo, Spot);

		StatisticsMean gatherer_mean3;

		ConvergenceTable gatherer3(gatherer_mean3);

		theEngine3.DoSimulation(gatherer3, static_cast<unsigned long>(1e6));

		mc_simul_dop = gatherer3.GetResultsSoFar()[19][0];

		analytical_dop = down_out_put(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//DOP1

		Spot = 140.0;
		double BarrierUp = 120.0;

		ql_analytical_dop1 = do_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		PathDependentDiscreteDO theOption4(times, Expiry, BarrierUp, PayOffPut(Strike));

		ExoticBSEngine theEngine4(theOption4, rParam, dParam, VolParam, GenTwo, Spot);

		StatisticsMean gatherer_mean4;

		ConvergenceTable gatherer4(gatherer_mean4);

		theEngine4.DoSimulation(gatherer4, static_cast<unsigned long>(1e6));

		mc_simul_dop1 = gatherer4.GetResultsSoFar()[19][0];

		analytical_dop1 = down_out_put(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOC

		Spot = 100.0;
		
		ql_analytical_uoc = uo_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		PathDependentDiscreteKnockOut theOption5(times, Expiry, BarrierUp, PayOffCall(Strike));

		ExoticBSEngine theEngine5(theOption5, rParam, dParam, VolParam, GenTwo, Spot);

		StatisticsMean gatherer_mean5;

		ConvergenceTable gatherer5(gatherer_mean5);

		theEngine5.DoSimulation(gatherer5, static_cast<unsigned long>(1e6));

		mc_simul_uoc = gatherer5.GetResultsSoFar()[19][0];

		analytical_uoc = up_out_call(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------
		*/

		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();

	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error" << endl;
		return 1;
	}
}