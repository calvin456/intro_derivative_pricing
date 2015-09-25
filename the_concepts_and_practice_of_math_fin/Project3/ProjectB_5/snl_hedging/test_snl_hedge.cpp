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

int main(){

	try{

		//Sell ATM 3-mth call option at fair value

		double Spot(100.0);
		double Strike(100.0);
		double r(0.05);
		double d(0.03);
		double Vol(.20);
		double Expiry(.25);

		CallOption* call1(new CallOption(Spot, Strike, r, d, Vol, Expiry));

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

		double call1_value0(call1->GetValue(Spot, Vol, Expiry));

		//-----------------------------------------------------------------------------------------
		//the delta-hedge strategy

		//Plot the var against time-step size
		//How is the var affected by chging mu and sigma?

		SnLHedging<CallOption>* snl_hedge(new SnLHedging<CallOption>(call1_value0, r, call1, path1, Expiry));

		EngineSimul<CallOption> engine_snl(snl_hedge, NumberOfPaths);

		cout << endl << "variance snl hedging vs rebalancing freq : " << endl;
		cout << "baseline : ";

		cout << " drift - ";
		cout << path1->GetDrift().Integral(0, 1);
		cout << " vol - ";
		cout << path1->GetVol().Integral(0, 1) << endl;

		cout << "No rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3

		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		//variance = engine_snl.DoSimulation(); 
		cout << "daily rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;
		//variance_neutral[3] = variance[0][0];

		//How is the var affected by chging mu and sigma?
		//Bump drift and vol by -/+ 10%
		cout << endl << "variance snl hedging vs rebalancing freq : " << endl;
		cout << "Bump drift by - 10% : ";

		path1->SetDrift(ParametersConstant(.9* (r - d)));
		cout << path1->GetDrift().Integral(0, 1) << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3
		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		cout << "daily rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//--------------------------------------
		cout << endl << "variance snl hedging vs rebalancing freq : " << endl;
		cout << "Bump drift by + 10% : ";

		path1->SetDrift(ParametersConstant(1.1* (r - d)));
		cout << path1->GetDrift().Integral(0, 1) << endl;
		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3
		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		cout << "daily rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;
		//--------------------------------------

		cout << endl << "variance snl hedging vs rebalancing freq : " << endl;
		cout << "Bump vol by - 10% : ";

		path1->SetVol(ParametersConstant(.9* Vol));
		cout << path1->GetVol().Integral(0, 1) << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3
		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		cout << "daily rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//--------------------------------------

		cout << endl << "variance snl hedging vs rebalancing freq : " << endl;
		cout << "Bump vol by + 10% : ";

		path1->SetVol(ParametersConstant(1.1* Vol));
		cout << path1->GetVol().Integral(0, 1) << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3
		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		cout << "daily rebalancing : ";
		cout << engine_snl.DoSimulation() << endl;

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