// test_lmm.cpp

/*b.13 project 11:BGM*/

#include <cmath>
#include<iostream>
#include<vector>

#include <MersenneTwister.h>
#include <interest_derivatives_analytical.h>
#include "fwd_vol_structure.h"
#include "products.h"
#include "rebonato_formula.h"
#include "engine.h"
#include "dsct_factor.h"

using namespace std;

int main(int argc, char **argv) {

	try {

		//test the engine

		//1st test price a caplet w/ the numéraire

		std::vector<double> times(11);
		for (size_t j(0); j < 11; ++j)	times[j] = 0.0 + j / 2.0;
		
		//intial curve is flat 
		double r(0.05);

		std::vector<double> zcps(11);
		for (size_t j(0); j < 11; ++j)	zcps[j] = exp(r*-times[j]);
		
		std::vector<double> fwd_rtes(10); //compute rates up to 5 yrs
		for (size_t j(0); j < 10; ++j)
			fwd_rtes[j] = (zcps[0] / zcps[j + 1] - 1.0) / (times[j + 1] - times[0]);
		
		double strike(0.06); //0.06

		//define fwd vol structure
		double a(0.05), b(0.09), c(0.44), d(0.11);

		double beta(0.1);

		FwdVolStructure1 vol_struct1(a, b, c, d, beta);

		shared_ptr<BGMProducts> caplet(new Caplet(times, strike));

		shared_ptr<RandomBase> generator(new RandomMersenneTwister(caplet->GetUnderlyingTimes().size() - 1));

		//price caplet in the 1st fwd rte with each diff pj

		TheEngine engine_caplet(caplet, vol_struct1, generator, fwd_rtes, times, .25, 0, zcps[0]); //initial setup no substep .5

		cout << "Caplet pricing : " << endl;

		for (size_t i(0); i < 10; ++i){
			engine_caplet.setNumeraire(i, zcps[i]);
			cout << "Numeraire : " << times[i] << ", BGM price : " << engine_caplet.DoSimulation(1000, PC) << endl;
		}

		cout << endl;

		//compare price w/ Black formula
		//must be numéraire invariant

		cout << "Black formula price for caplet : " <<
			black_formula_caplet(zcps[1], fwd_rtes[0], 1, 1.5, strike, vol_struct1.volatility(10.0, 0.0)) << endl;
		
		cout << endl;

		//implement swaption + trigger swap
		//test numéraire invariant

		//payer swaption 5-yr tenor half-year reset	

		shared_ptr<BGMProducts> swaption(new Swaption(times, strike));

		shared_ptr<RandomBase> generator1(new RandomMersenneTwister(swaption->GetUnderlyingTimes().size() - 1));

		TheEngine engine_swaption(swaption, vol_struct1, generator1, fwd_rtes, times, .25, 0, zcps[0]); //initial setup no substep

		cout << "Swaption pricing : " << endl;

		for (size_t i(0); i < 10; ++i){
			engine_swaption.setNumeraire(i, zcps[i]);
			cout << "Numeraire : " << times[i] << ", BGM price : " << engine_swaption.DoSimulation(1000, PC) << endl;
		}

		cout << endl;

		//---------------------------------------------------------------------------
		//the approx formula
		//Compare the prices obtained w/ those implied by the BGM engine
		//payer swaption 5-yr tenor half-year reset	

		cout << "Black formula pricing for swaption " << endl;
		cout << "using Rebonato formula for volatility : " << endl;

		matrix<double> cov = engine_swaption.getCovariance();

		double swap_rte = swap_rate(fwd_rtes, times, 0, 9);
		double annuity = annuity_swap(fwd_rtes, times, 0, 9);
		double vol_rebonato = sqrt(rebonato_formula(swap_rte, 0, 9, fwd_rtes, times, cov));

		cout << black_formula_payer_swaption(annuity, swap_rte, strike, vol_rebonato, 5.0) << endl;
		cout << endl;

		//exotic swap - trigger swap - 5-yr tenor

		shared_ptr<BGMProducts> up_n_out(new TriggerSwap(times, strike, 0.07)); //up & out 7% ko rate

		shared_ptr<RandomBase> generator2(new RandomMersenneTwister(up_n_out->GetUnderlyingTimes().size() - 1));

		TheEngine engine_up_out(up_n_out, vol_struct1, generator2, fwd_rtes, times, 10, 0, zcps[0]); //initial setup no substep

		cout << "Trigger swap pricing - up-and-out: " << endl;

		for (size_t i(0); i < 10; ++i){
			engine_up_out.setNumeraire(i, zcps[i]);
			cout << "Numeraire : " << times[i] << ", BGM price : " << engine_up_out.DoSimulation(1000, PC) << endl;

		}

		cout << endl;

		double tmp;
		cin >> tmp;

		return 0;



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