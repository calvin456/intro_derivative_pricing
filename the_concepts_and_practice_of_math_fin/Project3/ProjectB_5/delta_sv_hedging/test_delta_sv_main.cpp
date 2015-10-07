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

#include <path_generation_heston.h>

#include <hedging_strategy.cpp>
#include <hedging_strategy_sv.cpp>
#include <engine_simul.cpp>

using namespace std;

int main(){

	try{

		//Sell ATM 3-mth call option at fair value

		double Spot(100.0);
		double Strike(100.0);
		double r(0.05);
		double d(0.03);
		double Vol(.12); // .04 .08 .09 
		double Expiry(.25);

		shared_ptr<CallOption> call1(new CallOption(Spot, Strike, r, d, Vol, Expiry));

		//-----------------------------------------------------------------------------------------
		//the perfect BSM world
		unsigned long NumberOfPaths(static_cast<unsigned long>(1e4));

		shared_ptr<RandomMersenneTwister> generator(new RandomMersenneTwister(1));
		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant driftParam(r - d);

		//------------------------------------------------------------------------------------------
		//Time-dependent volatility

		double Correl(-0.6); //-0.9 -0.5 -0.3
		double Kappa(1.2); //0.5 0.3 1 
		double Epsilon(.05); //1 .09 1
		

		//Vol = .04; //4% 4% 9%

		/*
		Real v0=0.12, theta=0.08, 
		*/

		shared_ptr<PathGenerationHeston> path1(new PathGenerationHeston(generator, Spot, Expiry,
								driftParam,
								VolParam, 1, Correl, Kappa, Epsilon)); 

		double call1_value0(call1->GetValue(Spot, Vol, Expiry));

		
		//-----------------------------------------------------------------------------------------
		//Implement the following hedging methods :

		//For each method, plot the var against time-step size

		// (i) Delta hedge using the current value of sigma in the BSM delta - implicit milstein scheme Kahl & Jaeckel using full trunction

		shared_ptr<DeltaHedgingCurrentVol<CallOption>> delta_hedge_cv(new DeltaHedgingCurrentVol<CallOption>(call1_value0, r, call1, path1, Expiry));

		EngineSimulSV<CallOption> engine_delta_sv1(delta_hedge_cv, NumberOfPaths);

		cout << "variance of pnl : " << endl;
		cout << endl << "current vol delta hedging vs rebalancing freq : " << endl;
		

		cout << "No rebalancing : ";
		cout << engine_delta_sv1.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3

		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_delta_sv1.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_delta_sv1.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		//variance = engine_delta.DoSimulation(); 
		cout << "daily rebalancing : ";
		cout << engine_delta_sv1.DoSimulation() << endl;
		
		
		// (ii) Delta hedging using rms of sigma across at all times
		
		shared_ptr<DeltaHedgingRMS<CallOption>> delta_hedge_rms(new DeltaHedgingRMS<CallOption>(call1_value0, r, call1, path1, Expiry));

		EngineSimulSV<CallOption> engine_delta_sv2(delta_hedge_rms, NumberOfPaths);

		cout << endl << "rms vol delta hedging vs rebalancing freq : " << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_delta_sv2.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3

		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_delta_sv2.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_delta_sv2.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		//variance = engine_delta.DoSimulation(); 
		cout << "daily rebalancing : ";
		cout << engine_delta_sv2.DoSimulation() << endl;
		
		
		// (iii) Delta hedging using rms of sigma at time s

		shared_ptr<DeltaHedgingRMSDec<CallOption>> delta_hedge_rms_dec(new DeltaHedgingRMSDec<CallOption>(call1_value0, r, call1,path1,Expiry));

		EngineSimulSV<CallOption> engine_delta_sv3(delta_hedge_rms_dec, NumberOfPaths);

		cout << endl << "rms vol decreasing delta hedging vs rebalancing freq : " << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_delta_sv3.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3

		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_delta_sv3.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_delta_sv3.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		//variance = engine_delta.DoSimulation(); 
		cout << "daily rebalancing : ";
		cout << engine_delta_sv3.DoSimulation() << endl;
		
		//Extropolate to get the variance for instantaneous hedging - Broadie & Kaya, Quadratic Exponential scheme
		//Implement Quadratic Exponential scheme

		shared_ptr<DeltaHedgingInstantVol<CallOption>> delta_hedge_inst(new DeltaHedgingInstantVol<CallOption>(call1_value0, r, call1, path1, Expiry));

		EngineSimulSV<CallOption> engine_delta_sv4(delta_hedge_inst, NumberOfPaths);

		cout << endl << "instant vol  delta hedging vs rebalancing freq : " << endl;

		path1->SetSteps(1);

		cout << "No rebalancing : ";
		cout << engine_delta_sv4.DoSimulation() << endl;

		//Plot the var against time-step size

		//step-up initial hedge and do not take any other action. ie. No rebalancing 1 = 1
		//monthly rebalancing 1*3 = 3

		path1->SetSteps(3);

		cout << "monthly rebalancing : ";
		cout << engine_delta_sv4.DoSimulation() << endl;

		//weekly rebalancing 1*3*4 = 12
		path1->SetSteps(12);

		cout << "weekly rebalancing : ";
		cout << engine_delta_sv4.DoSimulation() << endl;

		//daily rebalancing 1*3*4*5 = 60
		path1->SetSteps(60);

		//variance = engine_delta.DoSimulation(); 
		cout << "daily rebalancing : ";
		cout << engine_delta_sv4.DoSimulation() << endl;
		
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