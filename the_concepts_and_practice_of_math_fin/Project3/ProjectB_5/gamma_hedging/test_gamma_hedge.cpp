//main.cpp

/*
b.5 project 3 hedging

Test delta hedge
*/

#include <iostream>
#include <cmath>
#include <memory>

#include <Parameters.h>
#include <MersenneTwister.h>
#include <path_generation_gbm.h>

#include <hedging_strategy.cpp>
#include <engine_simul.cpp>

using namespace std;
using namespace MyOption;

int main(){

	try{

		//Sell ATM 3-mth call option at fair value

		double Spot(100.0);
		double Strike(100.0);
		double r(0.05);
		double d(0.03);
		double Vol(.20);
		double Expiry(.25);

		shared_ptr<CallOption> call1(new CallOption(Spot, Strike, r, d, Vol, Expiry));

		//-----------------------------------------------------------------------------------------
		//Gamma Hedging
		//Implement the Gamma hedging of a far-OTM option
		//with spot and another option

		shared_ptr<CallOption>	call2(new CallOption(Spot, .9*Strike, r, d, Vol, Expiry));

		double call1_value0(call2->GetValue(Spot, Vol, Expiry));

		//-----------------------------------------------------------------------------------------
		//the perfect BSM world
		unsigned long NumberOfPaths(static_cast<unsigned long>(1e5));

		shared_ptr<RandomMersenneTwister> generator(new RandomMersenneTwister(1));
		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant driftParam(r - d);

		PathGenerationGBM* path1(new PathGenerationGBM(generator, Spot, Expiry,
			driftParam,
			VolParam));

		

		//-----------------------------------------------------------------------------------------
		//the delta-hedge strategy

		//Plot the var against time-step size
		//How is the var affected by chging mu and sigma?

		shared_ptr<GammaHedging<CallOption, CallOption>> gamma_hedge(new GammaHedging<CallOption, CallOption>
														(call1_value0, r, call2, call1, path1, Expiry));

		EngineSimul<CallOption> engine_gamma(gamma_hedge, NumberOfPaths);

		cout << "variance pnl" << endl;
		cout << endl << "gamma hedging vs rebalancing freq : " << endl;
		cout << "baseline : ";

		cout << " drift - ";
		cout << path1->GetDrift().Integral(0, 1);
		cout << " vol - ";
		cout << path1->GetVol().Integral(0, 1) << endl;

		cout << "No rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3

		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		//variance = engine_gamma.DoSimulation(); 
		cout << "daily rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;
		//variance_neutral[3] = variance[0][0];


		//How is the var affected by chging mu and sigma?
		//Bump drift and vol by -/+ 10%
		cout << endl << "gamma hedging vs rebalancing freq : " << endl;
		cout << "Bump drift by - 10% : ";

		path1->SetDrift(ParametersConstant(.9* (r - d)));
		cout << path1->GetDrift().Integral(0, 1) << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3
		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		cout << "daily rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//--------------------------------------
		cout << endl << "gamma hedging vs rebalancing freq : " << endl;
		cout << "Bump drift by + 10% : ";

		path1->SetDrift(ParametersConstant(1.1* (r - d)));
		cout << path1->GetDrift().Integral(0, 1) << endl;
		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3
		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		cout << "daily rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;
		//--------------------------------------

		cout << endl << "gamma hedging vs rebalancing freq : " << endl;
		cout << "Bump vol by - 10% : ";

		path1->SetVol(ParametersConstant(.9* Vol));
		cout << path1->GetVol().Integral(0, 1) << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3
		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		cout << "daily rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//--------------------------------------

		cout << endl << "gamma hedging vs rebalancing freq : " << endl;
		cout << "Bump vol by + 10% : ";

		path1->SetVol(ParametersConstant(1.1* Vol));
		cout << path1->GetVol().Integral(0, 1) << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3
		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		cout << "daily rebalancing : ";
		cout << engine_gamma.DoSimulation() << endl;

		//-----------------------------------------------------------------------------------------

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