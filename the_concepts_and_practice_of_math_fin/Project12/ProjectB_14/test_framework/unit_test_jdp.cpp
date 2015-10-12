// unit_test_heston.cpp

/*
Use google test to validate framework and QuantLib as benchmark.

Do the following test

1. analytical vs mc

2. analytical vs ql analytical

3. ms vs ql analytical

*/

#include "gtest/gtest.h"
#include "jdp_ql.h"
#include <analytical_jdm_pricer.h>
#include <options.h>
#include <path_generation_jdp.h>
#include <PayOff3.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>
#include <engine_jdp.h>


using namespace std;
using namespace QuantLib;

double absolute_range(5e-02);
double mc_simul;
double analytical;
Real ql_analytical;

TEST(JDPTest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical, ql_analytical, absolute_range);
}

TEST(JDPTest, AnalyticalvsMC) {
	EXPECT_NEAR(analytical, mc_simul, absolute_range);
}

TEST(JDPTest, MCvsQL) {
	EXPECT_NEAR(mc_simul, ql_analytical, absolute_range);
}

int main(int argc, char **argv) {

	try {

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, March, 2000);

		ql_analytical = jdp_ql_call(todaysDate, settlementDate, maturity, 100.0, 100.0, 0.0, 0.05, 0.1, .2, 0.9, 0.1);

		VanillaOptionTemplate<PayOffCall> theOption(PayOffCall(100.0), 0.25);

		ParametersConstant VolParam(.1), rParam(.05), driftParam(.05);

		shared_ptr<RandomBase> generator(new AntiThetic(RandomMersenneTwister(1)));

		unique_ptr<PathGenerationJDP> ThePath(new PathGenerationJDP(generator, 100.0, .25, driftParam, VolParam, .2, .9, .1, 1));

		mc_simul = mc_pricer_jdp(theOption, rParam, ThePath, static_cast<unsigned long> (1e06));

		MyOption::CallOption*  call = new MyOption::CallOption(100.0, 100.0, .05, 0, .1, .25);

		double Spot(100.0);
		double Strike(100.0);
		double r(0.05);
		double d(0.0);
		double Vol(.1);
		double kappa(0.2);
		double m(.9);
		double nu(.1);
		double Expiry(.25);

		analytical = analytical_jdm_pricer(Spot, Strike, r, d, Vol, Expiry, kappa, m, nu, call);

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