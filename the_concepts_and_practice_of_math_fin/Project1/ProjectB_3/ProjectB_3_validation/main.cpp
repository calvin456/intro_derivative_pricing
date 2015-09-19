#include <iostream>
#include <cmath>

#include <Normals.h>
#include <Parameters.h>
#include <Arrays.h>
#include <MersenneTwister.h>
//#include <ParkMiller.h>
#include <AntiThetic.h>
#include <BlackScholesFormulas.h>
#include <path_generation_gbm.h>
#include <engine_vanilla.h>
#include <Vanilla3Template.cpp>
#include <MCStatistics.h>
#include <ConvergenceTable.h>
#include <Digital.h>

using namespace std;

int main(){

	try{

		double Spot(100);
		double Strike(100);
		double r(.01);
		double d(.03);
		double Vol(.30);
		double Expiry(.33);
		unsigned long NumberOfPaths(static_cast<unsigned long>(1e5));

		//Validation via MC

		// (i) Compute MC and formula prices for a large range of inputs for each of the options above

		//Compute mean error and standard error of price difference btn exact price and mc price

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant driftParam(r - d);

		RandomMersenneTwister generator_(1);
		//RandomParkMiller generator_(1);

		RandomBase* generator(new AntiThetic(generator_));

		shared_ptr<PathGeneration> thePath(new PathGenerationGBM(generator, Spot, Expiry, 
												driftParam, VolParam, 1));

		//---------------------------------------------------------------------------
		PayOffCall thePayOff(Strike);

		VanillaOptionTemplate<PayOffCall> theOption(thePayOff, Expiry);
		
		StatisticsMean gatherer_mean;

		StatisticsSE gatherer_se;

		cout << "BSM call" << endl;

		for (size_t strike(0); strike <= 200; ++strike)
		{
			theOption.SetStrike(strike);
			
			double tmp1 = mc_pricer_vanilla(theOption, rParam, thePath, NumberOfPaths);
			tmp1 -= BlackScholesCall(Spot, strike, r, d, Vol, Expiry);
			gatherer_mean.DumpOneResult(tmp1);
			gatherer_se.DumpOneResult(tmp1);
		}

		cout << "difference simul vs analytical solution" << endl;
		cout << "mean" << "\t " << "se" << endl;

		cout << gatherer_mean.GetResultsSoFar()[0][0] << "\t " 
			<< gatherer_se.GetResultsSoFar()[0][0] << endl;

		//-------------------------------------------------------------------
		PayOffPut thePayOff1(Strike);

		VanillaOptionTemplate<PayOffPut> theOption1(thePayOff1, Expiry);


		StatisticsMean gatherer_mean1;

		StatisticsSE gatherer_se1;

		cout << "BSM put" << endl;

		for (size_t strike(0); strike <= 200; ++strike)
		{
			theOption1.SetStrike(strike);

			double tmp1 = mc_pricer_vanilla(theOption1, rParam, thePath, NumberOfPaths);
			tmp1 -= BlackScholesPut(Spot, strike, r, d, Vol, Expiry);
			gatherer_mean1.DumpOneResult(tmp1);
			gatherer_se1.DumpOneResult(tmp1);
		}

		cout << "difference simul vs analytical solution" << endl;
		cout << "mean" << "\t " << "se" << endl;

		cout << gatherer_mean1.GetResultsSoFar()[0][0] << "\t "
			<< gatherer_se1.GetResultsSoFar()[0][0] << endl;

		//---------------------------------------------------------------------
		PayOffDigitalCall thePayOff2(Strike);

		VanillaOptionTemplate<PayOffDigitalCall> theOption2(thePayOff2, Expiry);

		StatisticsMean gatherer_mean2;

		StatisticsSE gatherer_se2;

		cout << "BSM digital call" << endl;

		for (size_t strike(0); strike <= 200; ++strike)
		{
			theOption2.SetStrike(strike);

			double tmp1 = mc_pricer_vanilla(theOption2, rParam, thePath, NumberOfPaths);
			tmp1 -= BlackScholesDigitalCall(Spot, strike, r, d, Vol, Expiry);
			gatherer_mean2.DumpOneResult(tmp1);
			gatherer_se2.DumpOneResult(tmp1);
		}

		cout << "difference simul vs analytical solution" << endl;
		cout << "mean" << "\t " << "se" << endl;

		cout << gatherer_mean2.GetResultsSoFar()[0][0] << "\t "
			<< gatherer_se2.GetResultsSoFar()[0][0] << endl;
		
		//-----------------------------------------------------------------------
		PayOffDigitalPut thePayOff3(Strike);

		VanillaOptionTemplate<PayOffDigitalPut> theOption3(thePayOff3, Expiry);

		StatisticsMean gatherer_mean3;

		StatisticsSE gatherer_se3;

		cout << "BSM digital put" << endl;

		for (size_t strike(0); strike <= 200; ++strike)
		{
			theOption3.SetStrike(strike);

			double tmp1 = mc_pricer_vanilla(theOption3, rParam, thePath, NumberOfPaths);
			tmp1 -= BlackScholesDigitalPut(Spot, strike, r, d, Vol, Expiry);
			gatherer_mean3.DumpOneResult(tmp1);
			gatherer_se3.DumpOneResult(tmp1);
		}

		cout << "difference simul vs analytical solution" << endl;
		cout << "mean" << "\t " << "se" << endl;

		cout << gatherer_mean3.GetResultsSoFar()[0][0] << "\t "
			<< gatherer_se3.GetResultsSoFar()[0][0] << endl;

		//-----------------------------------------------------------------------

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