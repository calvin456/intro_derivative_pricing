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
#include <barrier_options_analytical.h>




using namespace std;
using namespace QuantLib;

double absolute_range(5e-02);

//test case barrier < strike

double tree_doc1, tree_dop1, tree_uoc1, tree_uop1;
double analytical_doc1, analytical_dop1, analytical_uoc1, analytical_uop1;
Real ql_analytical_doc1, ql_analytical_dop1, ql_analytical_uoc1, ql_analytical_uop1;

//test case barrier > strike

double tree_doc2, tree_dop2, tree_uoc2, tree_uop2;
double analytical_doc2, analytical_dop2, analytical_uoc2, analytical_uop2;
Real ql_analytical_doc2, ql_analytical_dop2, ql_analytical_uoc2, ql_analytical_uop2;

//-----------------------------------------------------------------------------

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


		//-----------------------------------------------------------------------------------------------
		//test case barrier < strike

		double BarrierDown(80.0);

		//DOC

		ql_analytical_doc1 = do_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		tree_doc1 = 0.0;

		analytical_doc1 = down_out_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//DOP

		ql_analytical_dop1 = do_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		tree_dop1 = 0.0;

		analytical_dop1 = down_out_put(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOC

		Spot = 50.0;

		ql_analytical_uoc1 = uo_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		tree_uoc1 = 0.0;

		analytical_uoc1 = up_out_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOP

		ql_analytical_uop1 = uo_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierDown, 0.0, d, r, Vol);

		tree_uop1 = 0.0;

		analytical_uop1 = up_out_put(Spot, Strike, BarrierDown, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------
		//test case barrier > strike

		Spot = 140.0;

		double BarrierUp(120.0);

		//DOC

		ql_analytical_doc2 = do_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		tree_doc2 = 0.0;

		analytical_doc2 = down_out_call(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//DOP

		ql_analytical_dop2 = do_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		tree_dop2 = 0.0;

		analytical_dop2 = down_out_put(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOC

		Spot = 100.0;

		ql_analytical_uoc2 = uo_call_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		tree_uoc2 = 0.0;

		analytical_uoc2 = up_out_call(Spot, Strike, BarrierUp, r, d, Vol, Expiry);

		//-----------------------------------------------------------------------------------------------

		//UOP


		ql_analytical_uop2 = uo_put_ql(todaysDate, settlementDate, maturity, Spot, Strike, BarrierUp, 0.0, d, r, Vol);

		tree_uop2 = 0.0;

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