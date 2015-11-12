//test_sensitivity.cpp



#include <cmath>
#include<iostream>
#include<vector>
#include<memory>
#include <MersenneTwister.h>

#include "fwd_vol_structure.h"
#include "products.h"

#include "engine.h"
#include "dsct_factor.h"

using namespace std;

int main(int argc, char **argv) {

	try {

		//payer swaption 5-yr tenor half-year reset	

		std::vector<double> times(11);
		for (size_t j(0); j < 11; ++j)	times[j] = 0 + j / 2.0;

		//intial curve is flat 
		double r(.05);

		std::vector<double> zcps(11);
		for (size_t j(0); j < 11; ++j)	zcps[j] = exp(r*-times[j]);

		std::vector<double> fwd_rtes(10); //compute rates up to 5 yrs
		for (size_t j(0); j < 10; ++j)
			fwd_rtes[j] = (zcps[0] / zcps[j + 1] - 1.0) / (times[j + 1] - times[0]);

		double strike(0.06);

		//define fwd vol structure
		double a(0.05), b(0.09), c(0.44), d(0.11);

		double beta(0.1);

		FwdVolStructure1 vol_struct1(a, b, c, d, beta);

		//implement swaption + trigger swap
		//test numéraire invariant

		//payer swaption 5-yr tenor half-year reset	

		shared_ptr<BGMProducts> swaption(new Swaption(times, strike));

		shared_ptr<RandomBase> generator(new RandomMersenneTwister(swaption->GetUnderlyingTimes().size() - 1));

		TheEngine engine_swaption(swaption, vol_struct1, generator, fwd_rtes, times, .25, 0, zcps[0]); //initial setup no substep .5

		//----------------------------------------------------------------------------
		//sensitivity to shape
		//compare the changes in value w/ the vega of the option

		//a. bumping all the volatilities up by 1%

		double value_0 = engine_swaption.DoSimulation(1000, PC);

		vol_struct1.bumpVol(.01);

		std::vector<double> K(fwd_rtes.size(), 1.0); //K = 1

		//matrix<double> cov = engine_swaption.getCovariance(); 
		size_t m(engine_swaption.getCovariance().size1());
		matrix<double> c1(m, m);

		vol_struct1.covariance(c1, K, times, 0, .5);

		engine_swaption.setCovariance(c1); 

		double value_1 = engine_swaption.DoSimulation(1000, PC);

		cout << "Bumped volatilities by 1% " << endl;

		cout << "abcd vol structure, vega - bps : " << fabs(value_1 - value_0) / .0001 << endl;

		//price using flat vol vs vol structure

		//effective constant volatility = mean-square-time-averaged volatility

		FwdVolStructureFlat vol_struct_flat(0.129291646, beta); //see vol term structure

		TheEngine engine_swaption_flat(swaption, vol_struct_flat, generator, fwd_rtes, times, .5, 0, zcps[10]);

		double value_2 = engine_swaption_flat.DoSimulation(1000, PC);

		vol_struct_flat.bumpVol(.01);

		matrix<double> c2(m,m); 

		vol_struct_flat.covariance(c2, K, times, 0, .5); 

		engine_swaption_flat.setCovariance(c2); 

		double value_3 = engine_swaption_flat.DoSimulation(1000, PC);

		cout << "flat vol structure, vega - bps : " << fabs(value_3 - value_2) / .0001 << endl;

		//b. test the price sensitivity to changing beta.
		//beta = 0.0 < -  beta = 0.1

		cout << "Price sensitivity to chging beta " << endl;
		cout << "beta 0.1 -> 0.0 " << endl;

		vol_struct1.setBeta(0.0);

		matrix<double> c3(m, m);

		vol_struct1.covariance(c3, K, times, 0, .5);

		engine_swaption.setCovariance(c3);

		double value_4 = engine_swaption.DoSimulation(1000, PC);

		cout << "abcd vol structure, vega -bps : " << fabs(value_4 - value_1) / .0001 << endl;

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