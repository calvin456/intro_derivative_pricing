//main.cpp

//test option pricing via template class mc and tree

#include<PayOff3.h>
#include<SimpleMC8Template.h>
#include<ParkMiller.h>
#include<Vanilla3Template.cpp>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>
#include"TrinomialTreeTemplate.h"
#include"TreeEuropeanTemplate.cpp"

#include<iostream>
using namespace std;

int main()
{

	double Expiry;
	double Strike;
	double Spot;
	double Vol;
	double r;
	double d;
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

	cout << "\nd\n";
	cin >> d;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	PayOffCall thePayOff(Strike);

	//create template vanilla option class
	VanillaOptionTemplate<PayOffCall> theOption(thePayOff, Expiry);

	//test template class
	cout << endl;
	cout << "option expiry" << endl;
	cout << theOption.GetExpiry() << endl;

	cout << endl;
	cout << "option payoff" << endl;
	cout << theOption.OptionPayOff(Spot) << endl;

	ParametersConstant VolParam(Vol);
	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	//----------------------------------------------------------
	//mc pricing

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

	SimpleMonteCarlo61(theOption,
		Spot,
		VolParam,
		rParam,
		dParam,
		NumberOfPaths,
		gatherer,
		GenTwo);

	vector<vector<double> > results = gatherer.GetResultsSoFar();

	cout << "\nFor the call price the results are \n";
	cout << "with antithetic variables \n";
	cout << "mean\t se\t path\n";
	for (unsigned long i = 0; i < results.size(); i++)
	{
		for (unsigned long j = 0; j < results[i].size(); j++)
			cout << results[i][j] << " ";

		cout << "\n";
	}

	//--------------------------------------------------------------------
	//tree pricing

	unsigned long Steps;

	cout << "\nEnter steps\n";
	cin >> Steps;

	TreeEuropeanTemplate<PayOffCall> theProduct(Expiry, thePayOff);

	TrinomialTreeTemplate theTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	double euroPrice = theTree.GetThePrice(theProduct);

	cout << endl;
	cout << "Trinomial tree pricing vanilla European call option" << endl;
	cout << "euro price " << euroPrice << "\n";

	//--------------------------------------------------------------------

	double tmp;
	cin >> tmp;

	return 0;
}

