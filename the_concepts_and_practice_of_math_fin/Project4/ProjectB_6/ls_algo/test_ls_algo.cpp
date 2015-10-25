//test_ls_algo.cpp

// Pricing American Put using Longstaff - Schwartz method
// Stock underlying dynamics : dS = r*S dt + sig*S dW


#include <iostream>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <engine_ls.h>
#include <path_generation_gbm.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>

#include <fstream>

using namespace std;
using namespace Vanilla;

int main(){

	try {

		double r(0.05);
		double d(0.0);
		double Vol(0.1);
		double Expiry(2.00);
		double Spot(100.0);
		double Strike(100.0);

		unsigned long M(static_cast<unsigned long>(1e4)); //1e4 # of simul

		unsigned long N(static_cast<unsigned long>(1e2)); //1e2 # of tree nodes

		PayOffPut thePayOff(Strike);

		VanillaOptionTemplate<PayOffPut>  theOption(thePayOff, Expiry);

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant DritfParam(r - d);

		RandomMersenneTwister generator0(1);

		shared_ptr<RandomBase> _generator(new AntiThetic(generator0));

		unique_ptr<PathGeneration> ThePath(new PathGenerationGBM(_generator, Spot, Expiry, DritfParam, VolParam, N));

		unique_ptr<PathGeneration> ThePath1(new PathGenerationGBM(_generator, Spot*1.2, Expiry, DritfParam, VolParam, N));

		double OptionPrice = mc_pricer_ls(theOption, rParam, ThePath, M, N);
		cout << "American put option MC LS ATM 2 yrs : ";
		cout << OptionPrice << endl;

		OptionPrice = mc_pricer_ls(theOption, rParam, ThePath1, M, N);
		cout << "American put option MC LS OTM 2 yrs : ";
		cout << OptionPrice << endl;

		cout << "computation started" << endl;

		ofstream price_am_ls;
		price_am_ls.open("price_am_ls.txt");

		price_am_ls << "i" << ";" << "am_put_atam" << "am_put_otm" << ";\n";

		for (unsigned long i = 10; i <= 100; ++i){

			price_am_ls << i << " "
				<< mc_pricer_ls(theOption, rParam, ThePath, i, N) << " "
				<< mc_pricer_ls(theOption, rParam, ThePath1, i, N) << ";\n";
		}

		price_am_ls.close();

		cout << "computation ended" << endl;

		double tmp;
		std::cin >> tmp;

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