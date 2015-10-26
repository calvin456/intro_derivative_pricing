// main.cpp

//test Margrabe and quanto options.

#include <iostream>
#include <cmath>
#include <Normals.h>
#include <Parameters.h>
#include <Arrays.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>
#include <BlackScholesFormulas.h>
#include <quanto_margrabe.h>
#include <BSCallTwo.h>
#include <NumericalIntegration.h>
#include <NumericalRule.h>
#include <NewtonRaphson.h>
#include <path_generation_multi.h>
#include <engine_multi.h>
#include <PayOffMulti.h>
#include <Vanilla3Template.cpp>
#include <MCStatistics.h>
#include <ConvergenceTable.h>

using namespace std;
using namespace BSFunction;

int main(){

	try{

		//ATM quanto 3-mth option EURUSD

		//Quanto options assume fixed FX rate to be 1 

		double Spot(100.0); //100.0
		double Strike(100.0);
		double rd(0.05);
		double rf(0.06); //interest rate of foreign currency
		double d(0.00); //dvd yield
		double VolS(.20); //vol stock price 
		double VolQ(.30); //vol foreign currency
		double correl(-.5); // correl(-.5);
		double Expiry(.25);

		cout << "quanto call option analytical : ";
		cout << QuantCallOption(Spot, Strike, rd, rf, d, VolS, VolQ, correl, Expiry) << endl;

		cout << "quanto put option analytical : ";
		cout << QuantPutOption(Spot, Strike, rd, rf, d, VolS, VolQ, correl, Expiry) << endl;

		//Margrabe option

		double Spot2(90.0);
		double Vol2(.25);

		double margrabe_price(MargrabeOptions(Spot, Spot2, VolS, Vol2, correl, Expiry));
		cout << "Margrabe option analytical : ";
		cout << margrabe_price << endl; cout << endl;

		//-----------------------------------------------------------------------------------

		//use of mc pricer with template class

		QuantoCall thePayOff(Strike);
		QuantoPut thePayOff1(Strike);
		ExchangeOption thePayOff2;

		PayOffCall thePayOff3(Strike);

		//create template vanilla option class
		VanillaOptionTemplate<QuantoCall> theOption(thePayOff, Expiry);
		VanillaOptionTemplate<QuantoPut> theOption1(thePayOff1, Expiry);
		VanillaOptionTemplate<ExchangeOption> theOption2(thePayOff2, Expiry);

		ParametersConstant rParam(rd);

		//----------------------------------------------------------
		//mc pricing

		StatisticsMean gatherer_mean;
		StatisticsSE gatherer_se;

		std::vector<Wrapper<StatisticsMC>> stat_vec;
		stat_vec.resize(2);
		stat_vec[0] = gatherer_mean;
		stat_vec[1] = gatherer_se;
		StatsGatherer gathererOne(stat_vec);

		ConvergenceTable gatherer(gathererOne);

		StatisticsKeepTrack _gatherer_time;

		ConvergenceTable gatherer_time(_gatherer_time);

		RandomMersenneTwister generator_(2);
	
		shared_ptr<RandomBase> generator(new AntiThetic(generator_));

		MJArray Spot0(2);
		Spot0[0] = Spot;
		Spot0[1] = 1.0;

		MJArray  r0(2);
		r0[0] = rd;
		r0[1] = rf;

		matrix<double> cov(2, 2);
		cov(0, 0) = VolS * VolS;
		cov(1, 1) = VolQ * VolQ;
		cov(1, 0) = VolS * VolQ * correl;
		cov(0, 1) = cov(1, 0);
		
		unsigned long steps(static_cast<unsigned long> (1e00));

		shared_ptr<PathGenerationMulti> ThePaths(new PathGenerationMulti(generator,
			Spot0, Expiry, r0, steps, cov));
		
		unsigned long NumberOfPaths(static_cast<unsigned long> (1e05));
		
		mc_pricer_multi(theOption, rParam, ThePaths, NumberOfPaths, gatherer, gatherer_time);

		std::vector<std::vector<double> > results = gatherer.GetResultsSoFar();
		std::vector<std::vector<double> > results1 = gatherer_time.GetResultsSoFar();

		cout << "step : 1" << endl;
		cout << "\nFor the quanto call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << "\t ";

			cout << results1[i][0] << "\t ";
			cout << "\n";


		}
		cout << endl;
		//---------------------------------------------------------------------------
		steps = static_cast<unsigned long> (1e02);

		ThePaths->SetSteps(steps);
		ConvergenceTable gatherer1(gathererOne);

		ConvergenceTable gatherer_time1(_gatherer_time);

		mc_pricer_multi(theOption, rParam, ThePaths, NumberOfPaths, gatherer1, gatherer_time1);

		std::vector<std::vector<double> > results2 = gatherer1.GetResultsSoFar();
		std::vector<std::vector<double> > results3 = gatherer_time1.GetResultsSoFar();

		cout << "step : 100" << endl;
		cout << "\nFor the quanto call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results2.size(); i++)
		{
			for (unsigned long j = 0; j < results2[i].size(); j++)
				cout << results2[i][j] << "\t ";

			cout << results3[i][0] << "\t ";
			cout << "\n";
		}
		cout << endl;
		
		//---------------------------------------------------------------------------
		
		steps = static_cast<unsigned long> (1e00);

		ThePaths->SetSteps(steps);

		ConvergenceTable gatherer2(gathererOne);

		ConvergenceTable gatherer_time2(_gatherer_time);

		mc_pricer_multi(theOption1, rParam, ThePaths, NumberOfPaths, gatherer2, gatherer_time2);

		std::vector<std::vector<double> > results4 = gatherer2.GetResultsSoFar();
		std::vector<std::vector<double> > results5 = gatherer_time2.GetResultsSoFar();

		cout << "\nFor the quanto put price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results4.size(); i++)
		{
			for (unsigned long j = 0; j < results4[i].size(); j++)
				cout << results4[i][j] << "\t ";

			cout << results5[i][0] << "\t ";
			cout << "\n";
		}
		cout << endl;

		//---------------------------------------------------------------------------

		MJArray Spot01(2);
		Spot01[0] = Spot;
		Spot01[1] = Spot2;

		MJArray  r1(2);
		r1[0] = .05;
		r1[1] = .05;

		matrix<double> cov1(2, 2);
		cov1(0, 0) = VolS * VolS;
		cov1(1, 1) = Vol2 * Vol2;
		cov1(1, 0) = VolS * Vol2 * correl;
		cov1(0, 1) = cov1(1, 0);

		generator->Reset();

		shared_ptr<PathGenerationMulti> ThePaths1(new PathGenerationMulti(generator,
			Spot01, Expiry, r1, steps, cov1));

		ConvergenceTable gatherer3(gathererOne);

		ConvergenceTable gatherer_time3(_gatherer_time);

		mc_pricer_multi(theOption2, rParam, ThePaths1, NumberOfPaths, gatherer3, gatherer_time3);

		std::vector<std::vector<double> > results6 = gatherer3.GetResultsSoFar();
		std::vector<std::vector<double> > results7 = gatherer_time3.GetResultsSoFar();

		cout << "\nFor the Margrabe option price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results6.size(); i++)
		{
			for (unsigned long j = 0; j < results6[i].size(); j++)
				cout << results6[i][j] << "\t ";

			cout << results7[i][0] << "\t ";
			cout << "\n";
		}
		cout << endl;
		//-----------------------------------------------------------------------------------

		//Compute implied correlation used in the Margrabe price through implied volatilities

		//implied correl = (implied vol exchange option^2 - implied vol s1 ^2 - implied vol s2 ^2)/ 2 * implied vol s1 * implied vol s2

		double tolerance(1e-6);
		double start(.3);

		BSCallTwo theCall0(0.0, 0.0, Expiry, Spot, Spot2);

		double implied_vol0 = NewtonRaphson<BSCallTwo, &BSCallTwo::Price, &BSCallTwo::Vega>(margrabe_price,
			start,
			tolerance,
			theCall0);

		cout << "vol used to compute Margrabe option price : ";
		cout << sqrt(VolS * VolS + Vol2 * Vol2 - 2.0 * correl * VolS * Vol2) << endl;
		cout << "implied vol Margrabe option : " << implied_vol0 << endl;

		double Price1(BlackScholesCall(Spot, Strike, rd, 0.0, VolS, Expiry));

		BSCallTwo theCall1(rd, 0.0, Expiry, Spot, Strike);

		double implied_vol1 = NewtonRaphson<BSCallTwo, &BSCallTwo::Price, &BSCallTwo::Vega>(Price1,
			start,
			tolerance,
			theCall1);

		cout << "implied vol s1 option : " << implied_vol1 << endl;

		double Price2(BlackScholesCall(Spot2, Spot2, rd, 0.0, Vol2, Expiry));

		BSCallTwo theCall2(rd, 0.0, Expiry, Spot2, Spot2);

		double implied_vol2 = NewtonRaphson<BSCallTwo, &BSCallTwo::Price, &BSCallTwo::Vega>(Price2,
			start,
			tolerance,
			theCall2);

		cout << "implied vol s2 option : " << implied_vol2 << endl;

		double implied_correl(-(implied_vol0 * implied_vol0 - implied_vol1 * implied_vol1 - implied_vol2 * implied_vol2) /
			(2.0 * implied_vol1 * implied_vol2));

		cout << "implied correlation :" << implied_correl << endl;

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