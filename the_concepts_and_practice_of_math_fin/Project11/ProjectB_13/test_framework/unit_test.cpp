// unit_test.cpp

/*
Use google test to validate framework and QuantLib as benchmark.

Do the following test

1. analytical vs mc

2. analytical vs ql analytical

3. ms vs ql analytical

*/

#include "gtest/gtest.h"

#include "caplet_lmm_ql.h"
#include "swaption_lmm_ql.h"
#include "fwd_vol_structure.h"
#include "products.h"
#include "engine.h"
#include "dsct_factor.h"

#include <MersenneTwister.h>
#include <NewtonRaphson.h>
#include <BlackSwaption.h>
#include <Terminator.h>

using namespace std;
using namespace QuantLib;
using namespace Product;

double absolute_range(5e-04);

double iv_lmm_swaption;

Real ql_iv_lmm_swaption;

double mc_lmm_swaption, mc_lmm_caplet;

Real ql_lmm_swaption, ql_lmm_caplet;

//LMM European swaption
TEST(LMMSwaptionTest, MCvsQL) {
	EXPECT_NEAR(mc_lmm_swaption, ql_lmm_swaption, absolute_range);
}

TEST(LMMSwaptionTest, MCivvsQLiv) {
	EXPECT_NEAR(iv_lmm_swaption, ql_iv_lmm_swaption, absolute_range);
}

//LMM caplet
TEST(LMMCapletTest, MCvsQL) {
	EXPECT_NEAR(mc_lmm_caplet, ql_lmm_caplet, absolute_range);
}



int main(int argc, char **argv) {

	try {

		Real Spot0(.05); 
		
		double Strike(.06);
		double Expiry(.5);
		unsigned long NumberOfDates(12);

		Rate Numeraire(1);

		double correl(.1);
		double a(.05);
		double b(.09);
		double c(.44);
		double d(.11);

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(01, Jan, 2006);

		//European swaption 

		ql_lmm_swaption = swaption_lmm(todaysDate,0,5,Spot0, Strike, correl,a,b,c,d);

		std::vector<double> times(11);
		for (size_t j(0); j < 11; ++j)	times[j] = 0.0 + j / 2.0;

		//intial curve is flat 
		double r(0.05);

		std::vector<double> zcps(11);
		for (size_t j(0); j < 11; ++j)	zcps[j] = exp(r*-times[j]);

		std::vector<double> fwd_rtes(10); //compute rates up to 5 yrs
		for (size_t j(0); j < 10; ++j)
			fwd_rtes[j] = (zcps[0] / zcps[j + 1] - 1.0) / (times[j + 1] - times[0]);

		FwdVolStructure1 vol_struct1(a, b, c, d, correl);

		//payer swaption 5-yr tenor half-year reset	

		shared_ptr<BGMProducts> swaption(new Product::Swaption(times, Strike));

		shared_ptr<RandomBase> generator1(new RandomMersenneTwister(swaption->GetUnderlyingTimes().size() - 1));

		TheEngine engine_swaption(swaption, vol_struct1, generator1, fwd_rtes, times, .25, 0, zcps[0]); 

		mc_lmm_swaption = engine_swaption.DoSimulation(1000, PC);

		double annuity = annuity_swap(fwd_rtes, times, 0, 9);

		BlackSwaption theSwaption(annuity, Spot0, Strike, Expiry);

		Terminator terminator(5, 100); //5 sec, 100 max iter

		iv_lmm_swaption = NewtonRaphson1<BlackSwaption, &BlackSwaption::Price, &BlackSwaption::Vega>(mc_lmm_swaption, 1.0, 1e-04, theSwaption, terminator);

		//BGM model flat volatility

		ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, 0,5, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

		//European Caplet ATM

		maturity = Date(30, Jun, 2000);

		ql_lmm_caplet = caplet_lmm(todaysDate, settlementDate, maturity, Spot0, Strike, Numeraire, correl, a, b, c, d);

		shared_ptr<BGMProducts> caplet(new Caplet(times, Strike));

		shared_ptr<RandomBase> generator(new RandomMersenneTwister(caplet->GetUnderlyingTimes().size() - 1));

		//price caplet in the 1st fwd rte 

		TheEngine engine_caplet(caplet, vol_struct1, generator, fwd_rtes, times, .25, 0, zcps[0]); //initial setup no substep .5

		mc_lmm_caplet = engine_caplet.DoSimulation(1000, PC);
	
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