// unit_test_heston.cpp

/*
Use google test to validate framework and QuantLib as benchmark.

Do the following test

1. analytical vs mc

2. analytical vs ql analytical

3. ms vs ql analytical

*/

#include "gtest/gtest.h"
#include "heston_ql.h"
#include <HestonPricingAnalytical.h>
#include <path_generation_heston.h>
#include <PayOff3.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>
#include <engine_heston.h>


using namespace std;
using namespace QuantLib;

double absolute_range(5e-02);
double mc_simul;
double analytical;
Real ql_analytical;

TEST(HestonTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical, ql_analytical, absolute_range);
}

TEST(HestonTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical, mc_simul, absolute_range);
}

TEST(HestonTest, MCvsQL) {
	EXPECT_NEAR(mc_simul, ql_analytical, absolute_range);
}

int main(int argc, char **argv) {

	try {

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, March, 2000);

		//Do not set-up kappa to zero. This will lead to execution failure.
		ql_analytical = heston_ql_call(todaysDate, settlementDate, maturity, 100.0, 100.0, 0.0, 0.05, 0.1, 1e-08, 0.05, 0.0);

		VanillaOptionTemplate<PayOffCall> theOption(PayOffCall(100.0), 0.25);

		ParametersConstant VolParam(.1), rParam(.05), driftParam(.05);

		shared_ptr<RandomBase> generator(new AntiThetic(RandomMersenneTwister(1)));

		unique_ptr<PathGenerationHeston> ThePath(new PathGenerationHeston(generator, 100.0, .25, driftParam, VolParam, static_cast<unsigned long>(1e01), 0.0, 0.0, 0.05));

		mc_simul = mc_pricer_heston(theOption, rParam, ThePath, static_cast<unsigned long> (1e06));

		analytical = HestonVanillaCalltAnalytical(ParametersHeston(0.05, 100.0, .1, 0.05, 0, 0.1, .05, 0, 100.0, .25));

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