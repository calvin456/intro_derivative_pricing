//test_log_normality.cpp



#include <cmath>
#include<fstream>
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
		cout << "computation starts" << endl;

		//log-nomrality of swap-rates
		//Price swaption using our bgm engine with variety of strike
		//volatility smile

		//price options 

		//tenors 1y, 5y, 10y
		//starting in 1y,5y, 10y

		//9 swaptions - assume as in testing part half-year reset

		unsigned long P(21), Q(61);double s(.002);

		//rate start in 1 year
		std::vector<double> times1(P);
		for (size_t j(0); j < P; ++j)
			times1[j] = 1.0 + j / 2.0;

		//intial curve is flat 	
		double r(0.05127);

		std::vector<double> zcps1(P);
		for (size_t j(0); j < P; ++j)
			zcps1[j] = exp(-r * times1[j]);

		std::vector<double> fwd_rtes1(P-1);
		for (size_t j(0); j < P-1; ++j)
			fwd_rtes1[j] = (zcps1[0] / zcps1[j + 1] - 1.0) / (times1[j + 1] - times1[0]);

		//----------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 1x1" << endl;
		
		double strike(0.04); //set 4% as initial stike rate

		std::vector<double> times11(3);

		times11.assign(times1.begin(), times1.end() - 18);

		std::vector<double> fwd_rtes11(2);

		fwd_rtes11.assign(fwd_rtes1.begin(), fwd_rtes1.end() - 17);

		cout << "annuity " << annuity_swap(fwd_rtes11,times11,0,2-1);
		
		cout << ", swap rate spot " << swap_rate(fwd_rtes11,times11,0,2-1) << endl;

		shared_ptr<BGMProducts> swaption11(new Swaption(times11, strike)); //swaption tenor 1yr starting 1yr

		//vol struct1 
		//define fwd vol structure
		double a(0.05), b(0.09), c(0.44), d(0.11);

		double beta(0.1);

		FwdVolStructure1 vol_struct1(a, b, c, d, beta);

		//generator - 2 rtes
		
		shared_ptr<RandomBase> generator2(new RandomMersenneTwister(swaption11->GetUnderlyingTimes().size() - 1));

		TheEngine engine_swaption11(swaption11, vol_struct1, generator2, fwd_rtes1, times1, .25, 2, zcps1[2]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 2 bps up to 800 bps
		
		std::vector<double> price_swaption11(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption11[j] = engine_swaption11.DoSimulation(1000, PC);
			swaption11->setStrike(strike + s * (j + 1));
		}

		//-----------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 1x5" << endl;
		
		strike = 0.04;

		std::vector<double> times15(11);

		times15.assign(times1.begin(), times1.end() -10); 

		std::vector<double> fwd_rtes15(10);

		fwd_rtes15.assign(fwd_rtes1.begin(), fwd_rtes1.end() - 9);

		cout << "annuity " << annuity_swap(fwd_rtes15, times15, 0, 9-1);

		cout << ", swap rate spot " << swap_rate(fwd_rtes15, times15, 0, 9-1) << endl;

		shared_ptr<BGMProducts> swaption15(new Swaption(times15, strike)); //swaption tenor 5yr starting 1 yr

		//generator - 10 rtes
		shared_ptr<RandomBase> generator10(new RandomMersenneTwister(swaption15->GetUnderlyingTimes().size() - 1));

		TheEngine engine_swaption15(swaption15, vol_struct1, generator10, fwd_rtes1, times1, 2.5, 9, zcps1[10]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 1 bp up to 800 bps
		std::vector<double> price_swaption15(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption15[j] = engine_swaption15.DoSimulation(1000, PC);
			swaption15->setStrike(strike + s * (j + 1));
		}

		//----------------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 1x10" << endl;
		
		strike = 0.04;

		cout << "annuity " << annuity_swap(fwd_rtes1, times1, 0, 19-1);

		cout << ", swap rate spot " << swap_rate(fwd_rtes1, times1, 0, 19-1) << endl;

		shared_ptr<BGMProducts> swaption110(new Swaption(times1, strike)); //swaption tenor 10yr starting 1 yr

		//generator - P rtes
		shared_ptr<RandomBase> generatorP(new RandomMersenneTwister(swaption110->GetUnderlyingTimes().size() - 1));

		TheEngine engine_swaption110(swaption110, vol_struct1, generatorP, fwd_rtes1, times1, 5.0, 19, zcps1[20]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 1 bp up to 800 bps
		std::vector<double> price_swaption110(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption110[j] = engine_swaption110.DoSimulation(1000, PC);
			swaption110->setStrike(strike + s * (j + 1));
		}

		//-------------------------------------------------------------------------------------------------------------------------------------
		//rate start in 5 years
		std::vector<double> times5(P);
		for (size_t j(0); j < P; ++j)
			times5[j] = 5.0 + j / 2.0;

		//intial curve is flat 
		r = 0.056805;

		std::vector<double> zcps5(P);
		for (size_t j(0); j < P; ++j)
			zcps5[j] = exp(r*-times1[j]);

		std::vector<double> fwd_rtes5(P-1);
		for (size_t j(0); j < P-1; ++j)
			fwd_rtes5[j] = (zcps5[0] / zcps5[j + 1] - 1.0) / (times5[j + 1] - times5[0]);

		//-------------------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 5x1" << endl;
		
		strike = 0.04;

		std::vector<double> times51(3);

		times51.assign(times5.begin(), times5.end() - 18);

		std::vector<double> fwd_rtes51(2);

		fwd_rtes51.assign(fwd_rtes5.begin(), fwd_rtes5.end() -17);

		cout << "annuity " << annuity_swap(fwd_rtes51, times51, 0, 2-1);

		cout << ", swap rate spot " << swap_rate(fwd_rtes51, times51, 0, 2-1) << endl;

		shared_ptr<BGMProducts> swaption51(new Swaption(times51, strike)); //swaption tenor 1yr starting 5 yr

		generator2->Reset();

		TheEngine engine_swaption51(swaption51, vol_struct1, generator2, fwd_rtes5, times5, .25, 2, zcps5[2]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 1 bp up to 800 bps
		std::vector<double> price_swaption51(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption51[j] = engine_swaption51.DoSimulation(1000, PC);
			swaption51->setStrike(strike + s * (j + 1));
		}

		//------------------------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 5x5" << endl;
		
		strike = 0.04;

		std::vector<double> times55(11);

		times55.assign(times5.begin(), times5.end() - 10);

		std::vector<double> fwd_rtes55(10);

		fwd_rtes55.assign(fwd_rtes5.begin(), fwd_rtes5.end() - 9);

		cout << "annuity " << annuity_swap(fwd_rtes55, times55, 0, 9-1);

		cout << ", swap rate spot " << swap_rate(fwd_rtes55, times55, 0, 9-1) << endl;

		shared_ptr<BGMProducts> swaption55(new Swaption(times55, strike)); //swaption tenor 5yr starting 5 yr



		generator10->Reset();

		TheEngine engine_swaption55(swaption55, vol_struct1, generator10, fwd_rtes5, times5, 2.5, 9, zcps5[10]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 1 bp up to 800 bps
		std::vector<double> price_swaption55(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption55[j] = engine_swaption55.DoSimulation(1000, PC);
			swaption55->setStrike(strike + s * (j + 1));
		}

		//------------------------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 5x10" << endl;
		
		strike = 0.04;

		cout << "annuity " << annuity_swap(fwd_rtes5, times5, 0, 19-1);

		cout << ", swap rate spot " << swap_rate(fwd_rtes5, times5, 0, 19-1) << endl;

		shared_ptr<BGMProducts> swaption510(new Swaption(times5, strike)); //swaption tenor 5yr starting 5 yr

		generatorP->Reset();

		TheEngine engine_swaption510(swaption510, vol_struct1, generatorP, fwd_rtes5, times5, 5.0, 19, zcps5[20]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 1 bp up to 800 bps
		std::vector<double> price_swaption510(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption510[j] = engine_swaption510.DoSimulation(1000, PC);
			swaption510->setStrike(strike + s * (j + 1));
		}

		//------------------------------------------------------------------------------------------------------------------------------------------
		//rate start in 10 years
		std::vector<double> times10(P);
		for (size_t j(0); j < P; ++j)
			times10[j] = 10.0 + j / 2.0;

		//intial curve is flat 
		r = 0.064872;

		std::vector<double> zcps10(P);
		for (size_t j(0); j < P; ++j)
			zcps10[j] = exp(r*-times1[j]);

		std::vector<double> fwd_rtes10(P-1);
		for (size_t j(0); j < P-1; ++j)
			fwd_rtes10[j] = (zcps10[0] / zcps10[j + 1] - 1.0) / (times10[j + 1] - times10[0]);

		//------------------------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 10x1" << endl;
		
		strike = 0.04;

		std::vector<double> times101(3);

		times101.assign(times10.begin(), times10.end() - 18);

		std::vector<double> fwd_rtes101(2);

		fwd_rtes101.assign(fwd_rtes5.begin(), fwd_rtes5.end() - 17);

		cout << "annuity " << annuity_swap(fwd_rtes101, times101, 0, 2-1);

		cout << ", swap rate spot " << swap_rate(fwd_rtes101, times101, 0, 2-1) << endl;


		shared_ptr<BGMProducts> swaption101(new Swaption(times101, strike)); //swaption tenor 1yr starting 10 yr

		generator2->Reset();

		TheEngine engine_swaption101(swaption101, vol_struct1, generator2, fwd_rtes10, times10, .25, 2, zcps10[2]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 1 bp up to 800 bps
		std::vector<double> price_swaption101(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption101[j] = engine_swaption101.DoSimulation(1000, PC);
			swaption101->setStrike(strike + s * (j + 1));
		}

		//------------------------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 10x5" << endl;
		
		strike = 0.04;

		std::vector<double> times105(11);

		times105.assign(times10.begin(), times10.end() - 10);

		std::vector<double> fwd_rtes105(10);

		fwd_rtes105.assign(fwd_rtes5.begin(), fwd_rtes5.end() - 9);

		cout << "annuity " << annuity_swap(fwd_rtes105, times105, 0, 9-1);

		cout << ", swap rate spot " << swap_rate(fwd_rtes105, times105, 0, 9-1) << endl;

		shared_ptr<BGMProducts> swaption105(new Swaption(times105, strike)); //swaption tenor 5yr starting 10 yr

		generator10->Reset();

		TheEngine engine_swaption105(swaption105, vol_struct1, generator10, fwd_rtes10, times10, 2.5, 9, zcps10[10]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 1 bp up to 800 bps
		std::vector<double> price_swaption105(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption105[j] = engine_swaption105.DoSimulation(1000, PC);
			swaption105->setStrike(strike + s * (j + 1));
		}

		//------------------------------------------------------------------------------------------------------------------------------------------
		cout << "swaption 10x10" << endl;
		
		strike = 0.04;

		cout << "annuity " << annuity_swap(fwd_rtes10, times10, 0, 19-1);

		cout << ", swap rate spot " << swap_rate(fwd_rtes10, times10, 0, 19-1) << endl;

		shared_ptr<BGMProducts> swaption1010(new Swaption(times10, strike)); //swaption tenor 10yr starting 10 yr

		generatorP->Reset();

		TheEngine engine_swaption1010(swaption1010, vol_struct1, generatorP, fwd_rtes10, times10, 5.0, 19, zcps10[20]);
		//use final zcp as numéraire

		//calculate swaption price starting w/ strike 400 bps and increase by 1 bp up to 800 bps
		std::vector<double> price_swaption1010(Q);
		for (size_t j(0); j < Q; ++j){
			price_swaption1010[j] = engine_swaption1010.DoSimulation(1000, PC);
			swaption1010->setStrike(strike + s * (j + 1));
		}

		//------------------------------------------------------------------------------------------------------------------------------------------
		//stock rates into csv file
		//compute implied vol on spreadsheet
		ofstream myfile;
		myfile.open("swaption_rates.csv");

		myfile << "strike" << ", " << "1x1" << ", " << "1x5" << ", " << "1x10" << ", " << "5x1" << ", " << "5x5" << ", " << "5X10"
			<< ", " << "10X1" << ", " << "10X5" << ", " << "10X10" << endl;

		for (size_t i(0); i < P; ++i){
			myfile << strike << ", "; //strike
			myfile << price_swaption11[i] << ", "; //1x1
			myfile << price_swaption15[i] << ", "; //1x5
			myfile << price_swaption110[i] << ", "; //1x10
			myfile << price_swaption51[i] << ", "; //5x1
			myfile << price_swaption55[i] << ", "; //5x5
			myfile << price_swaption510[i] << ", "; //5x10
			myfile << price_swaption101[i] << ", "; //10x1
			myfile << price_swaption105[i] << ", "; //10x5
			myfile << price_swaption1010[i] << endl; //10x10
			strike += s;
		}
	
		myfile.close();

		cout << "computation end" << endl;

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