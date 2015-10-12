// unit_test_heston.cpp

/*
Use google test to validate framework and QuantLib as benchmark.

Do the following test

1. analytical vs mc

2. analytical vs ql analytical

3. ms vs ql analytical

*/

#include "gtest/gtest.h"

#include "multi_ql.h"
#include <quanto_margrabe.h>

#include <path_generation_multi.h>
#include <PayOffMulti.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>
#include <engine_multi.h>


using namespace std;
using namespace QuantLib;

double absolute_range(5e-02);
double mc_simul_margrabe,mc_simul_quanto_call,mc_simul_quanto_put;
double analytical_margrabe, analytical_quanto_call, analytical_quanto_put;
Real ql_analytical_margrabe, ql_analytical_quanto_call, ql_analytical_quanto_put;

TEST(MargrabeTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_margrabe, ql_analytical_margrabe, absolute_range);
}

TEST(MargrabeTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_margrabe, mc_simul_margrabe, absolute_range);
}

TEST(MargrabeTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_margrabe, ql_analytical_margrabe, absolute_range);
}

TEST(QuantoCallTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_quanto_call, ql_analytical_quanto_call, absolute_range);
}

TEST(QuantoCallTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_quanto_call, mc_simul_quanto_call, absolute_range);
}

TEST(QuantoCallTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_quanto_call, ql_analytical_quanto_call, absolute_range);
}

TEST(QuantoPutTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_quanto_put, ql_analytical_quanto_put, absolute_range);
}

TEST(QuantoPutTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical_quanto_put, mc_simul_quanto_put, absolute_range);
}

TEST(QuantoPutTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_quanto_put, ql_analytical_quanto_put, absolute_range);
}


int main(int argc, char **argv) {

	try {

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, March, 2000);

		//Quanto call 

		ql_analytical_quanto_call = quanto_ql_call(todaysDate, settlementDate, maturity, 100.0, 100.0, 0.0, 0.05, 0.06, .20, .30, -.50);

		VanillaOptionTemplate<QuantoCall> theOption(QuantoCall(100.0), .25);

		shared_ptr<RandomBase> generator(new RandomMersenneTwister(2));

		MJArray Spot0(2);
		Spot0[0] = 100.0;
		Spot0[1] = 1.0;

		MJArray  r0(2);
		r0[0] = .05;
		r0[1] = .06;

		matrix<double> cov(2, 2);
		cov(0, 0) = .20 * .20;
		cov(1, 1) = .30 * .30;
		cov(1, 0) = .20 * .30 * -.50;
		cov(0, 1) = cov(1, 0);

		unique_ptr<PathGenerationMulti> ThePaths(new PathGenerationMulti(generator, Spot0, .25, r0, 1, cov));

		mc_simul_quanto_call = mc_pricer_multi(theOption, ParametersConstant(.05), ThePaths, static_cast<unsigned long> (1e6));

		analytical_quanto_call = QuantCallOption(100.0, 100.0, .05, .06, 0.0, .20, .30, -.50, .25);

		//Quanto put 

		ql_analytical_quanto_put = quanto_ql_put(todaysDate, settlementDate, maturity, 100.0, 100.0, 0.0, 0.05, 0.06, .20, .30, -.50);

		VanillaOptionTemplate<QuantoPut> theOption1(QuantoPut(100.0), .25);

		generator->Reset();

		mc_simul_quanto_put = mc_pricer_multi(theOption1, ParametersConstant(.05), ThePaths, static_cast<unsigned long> (1e6));

		analytical_quanto_put = QuantPutOption(100.0, 100.0, 0.05, .06, 0.00, .20, .30, -.50, .25);

		//Margrabe option

		ql_analytical_margrabe = margrabe_ql(todaysDate, settlementDate, maturity, 100.0, 90.0, 0.0, 0.05, 0.0, 0.05, .20, .25, -.5);

		//ExchangeOption thePayOff;
		VanillaOptionTemplate<ExchangeOption> theOption2(ExchangeOption(), .25);

		generator->Reset();

		MJArray Spot1(2);
		Spot1[0] = 100.0;
		Spot1[1] = 90.0;

		MJArray  r1(2);
		r1[0] = .05;
		r1[1] = .05;

		matrix<double> cov1(2, 2);
		cov1(0, 0) = .20 * .20;
		cov1(1, 1) = .25 * .25;
		cov1(1, 0) = .20 * .25 *  - .50;
		cov1(0, 1) = cov1(1, 0);

		unique_ptr<PathGenerationMulti> ThePaths1(new PathGenerationMulti(generator, Spot1, .25, r1, 1, cov1));

		mc_simul_margrabe = mc_pricer_multi(theOption2, ParametersConstant(.05), ThePaths1, static_cast<unsigned long> (1e6));

		analytical_margrabe = MargrabeOptions(100.0, 90.0, .20, .25, -.5, .25);

		//-----------------------------------------------------------------------------------------------

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