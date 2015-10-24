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

#include <Parameters.h>
#include <Sobol.h>
//#include <AntiThetic.h>

#include<ParametersPWC.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>

#include<PathDependentAsian.h>

#include<ExoticBSEngine.h>


using namespace std;
//using namespace QuantLib;

double absolute_range(5e-02);
double mc_simul_asian_ar_qmc, mc_simul_bb;

//Real ql_asian_ar_qmc, ql_bb;
double ql_asian_ar_qmc, ql_bb;

//Asian Arithmetic
TEST(AsianAritmeticTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_asian_ar_qmc, ql_asian_ar_qmc, absolute_range);
}

//Brownian bridge
TEST(BBTest, AnalyticalvsMC) {
	EXPECT_NEAR(mc_simul_bb, ql_bb, absolute_range);
}



int main(int argc, char **argv) {

	try {
		
		double Spot(100.0);
		double Vol(0.1);
		double r(.05);
		double d(.03);
		double Strike(103.0);
		double Expiry(1.0);
		unsigned long NumberOfDates(52); //12

		/*
		As number of steps grows, perf of model deteriorates
		*/

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, Dec, 2000);

		//Asian

		ql_asian_ar_qmc = asian_arm_call_qmc_ql(todaysDate, settlementDate, maturity, Spot, Strike, NumberOfDates, d, r, Vol);

		RandomSobol generator(NumberOfDates);

		ParametersConstant VolParam(Vol), rParam(r), dParam(d);

		//Assume flat struture for Vol,r, and d
		MJArray times(NumberOfDates);

		for (unsigned long i = 0; i < NumberOfDates; i++)
			times[i] = (i + 1.0)*Expiry / NumberOfDates;

		PathDependentAsian theOption(times, Expiry, PayOffCall(Strike));

		ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, generator, Spot);

		StatisticsMean gatherer_mean;

		ConvergenceTable gatherer(gatherer_mean);

		theEngine.DoSimulation(gatherer, static_cast<unsigned long>(1e6));

		mc_simul_asian_ar_qmc = gatherer.GetResultsSoFar()[19][0];

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