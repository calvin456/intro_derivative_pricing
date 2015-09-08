//main.cpp

// Exercice 7.2. Test discrete KO option w/ rebate.

#include<ParkMiller.h>
#include<iostream>
using namespace std;
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>
#include<BarrierOption.h>

#include<PathDependentDiscreteKnockOut.h>



#include<ExoticBSEngine.h>
int main()
{

	double Expiry;
	double Strike;

	double Barrier;
	double Rebate;

	double Spot;
	double Vol;
	double r;
	double d;
	unsigned long NumberOfPaths;
	unsigned NumberOfDates;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nStrike\n";
	cin >> Strike;

	cout << "\nBarrier\n";
	cin >> Barrier;

	cout << "\nRebate\n";
	cin >> Rebate;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nd\n";
	cin >> d;

	cout << "\nNumber of dates\n";
	cin >> NumberOfDates;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	PayOffCall thePayOff(Strike);

	MJArray times(NumberOfDates);

	for (unsigned long i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;

	ParametersConstant VolParam(Vol);
	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	//Exercice 7.2 discrete knock-out call price
	PathDependentDiscreteKnockOut  theOption(times, Expiry, Barrier, thePayOff);

	StatisticsMean gatherer;
	ConvergenceTable gathererTwo(gatherer);

	RandomParkMiller generator(NumberOfDates);

	AntiThetic GenTwo(generator);

	ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot);

	theEngine.DoSimulation(gathererTwo, NumberOfPaths);

	vector<vector<double> > results = gathererTwo.GetResultsSoFar();

	cout << "\nFor the discrete knock-out call price the results are \n";
	cout << "with antithetic variables \n";
	cout << "mean\t path\n";

	for (unsigned long i = 0; i < results.size(); i++)
	{
		for (unsigned long j = 0; j < results[i].size(); j++)
			cout << results[i][j] << "\t ";

		cout << "\n";
	}

	double tmp;
	cin >> tmp;

	return 0;

}
