//main.cpp

/*
b.9 project 7 replication continuous barrier option

Test 
*/

#include <iostream>
#include <memory>

#define _USE_MATH_DEFINES
#include<cmath>
#include<math.h>

#include <OptionsToReplicate.h>
#include <barrier_options_analytical.h>
#include <engine_replication.h>
#include <options.h>

using namespace std;

int main(){

	try{
		//convergence
		//Implement the method of section 10.2 for the pricing of continous barrier options

		double Spot(100.0);
		double Strike(100.0);

		double BarrierUp(120.0); //+20% barrier
		double BarrierDown(80.0); //-20% barrier

		double Expiry(1.0);

		double r(0.05);
		double d(0.0);

		double Vol(.10);

		//down-and-out call

		shared_ptr<OptionToReplicate> DOC(new DownAndOutCall(Strike, BarrierDown, r, Vol, Expiry, d));

		//up-and-out call

		shared_ptr<OptionToReplicate> UOC(new UpAndOutCall(Strike, BarrierUp, r, Vol, Expiry, d));

		cout << "Down-and-out call : ";
		cout << down_out_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry) << endl;

		cout << "Up-and-out call : ";
		cout << up_out_call(Spot, Strike, BarrierUp, r, d, Vol, Expiry) << endl;

		cout << endl;

		//Varying the final pay-off

		//(i) pay-off const above the barrier
		shared_ptr<Option> OT(new DigitalCallOption(Spot, BarrierUp, r, d, Vol, Expiry));
		shared_ptr<Option> OT1(new DigitalPutOption(Spot, BarrierDown, r, d, Vol, Expiry));

		double epsilon(.010); //5.0 1.0 .5 .1

		//(ii) tight call spread of width epsilon starting at 120
		shared_ptr<Option> CallSpread(new CallSpreadOption(Spot, BarrierUp, r, d, Vol, Expiry, epsilon));

		//(iii) tight call spread of width 2 * epsilon starting at 120
		shared_ptr<Option> CallSpread1(new CallSpreadOption(Spot, BarrierUp, r, d, Vol, Expiry, 2.0 *epsilon));

		//(iv) tight call spread of width 2 * epsilon starting at 120 - epsilon
		shared_ptr<Option> CallSpread2(new CallSpreadOption(Spot, BarrierUp - epsilon, r, d, Vol, Expiry, 2.0 *epsilon));

		double t(Expiry);


		EngineRepli<OptionToReplicate, Option> engine_doc_ot(DOC, OT1);

		for (size_t i(0); i < 10; ++i){
			cout << "OT ";
			cout << "DOC steps " << i << " : ";
			cout << engine_doc_ot.DoReplication(i, Spot, t) << endl;
		}
		cout << endl;

		EngineRepli<OptionToReplicate, Option> engine_uoc_ot(UOC, OT);

		for (size_t i(0); i < 10; ++i){
			cout << "OT ";
			cout << "UOC steps " << i << " : ";
			cout << engine_uoc_ot.DoReplication(i, Spot, t) << endl;
		}
		cout << endl;


		EngineRepli<OptionToReplicate, Option> engine_uoc_cs(UOC, CallSpread);

		for (size_t i(0); i < 10; ++i){
			cout << "call spread 120, " << 120 + epsilon << " ";
			cout << "- UOC steps " << i << " : ";
			cout << engine_uoc_cs.DoReplication(i, Spot, t) << endl;
		}
		cout << endl;

		EngineRepli<OptionToReplicate, Option> engine_uoc_cs1(UOC, CallSpread1);

		for (size_t i(0); i < 10; ++i){
			cout << "call spread 120, " << 120 + 2.0*epsilon << " ";
			cout << "- UOC steps " << i << " : ";
			cout << engine_uoc_cs1.DoReplication(i, Spot, t) << endl;
		}
		cout << endl;

		EngineRepli<OptionToReplicate, Option> engine_uoc_cs2(UOC, CallSpread2);

		for (size_t i(0); i < 10; ++i){
			cout << "call spread " << 120 - epsilon << ", " << 120 + epsilon << " ";
			cout << "- UOC steps " << i << " : ";
			cout << engine_uoc_cs2.DoReplication(i, Spot, t) << endl;
		}
		cout << endl;



		//time-step size
		//Try varying the time-step sizes st steps shorter close to expiry

		for (size_t i(0); i < 10; ++i){
			cout << "OT - time varying steps" << " ";
			cout << "- UOC steps " << i << " : ";
			cout << engine_uoc_ot.DoReplication1(i, Spot, t) << endl;
		}
		cout << endl;

		//--------------------------------------------------------------------------------

		//time-dependent volatility
		//Reprice options using variety of time-dep func for volatile
		//Choose func st rms vol over the year always the same

		//-------------------------------------------------------------------------------
		//Model rms st
		//rms = a / sqrt(2) 
		//y = a * sin( 2 * pi * f * t + phi) + b

		double rms(.1); // .1 rms vol
		double b(0.15);
		double a(rms* sqrt(2.0));
		double f(-.26);
		double phi(-0.05);

		unsigned long steps(3);

		double deltaT(Expiry / steps);

		//(i) function rapidly decreasing
		vector<double> vol_dec(steps + 1);


		for (size_t i(0); i < vol_dec.size(); ++i){
			vol_dec[i] = a * sin(2.0 * M_PI * f * deltaT * i + phi) + b;
		}

		cout << "UOC - OT - rapidly decreasing vol : ";
		cout << engine_uoc_ot.DoReplication(steps, vol_dec, Spot, t) << endl;

		//(ii) function rapidly increasing
		vector<double> vol_inc(steps + 1);
		b = 0.0;
		phi = 0.0;
		f = .3;

		for (size_t i(0); i < vol_inc.size(); ++i){
			vol_inc[i] = a * sin(2.0 * M_PI * f * deltaT * i + phi) + b;
		}

		cout << "UOC - OT - rapidly increasing vol : ";
		cout << engine_uoc_ot.DoReplication(steps, vol_inc, Spot, t) << endl;

		//(iii) function w/ bump in the middle
		vector<double> vol_bump(steps + 1);
		f = .5;

		for (size_t i(0); i < vol_bump.size(); ++i){
			vol_bump[i] = a * sin(2.0 * M_PI * f * deltaT * i + phi) + b;
		}

		cout << "UOC - OT - bumped vol : ";
		cout << engine_uoc_ot.DoReplication(steps, vol_bump, Spot, t) << endl;


		//Do the test w/
		//zero int rte
		OT->Setr(0.0);
		UOC->setRate(0.0);

		cout << "UOC - OT - rapidly decreasing vol - null int rte env : ";
		cout << engine_uoc_ot.DoReplication(steps, vol_dec, Spot, t) << endl;

		//small int rte  - 25 bps
		OT->Setr(0.0025);
		UOC->setRate(0.0025);

		cout << "UOC - OT - rapidly decreasing vol - low int rte env : ";
		cout << engine_uoc_ot.DoReplication(steps, vol_dec, Spot, t) << endl;

		//large int rte - 10 percnet 
		OT->Setr(0.1);
		UOC->setRate(0.1);

		cout << "UOC - OT - rapidly decreasing vol - high int rte env : ";
		cout << engine_uoc_ot.DoReplication(steps, vol_dec, Spot, t) << endl;

		

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