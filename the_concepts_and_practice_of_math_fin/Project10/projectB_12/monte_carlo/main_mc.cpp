// main_mc.cpp

//project 10. LIBOR-in-arrears
//implement the following pricers
//i. analytical pricer arrers FRA
//ii. numeric integration pricer arrears FRA
//iii. " " " arrears caplet
//iv MC pricer for FRA and caplet using t1 bond as numéraire

//change of numeraire
//implement MC pricer for FRA and caplet using t0 bond as numéraire
//Euler integration method 
//predictor-corrector ex. 14.6

#include<payoff_interest_derivatives.h>
#include"MC.h"
#include<interest_derivatives_analytical.h>
#include<ParkMiller.h>
#include<MersenneTwister.h>

#include<iostream>
#include<Vanilla3.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>

using namespace std;

int main(int argc, char **argv) {

	try {

		//double Expiry(.5);
		double Strike(.07);
		double Fwd(.06);
		double Vol(.20);
		double t0(10.0);
		double t1(10.5);
		unsigned long NumberOfPaths(1000000);

		//project 10 price caplet and FRA
		//price a FRA and caplet starting in ten 10 years current fwd rate .06, strike .07, vol .2,
		//price of the zcp expiring in ten years .5 
		//and they are both of lenght .5

		cout << "caplet - not in-arrear : " << endl;

		cout << "analytical solution ";

		cout << black_formula_caplet(.5, Fwd, 10.0, 10.5, Strike, Vol) << endl;

		CapletIA thePayOff(Strike, t0, t1);

		VanillaOption theOption(thePayOff, t1 - t0);

		ParametersConstant VolParam(Vol);

		//StatisticsMean gatherer;
		//ConvergenceTable gathererTwo(gatherer);

		StatisticsMean gatherer_mean;

		//exercice 6.1
		StatisticsSE gatherer_se;

		vector<Wrapper<StatisticsMC>> stat_vec;
		stat_vec.resize(2);
		stat_vec[0] = gatherer_mean;
		stat_vec[1] = gatherer_se;
		StatsGatherer gathererOne(stat_vec);

		//Generate convergence table
		ConvergenceTable gatherer(gathererOne);

		//RandomParkMiller generator(1);
		RandomMersenneTwister generator(1);

		AntiThetic GenTwo(generator);

		SimpleMonteCarloP1(theOption, Fwd, t0, t1, VolParam, NumberOfPaths, gatherer, GenTwo);


		vector<vector<double> > results = gatherer.GetResultsSoFar();

		cout << endl << "Use the fwd as numméraire" << endl;
		cout << "\nFor the caplet price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << "\t ";

			cout << "\n";
		}

		ConvergenceTable gatherer1(gathererOne);
		//SimpleMonteCarloP2(theOption, EULER, Fwd, t0, t1, VolParam, NumberOfPaths, gatherer1, GenTwo);

		SimpleMonteCarloP2(theOption, PC, Fwd, t0, t1, VolParam, NumberOfPaths, gatherer1, GenTwo);

		vector<vector<double> > results1 = gatherer1.GetResultsSoFar();

		cout << endl << "Use the spot as numméraire" << endl;
		cout << "\nFor the caplet price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results1.size(); i++)
		{
			for (unsigned long j = 0; j < results1[i].size(); j++)
				cout << results1[i][j] << "\t ";

			cout << "\n";
		}
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