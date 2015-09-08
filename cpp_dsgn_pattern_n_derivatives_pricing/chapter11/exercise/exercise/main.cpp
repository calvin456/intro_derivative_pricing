/*
//ex 11.1 Implement  the factory from chap. 10 using the monostate pattern
//instead of the Singleton pattern

Compare implementation of book example, curiuosly recurring template pattern , and monostate pattern

*/



#include <string>
#include <iostream>

#include <memory>

#include<SimpleMC8.h>
#include<ParkMiller.h>

#include<Vanilla3.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>

#include <PayOff3.h>
#include <PayOffBridge.h>

#include "PayOffConstructibleMono.h"
#include "PayOffFactoryMono.h"

#include <PayOffFactory.h>
#include <PayOffConstructible.h>

#include "PayOffConstructibleCRTP.h"
#include "PayOffFactoryCRTP.h"

using namespace std;

int main()
{

	double Expiry;
	double Strike;
	double Spot;
	double Vol;
	double r;
	unsigned long NumberOfPaths;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nStrike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	string name;

	cout << "\npay-off name\n";
	cin >> name;

	MJArray args(1); args[0] = Strike;
	//Singleton -  Meyers singleton
	PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(name, args);
	//Monostate
	unique_ptr<PayOff> PayOffPtr1 = PayOffFactoryMono().CreatePayOff(name, args);
	//14.2 Singleton + CRTP
	PayOff* PayOffPtr2 = PayOffFactoryCRTP::Instance().CreatePayOff(name, args);

	VanillaOption1 theOption(PayOffPtr, Expiry);
	VanillaOption1 theOption1(PayOffPtr1, Expiry);
	VanillaOption1 theOption2(PayOffPtr2, Expiry);

	ParametersConstant VolParam(Vol);
	ParametersConstant rParam(r);

	StatisticsMean gatherer_mean;
	StatisticsSE gatherer_se;

	vector<Wrapper<StatisticsMC>> stat_vec;
	stat_vec.resize(2);
	stat_vec[0] = gatherer_mean;
	stat_vec[1] = gatherer_se;
	StatsGatherer gathererOne(stat_vec);

	//Generate convergence table
	ConvergenceTable gatherer(gathererOne);

	RandomParkMiller generator(1);
	AntiThetic GenTwo(generator);

	SimpleMonteCarlo6_(theOption, Spot, VolParam, rParam, NumberOfPaths, gatherer, GenTwo);

	GenTwo.Reset();
	ConvergenceTable gatherer1(gathererOne);
	SimpleMonteCarlo6_(theOption1, Spot, VolParam, rParam, NumberOfPaths, gatherer1, GenTwo);

	GenTwo.Reset();
	ConvergenceTable gatherer2(gathererOne);
	SimpleMonteCarlo6_(theOption2, Spot, VolParam, rParam, NumberOfPaths, gatherer2, GenTwo);

	vector<vector<double> > results = gatherer.GetResultsSoFar();
	vector<vector<double> > results1 = gatherer1.GetResultsSoFar();
	vector<vector<double> > results2 = gatherer2.GetResultsSoFar();

	cout << "\nFor the " << name << " price the results are \n";
	cout << "with antithetic variables \n";
	cout << "mean\t se\t path\n";
	for (unsigned long i = 0; i < results1.size(); i++)
	{
		for (unsigned long j = 0; j < results1[i].size(); j++)
			cout << results1[i][j] << " ";

		cout << "\n";
	}



	double tmp;
	cin >> tmp;



	return 0;
}