// unit_test_asian.cpp

/*
Use google test to validate framework and QuantLib as benchmark.

Do the following test

1. analytical vs mc

2. analytical vs ql analytical

3. ms vs ql analytical

*/

#include "gtest/gtest.h"

#include<limits>
#include<cmath>

#include <NumericalIntegration.h>
#include <NumericalRule.h>

#include<MersenneTwister.h>
#include<AntiThetic.h>
#include<Vanilla3.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<payoff_interest_derivatives.h>

#include"MC.h"

#include "libor_in_arrear_fra_analytical.h"
#include "function_to_eval.h"

#include "caplet_in_arrear.h"
#include "fwd_in_arrear.h"

using namespace std;
using namespace QuantLib;

double absolute_range(5e-04);
double analytical_ia_fra;
double num_int_ia_fra, num_int_ia_caplet, num_int_ia_floorlet;
double mc_ia_fra, mc_ia_caplet, mc_ia_floorlet;

Real ql_ia_fra, ql_ia_caplet, ql_ia_floorlet;

//In arrear FRA
TEST(IAFRATest, MCvsQL) {
	EXPECT_NEAR(mc_ia_fra, ql_ia_fra, absolute_range);
}

TEST(IAFRATest, AnalyticalvsQL) {
	EXPECT_NEAR(analytical_ia_fra, ql_ia_fra, absolute_range);
}

TEST(IAFRATest, NumIntvsQL) {
	EXPECT_NEAR(num_int_ia_fra, ql_ia_fra, absolute_range);
}

//In arrear caplet
TEST(IACaplet, MCvsQL) {
	EXPECT_NEAR(mc_ia_caplet, ql_ia_caplet, absolute_range);
}

TEST(IACaplet, NumIntvsQL) {
	EXPECT_NEAR(num_int_ia_caplet, ql_ia_caplet, absolute_range);
}

//In arrear floorlet
TEST(IAFloorlet, MCvsQL) {
	EXPECT_NEAR(mc_ia_floorlet, ql_ia_floorlet, absolute_range);
}

TEST(IAFloorlet, NumIntvsQL) {
	EXPECT_NEAR(num_int_ia_floorlet, ql_ia_floorlet, absolute_range);
}


int main(int argc, char **argv) {

	try {

		double Spot(.06);
		double Vol(0.2);
		
		double Strike(.07);
		double Expiry(.5);
		unsigned long NumberOfDates(12);

		double t0(10);
		double t1(10.5);
		double numeraire(.5);

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(30, Jun, 2000);

		//FRA

		ql_ia_fra = in_arrear_fra(todaysDate, 10, .5, Spot, Strike, Vol);

		analytical_ia_fra = fabs(numeraire * libor_in_arrear_fra(Spot, Strike, Vol, t0, t1));

		FuncToEval myFunc(Spot, Strike, Vol, t0, t1, fwd);

		double Tolerance(1e-6);
		double Low(1.0e-10);
		double High(10.0);
		unsigned long Steps(100);

		Trapezium_rule<FuncToEval> rule(Low, High, myFunc);

		num_int_ia_fra = fabs(numeraire * Numerical_integration<Trapezium_rule, FuncToEval>(Tolerance, Steps, rule));

		unsigned long NumberOfPaths(1000000);

		FRAIA thePayOff(Strike, t0, t1);

		Vanilla::VanillaOption theOption(thePayOff, t1 - t0);

		ParametersConstant VolParam(Vol);

		StatisticsMean gatherer_mean;

		//Generate convergence table
		ConvergenceTable gatherer(gatherer_mean);

		//RandomParkMiller generator(1);
		RandomMersenneTwister generator(1);

		AntiThetic GenTwo(generator);

		SimpleMonteCarloP2(theOption, PC,Spot, t0, t1, VolParam, NumberOfPaths, gatherer, GenTwo);

		std::vector<std::vector<double>>  results = gatherer.GetResultsSoFar();

		mc_ia_fra = fabs(results[results.size() - 1][0]);

		//Caplet

		ql_ia_caplet = in_arrear_caplet(todaysDate,10,.5,Spot,Strike,Vol);

		FuncToEval myFunc1(Spot, Strike, Vol, t0, t1, caplet);

		Trapezium_rule<FuncToEval> rule1(Low, High, myFunc1);

		num_int_ia_caplet = fabs(numeraire * Numerical_integration<Trapezium_rule, FuncToEval>(Tolerance, Steps, rule1));

		CapletIA thePayOff1(Strike, t0, t1);

		Vanilla::VanillaOption theOption1(thePayOff1, t1 - t0);

		//Generate convergence table
		ConvergenceTable gatherer1(gatherer_mean);

		GenTwo.Reset();

		SimpleMonteCarloP2(theOption1, PC,Spot, t0, t1, VolParam, NumberOfPaths, gatherer1, GenTwo);

		std::vector<std::vector<double>>  results1 = gatherer1.GetResultsSoFar();
		
		mc_ia_caplet = results1[results1.size() - 1][0];

		//Floorlet

		ql_ia_floorlet = in_arrear_floorlet(todaysDate, 10, .5, Spot, Strike, Vol);

		FuncToEval myFunc2(Spot, Strike, Vol, t0, t1, floorlet);

		Trapezium_rule<FuncToEval> rule2(Low, High, myFunc2);

		num_int_ia_floorlet = fabs(numeraire * Numerical_integration<Trapezium_rule, FuncToEval>(Tolerance, Steps, rule2));

		FloorletIA thePayOff2(Strike, t0, t1);

		Vanilla::VanillaOption theOption2(thePayOff2, t1 - t0);

		//Generate convergence table
		ConvergenceTable gatherer2(gatherer_mean);

		GenTwo.Reset();

		SimpleMonteCarloP2(theOption2, PC,Spot, t0, t1, VolParam, NumberOfPaths, gatherer2, GenTwo);

		std::vector<std::vector<double>>  results2 = gatherer2.GetResultsSoFar();

		mc_ia_floorlet = results2[results2.size() - 1][0];

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