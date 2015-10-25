// unit_test_barrier.cpp

/*
Use google test to validate framework and QuantLib as benchmark.

Do the following test

1. analytical vs mc

2. analytical vs ql analytical

3. ms vs ql analytical

*/

#include "gtest/gtest.h"

#include "barrier_ql.h"
#include "american_ql.h"
#include <barrier_options_analytical.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <engine_ls.h>
#include <path_generation_gbm.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>

#include <TrinomialTree.h>
#include <TreeAmerican.h>
#include <TreeBarrier.h>
#include <BarrierOption.h>

using namespace std;
using namespace QuantLib;

double absolute_range(5e-02);

//test American put ls
double mc_simul_am_ls;
Real ql_am_put_ls;
double tree_am;

//test case barrier < strike

double tree_doc1, tree_dop1, tree_uoc1, tree_uop1;
double analytical_doc1, analytical_dop1, analytical_uoc1, analytical_uop1;
Real ql_analytical_doc1, ql_analytical_dop1, ql_analytical_uoc1, ql_analytical_uop1;

//test case barrier > strike

double tree_doc2, tree_dop2, tree_uoc2, tree_uop2;
double analytical_doc2, analytical_dop2, analytical_uoc2, analytical_uop2;
Real ql_analytical_doc2, ql_analytical_dop2, ql_analytical_uoc2, ql_analytical_uop2;

//-----------------------------------------------------------------------------

//test American put

TEST(AmericanTest, MCvsQL) {
	EXPECT_NEAR(mc_simul_am_ls, ql_am_put_ls, absolute_range);
}

TEST(AmericanTest, TreevsMC) {
	EXPECT_NEAR(tree_am, mc_simul_am_ls, absolute_range);
}

TEST(AmericanTest, TreevsQL) {
	EXPECT_NEAR(tree_am, ql_am_put_ls, absolute_range);
}

//test case barrier < strike

//DOC

TEST(DOCTestBelow, AnalyticalvsQLBelow) {
	EXPECT_NEAR(analytical_doc1, ql_analytical_doc1, absolute_range);
}

TEST(DOCTestBelow, AnalyticalvsTreeBelow) {
	EXPECT_NEAR(analytical_doc1, tree_doc1, absolute_range);
}

TEST(DOCTestBelow, TreevsQLBelow) {
	EXPECT_NEAR(tree_doc1, ql_analytical_doc1, absolute_range);
}

//DOP
TEST(DOPTestBelow, AnalyticalvsQLBelow) {
	EXPECT_NEAR(analytical_dop1, ql_analytical_dop1, absolute_range);
}

TEST(DOPTestBelow, AnalyticalvsTreeBelow) {
	EXPECT_NEAR(analytical_dop1, tree_dop1, absolute_range);
}

TEST(DOPTestBelow, TreevsQLBelow) {
	EXPECT_NEAR(tree_dop1, ql_analytical_dop1, absolute_range);
}

//UOC
TEST(UOCTestBelow, AnalyticalvsQLBelow) {
	EXPECT_NEAR(analytical_uoc1, ql_analytical_uoc1, absolute_range);
}

TEST(UOCTestBelow, AnalyticalvsTreeBelow) {
	EXPECT_NEAR(analytical_uoc1, tree_uoc1, absolute_range);
}

TEST(UOCTestBelow, TreevsQLBelow) {
	EXPECT_NEAR(tree_uoc1, ql_analytical_uoc1, absolute_range);
}

//UOP
TEST(UOPTestBelow, AnalyticalvsQLBelow) {
	EXPECT_NEAR(analytical_uop1, ql_analytical_uop1, absolute_range);
}

TEST(UOPTestBelow, AnalyticalvsTreeBelow) {
	EXPECT_NEAR(analytical_uop1, tree_uop1, absolute_range);
}

TEST(UOPTestBelow, TreevsQLBelow) {
	EXPECT_NEAR(tree_uop1, ql_analytical_uop1, absolute_range);
}

//-----------------------------------------------------------------------------------

//test case barrier > strike

//DOC

TEST(DOCTestAbove, AnalyticalvsQLAbove) {
	EXPECT_NEAR(analytical_doc2, ql_analytical_doc2, absolute_range);
}

TEST(DOCTestAbove, AnalyticalvsTreeAbove) {
	EXPECT_NEAR(analytical_doc2, tree_doc2, absolute_range);
}

TEST(DOCTestAbove, TreevsQLAbove) {
	EXPECT_NEAR(tree_doc2, ql_analytical_doc2, absolute_range);
}

//DOP
TEST(DOPTestAbove, AnalyticalvsQLAbove) {
	EXPECT_NEAR(analytical_dop2, ql_analytical_dop2, absolute_range);
}

TEST(DOPTestAbove, AnalyticalvsTreeAbove) {
	EXPECT_NEAR(analytical_dop2, tree_dop2, absolute_range);
}

TEST(DOPTestAbove, TreevsQLAbove) {
	EXPECT_NEAR(tree_dop2, ql_analytical_dop2, absolute_range);
}

//UOC
TEST(UOCTestAbove, AnalyticalvsQLAbove) {
	EXPECT_NEAR(analytical_uoc2, ql_analytical_uoc2, absolute_range);
}

TEST(UOCTestAbove, AnalyticalvsTreeAbove) {
	EXPECT_NEAR(analytical_uoc2, tree_uoc2, absolute_range);
}

TEST(UOCTestAbove, TreevsQLAbove) {
	EXPECT_NEAR(tree_uoc2, ql_analytical_uoc2, absolute_range);
}

//UOP
TEST(UOPTestAbove, AnalyticalvsQLAbove) {
	EXPECT_NEAR(analytical_uop2, ql_analytical_uop2, absolute_range);
}

TEST(UOPTestAbove, AnalyticalvsTreeAbove) {
	EXPECT_NEAR(analytical_uop2, tree_uop2, absolute_range);
}

TEST(UOPTestAbove, TreevsQLAbove) {
	EXPECT_NEAR(tree_uop2, ql_analytical_uop2, absolute_range);
}

int main(int argc, char **argv) {

	try {

		double Spot(100.0); //120
		double Vol(0.1);
		double r(.05);
		double d(.00);
		double Strike(100.0);
		double Expiry(2.0);
	

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, Dec, 2001);

		//-----------------------------------------------------------------------------------------------
		//ATM option fails benchmark test w/ QL while OTM comes close.
		ql_am_put_ls = am_put_ls_ql(todaysDate, settlementDate, maturity, Spot, Strike, d, r, Vol);

		unsigned long M(static_cast<unsigned long>(1e04)) ,N(static_cast<unsigned long>(1e02)); 

		PayOffPut put(Strike);

		VanillaOptionTemplate<PayOffPut>  theOption(put , Expiry);

		ParametersConstant VolParam(Vol), rParam(r), dParam(d), DritfParam(r - d);

		shared_ptr<RandomBase> generator(new AntiThetic(RandomMersenneTwister(1)));

		unique_ptr<PathGeneration> ThePath(new PathGenerationGBM(generator, Spot, Expiry, DritfParam, VolParam, N)); 

		mc_simul_am_ls = mc_pricer_ls(theOption, rParam, ThePath, M, N);

		TreeAmerican AmericanPut(Expiry, put);

		MyTrinomialTree::TrinomialTree trinomial_tree_atm(Spot, rParam, dParam, Vol, N, Expiry);

		tree_am = trinomial_tree_atm.GetThePrice(AmericanPut);

		//-----------------------------------------------------------------------------------------------
		//test case barrier < strike
		
		d = .03;
		Strike = 103.0;
		Expiry = 1.0;
		
		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Dec, 2000);

		double BarrierDown(80.0);

		//DOC

		ql_analytical_doc1 = do_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		TreeBarrier DOC(Expiry, PayOffDownOutCall(BarrierDown, Strike));

		MyTrinomialTree::TrinomialTree trinomial_tree_atm_down(BarrierDown, rParam, dParam, Vol, N, Expiry);

		tree_doc1 = trinomial_tree_atm_down.GetThePrice(DOC);

		analytical_doc1 = down_out_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//DOP

		ql_analytical_dop1 = do_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		TreeBarrier DOP(Expiry, PayOffKOPut(BarrierDown, Strike));

		tree_dop1 = trinomial_tree_atm_down.GetThePrice(DOP);

		analytical_dop1 = down_out_put(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOC

		Spot = 50.0;

		ql_analytical_uoc1 = uo_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		TreeBarrier UOC(Expiry, PayOffKOCall(BarrierDown, Strike));

		tree_uoc1 = trinomial_tree_atm_down.GetThePrice(UOC);

		analytical_uoc1 = up_out_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOP

		ql_analytical_uop1 = uo_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		TreeBarrier UOP(Expiry, PayOffUpOutPut(BarrierDown, Strike));

		tree_uop1 = trinomial_tree_atm_down.GetThePrice(UOC);

		analytical_uop1 = up_out_put(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------
		//test case barrier > strike

		Spot = 140.0;

		double BarrierUp(120.0);

		//DOC

		ql_analytical_doc2 = do_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		DOC = TreeBarrier(Expiry, PayOffDownOutCall(BarrierUp, Strike));

		MyTrinomialTree::TrinomialTree trinomial_tree_atm_up(BarrierUp, rParam, dParam, Vol, N, Expiry);

		tree_doc2 = trinomial_tree_atm_up.GetThePrice(DOC);

		analytical_doc2 = down_out_call(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//DOP

		ql_analytical_dop2 = do_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		DOP = TreeBarrier(Expiry, PayOffKOPut(BarrierUp, Strike));

		tree_dop2 = trinomial_tree_atm_up.GetThePrice(DOP);

		analytical_dop2 = down_out_put(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOC

		Spot = 100.0;

		ql_analytical_uoc2 = uo_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		UOC = TreeBarrier(Expiry, PayOffKOCall(BarrierUp, Strike));

		tree_uoc2 = trinomial_tree_atm_up.GetThePrice(UOC);

		analytical_uoc2 = up_out_call(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOP


		ql_analytical_uop2 = uo_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		UOP = TreeBarrier(Expiry, PayOffUpOutPut(BarrierUp, Strike));

		tree_uop2 = trinomial_tree_atm_up.GetThePrice(UOP);

		analytical_uop2 = up_out_put(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

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