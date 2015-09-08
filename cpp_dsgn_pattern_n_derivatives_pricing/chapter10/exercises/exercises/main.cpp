/*
ex. 10.2 Handle multi parameters

ex. 10.3 Integrate the factory w/a mc routine

*/

#include <string>
#include <iostream>

#include <PayOff3.h>
#include <PayOffConstructible.h>
#include <PayOffBridge.h>
#include <PayOffFactory.h>

#include<SimpleMC8.h>
#include<ParkMiller.h>

#include<Vanilla3.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>

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
	/*
	std::string name;

	cout << "\npay-off name\n";
	cin >> name;
	*/

	string call("call");
	string put("put");
	string straddle("straddle");
	string doubleDigital("double digital");


	MJArray args(1); args[0] = Strike;
	MJArray args1(2); args1[0] = .9 * Strike; args1[1] = 1.1 * Strike;

	PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(call, args);
	PayOff* PayOffPtr1 = PayOffFactory::Instance().CreatePayOff(doubleDigital, args1);

	//PayOff* PayOffPtr1 = new PayOffDoubleDigital(Strike * .9, Strike * 1.1);
	//PayOff* PayOffPtr = PayOffHelper<PayOffCall>::Create(Strike);

	VanillaOption1 theOption(PayOffPtr, Expiry);
	VanillaOption1 theOption1(PayOffPtr1, Expiry);

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

	vector<vector<double> > results = gatherer.GetResultsSoFar();

	cout << "\nFor the " << call << " price the results are \n";
	cout << "with antithetic variables \n";
	cout << "mean\t se\t\t path\n";
	for (unsigned long i = 0; i < results.size(); i++)
	{
		for (unsigned long j = 0; j < results[i].size(); j++)
			cout << results[i][j] << "\t ";

		cout << "\n";
	}

	GenTwo.Reset();
	ConvergenceTable gatherer1(gathererOne);

	SimpleMonteCarlo6_(theOption1, Spot, VolParam, rParam, NumberOfPaths, gatherer1, GenTwo);

	vector<vector<double> > results1 = gatherer1.GetResultsSoFar();

	cout << "\nFor the " << doubleDigital << " price the results are \n";
	cout << "with antithetic variables \n";
	cout << "mean\t se\t\t path\n";
	for (unsigned long i = 0; i < results1.size(); i++)
	{
		for (unsigned long j = 0; j < results1[i].size(); j++)
			cout << results1[i][j] << "\t ";

		cout << "\n";
	}

	double tmp;
	cin >> tmp;

	return 0;
}