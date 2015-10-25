//main.cpp

/*
B.6 Project 4 : recombining trees

*/

#include <BinomialTreeLinear.h>
#include <BinomialTreeAmericanBarrier.h>
#include <TrinomialTree.h>

#include <TreeAmerican.h>
#include <TreeEuropean.h>
#include <TreeBarrier.h>

#include <BlackScholesFormulas.h>
#include <PayOff3.h>
#include <PayOffForward.h>
#include <barrierOption.h>
#include <Digital.h>

#include <Parameters.h>

#include <iostream>
#include <fstream>

#include <cmath>
using namespace std;
using namespace MyTrinomialTree;

int main(){

	try{

		double Expiry(2.0);
		double Strike(100);
		double Spot(100);
		double BarrierUp(Spot * 1.2);
		double BarrierDown(Spot * .8);

		double Vol(.1);
		double r(.05);
		double d(0.0);

		unsigned long Steps(100);

		ParametersConstant rParam(r);
		ParametersConstant dParam(d);

		PayOffCall call(Strike);
		PayOffPut put(Strike);

		PayOffForward fwd(Strike);

		PayOffDigitalCall digital(Strike);

		PayOffDownOutCall doc(BarrierDown, Strike);
		PayOffKOPut dop(BarrierDown, Strike);

		TreeEuropean VanillaCall(Expiry, call);
		TreeEuropean Forward(Expiry, fwd);
		TreeEuropean VanillaPut(Expiry, put);

		TreeBarrier DOC(Expiry, doc);
		TreeBarrier DOP(Expiry, dop);

		TreeAmerican AmericanPut(Expiry, put);

		TreeEuropean DigitalOption(Expiry, digital);

		//price option under GBM

		//Price products ATM under binomial tree

		cout << "computation starts" << endl;
		cout << "ATM binomial tree" << endl;

		ofstream bin_price_atm;
		bin_price_atm.open("bin_price_atm.txt");

		bin_price_atm << "i" << ";" << "prices_vanilla_call" << ";" << "prices_forward" << ";" << "prices_vanilla_put" << ";" << "prices_doc" << ";" <<
			"prices_dop" << ";" << "prices_american_put" << ";" << "prices_digital" << ";\n";


		for (unsigned long i = 1; i <= Steps; ++i){

			BinomialTree binomial_tree_atm(Spot, rParam, dParam, Vol, i, Expiry);

			BinomialTreeAmericanBarrier binomial_tree_atm_am(Spot, rParam, dParam, Vol, i, Expiry);

			bin_price_atm << i << " "
				<< binomial_tree_atm.GetThePrice(VanillaCall) << " "
				<< binomial_tree_atm.GetThePrice(Forward) << " "
				<< binomial_tree_atm.GetThePrice(VanillaPut) << " "
				<< binomial_tree_atm.GetThePrice(DOC) << " "
				<< binomial_tree_atm.GetThePrice(DOP) << " "



				<< binomial_tree_atm_am.GetThePrice(AmericanPut) << " "
				<< binomial_tree_atm.GetThePrice(DigitalOption) << ";\n";

		}

		bin_price_atm.close();

		//Price products OTM under binomial tree

		cout << "OTM binomial tree" << endl;

		ofstream bin_price_otm;
		bin_price_otm.open("bin_price_otm.txt");

		bin_price_otm << "i" << ";" << "prices_vanilla_call" << ";" << "prices_forward" << ";" << "prices_vanilla_put" << ";" << "prices_doc" << ";" <<
			"prices_dop" << ";" << "prices_american_put" << ";" << "prices_digital" << ";\n";


		for (unsigned long i = 1; i <= Steps; ++i){

			BinomialTree binomial_tree_otm_down(BarrierDown, rParam, dParam, Vol, i, Expiry);
			BinomialTree binomial_tree_otm_up(BarrierUp, rParam, dParam, Vol, i, Expiry);

			BinomialTreeAmericanBarrier binomial_tree_otm_am(BarrierUp, rParam, dParam, Vol, i, Expiry);

			bin_price_otm << i << " "
				<< binomial_tree_otm_down.GetThePrice(VanillaCall) << " "
				<< binomial_tree_otm_down.GetThePrice(Forward) << " "
				<< binomial_tree_otm_up.GetThePrice(VanillaPut) << " "
				<< binomial_tree_otm_down.GetThePrice(DOC) << " "
				<< binomial_tree_otm_up.GetThePrice(DOP) << " "

				<< binomial_tree_otm_am.GetThePrice(AmericanPut) << " "
				<< binomial_tree_otm_down.GetThePrice(DigitalOption) << ";\n";

		}

		bin_price_otm.close();

		//Price products ATM under trinomial tree

		cout << "ATM trinomial tree" << endl;

		ofstream tri_price_atm;
		tri_price_atm.open("tri_price_atm.txt");

		tri_price_atm << "i" << ";" << "prices_vanilla_call" << ";" << "prices_forward" << ";" << "prices_vanilla_put" << ";" << "prices_doc" << ";" <<
			"prices_dop" << ";" << "prices_american_put" << ";" << "prices_digital" << ";\n";

		for (unsigned long i = 0; i <= Steps; ++i){

			TrinomialTree trinomial_tree_atm(Spot, rParam, dParam, Vol, i, Expiry);



			tri_price_atm << i << " "
				<< trinomial_tree_atm.GetThePrice(VanillaCall) << " "
				<< trinomial_tree_atm.GetThePrice(Forward) << " "
				<< trinomial_tree_atm.GetThePrice(VanillaPut) << " "
				<< trinomial_tree_atm.GetThePrice(DOC) << " "
				<< trinomial_tree_atm.GetThePrice(DOP) << " "
				<< trinomial_tree_atm.GetThePrice(AmericanPut) << " "
				<< trinomial_tree_atm.GetThePrice(DigitalOption) << ";\n";

		}

		tri_price_atm.close();

		//Price products OTM under trinomial tree

		cout << "OTM trinomial tree" << endl;

		ofstream tri_price_otm;
		tri_price_otm.open("tri_price_otm.txt");

		tri_price_otm << "i" << ";" << "prices_vanilla_call" << ";" << "prices_forward" << ";" << "prices_vanilla_put" << ";" << "prices_doc" << ";" <<
			"prices_dop" << ";" << "prices_american_put" << ";" << "prices_digital" << ";\n";

		for (unsigned long i = 0; i <= Steps; ++i){

			TrinomialTree trinomial_tree_otm_down(BarrierDown, rParam, dParam, Vol, i, Expiry);
			TrinomialTree trinomial_tree_otm_up(BarrierUp, rParam, dParam, Vol, i, Expiry);

			tri_price_otm << i << " "
				<< trinomial_tree_otm_down.GetThePrice(VanillaCall) << " "
				<< trinomial_tree_otm_down.GetThePrice(Forward) << " "
				<< trinomial_tree_otm_up.GetThePrice(VanillaPut) << " "
				<< trinomial_tree_otm_down.GetThePrice(DOC) << " "
				<< trinomial_tree_otm_up.GetThePrice(DOP) << " "
				<< trinomial_tree_otm_up.GetThePrice(AmericanPut) << " "
				<< trinomial_tree_otm_down.GetThePrice(DigitalOption) << ";\n";
		}

		tri_price_otm.close();

		cout << "computation end" << endl;

		//--------------------------------------------------------------------------------------------------------

		double tmp;
		cin >> tmp;

		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "unknown error" << std::endl;
		return 1;
	}



}