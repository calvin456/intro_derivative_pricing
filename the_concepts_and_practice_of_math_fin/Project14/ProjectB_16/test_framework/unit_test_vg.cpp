// unit_test_heston.cpp

/*
Use google test to validate framework and QuantLib as benchmark.

Do the following test

1. analytical vs mc

2. analytical vs ql analytical

3. ms vs ql analytical

*/

#include "gtest/gtest.h"
#include "vg_ql.h"


#include <VGPricingAnalytical.h>
#include <path_generation_vg.h>
#include <PayOff3.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>
#include <Engine_vg.h>


using namespace std;
using namespace QuantLib;

double absolute_range(5e-02);
double mc_simul;
double analytical;
Real ql_analytical;

TEST(VGTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical, ql_analytical, absolute_range);
}

TEST(VGTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical, mc_simul, absolute_range);
}

TEST(VGTest, MCvsQL) {
	EXPECT_NEAR(mc_simul, ql_analytical, absolute_range);
}

int main(int argc, char **argv) {

	try {

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, March, 2000); 

		ql_analytical = vg_ql_call(todaysDate, settlementDate, maturity, 100.0, 100.0, 0.0, 0.05, .1, .2, 0.0);
		//cout << ql_analytical << endl;
		
		VanillaOptionTemplate<PayOffCall> theOption(PayOffCall(100.0), 0.25);

		ParametersConstant VolParam(.1), rParam(.05), driftParam(.05);

		shared_ptr<RandomBase> generator(new AntiThetic(RandomMersenneTwister(1)));

		unique_ptr<PathGenerationVG> ThePath(new PathGenerationVG(generator, 100.0, .25, driftParam, VolParam, .2, 0.0, static_cast<unsigned long> (1e01)));

		mc_simul = mc_pricer_vg(theOption, rParam, ThePath, static_cast<unsigned long> (1e06));

		analytical = VGVanillaCallAnalytical(100.0, 100.0, .05, .25, .1, .2, 0.0);

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