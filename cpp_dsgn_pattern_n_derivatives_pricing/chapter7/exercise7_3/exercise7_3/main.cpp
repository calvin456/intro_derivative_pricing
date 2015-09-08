//main.cpp

/*
ex 7.3 test log of spot values
*/
//#pragma warning (disable : 4996)
//#define _CRT_SECURE_NO_DEPRECATE

#include<ParkMiller.h>
#include<iostream>
using namespace std;
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>

#include<PathDependentAsian.h>
#include<PathDependentAsianGeo.h>

#include<PathDependentDiscreteKnockOut.h>


#include<ExoticBSEngine.h>

#include <ctime>

int main()
{

	double Expiry(1.0);
	double Strike(100.0);

	double Barrier(Strike * 1.10);
	double Rebate(10.0);

	double Spot(100.0);
	double Vol(.1);
	double r(.05);
	double d(.03);
	unsigned long NumberOfPaths(static_cast<unsigned long>(1e05));
	unsigned NumberOfDates(12);

	PayOffCall thePayOff(Strike);

	MJArray times(NumberOfDates);

	for (unsigned long i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;

	ParametersConstant VolParam(Vol);
	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	StatisticsMean gatherer_mean;
	StatisticsSE gatherer_se;

	vector<Wrapper<StatisticsMC>> stat_vec;
	stat_vec.resize(2);
	stat_vec[0] = gatherer_mean;
	stat_vec[1] = gatherer_se;
	StatsGatherer gathererOne(stat_vec);

	//Generate convergence table
	ConvergenceTable gathererTwo(gathererOne);

	RandomParkMiller generator(NumberOfDates);

	AntiThetic GenTwo(generator);

	//-------------------------------------------------------------------
	//Geometric Asian option

	PathDependentAsian theOption(times, Expiry, thePayOff);

	ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot);

	theEngine.DoSimulation(gathererTwo, NumberOfPaths);

	vector<vector<double> > results = gathererTwo.GetResultsSoFar();

	//-------------------------------------------------------------------
	//Geometric Asian option log

	ConvergenceTable gathererTwo1(gathererOne);

	GenTwo.Reset();

	PathDependentAsianGeo theOption1(times, Expiry, thePayOff);

	ExoticBSEngine theEngine1(theOption1, rParam, dParam, VolParam, GenTwo, Spot);

	theEngine1.DoSimulation(gathererTwo1, NumberOfPaths);

	vector<vector<double> > results1 = gathererTwo1.GetResultsSoFar();

	//-------------------------------------------------------------------
	//discrete barrier option

	ConvergenceTable gathererTwo2(gathererOne);

	GenTwo.Reset();

	PathDependentDiscreteKnockOut theOption2(times, Expiry, Barrier, thePayOff);

	ExoticBSEngine theEngine2(theOption2, rParam, dParam, VolParam, GenTwo, Spot);

	theEngine2.DoSimulation(gathererTwo2, NumberOfPaths);

	vector<vector<double> > results2 = gathererTwo2.GetResultsSoFar();
	//-------------------------------------------------------------------

	cout << "\nFor the Asian arithmetic call price the results are - log values : " << endl;
	cout << "mean" << "\t " << "se" << "\t\t " << "# of it" << endl;
	for (unsigned long i = 0; i < results.size(); i++){
		for (unsigned long j = 0; j < results[i].size(); j++)	cout << results[i][j] << "\t ";
		cout << "\n";
	}

	cout << endl;

	cout << "\nFor the Asian geometric call price the results are - log values : " << endl;
	cout << "mean" << "\t " << "se" << "\t\t " << "# of it" << endl;
	for (unsigned long i = 0; i < results1.size(); i++){
		for (unsigned long j = 0; j < results1[i].size(); j++)	cout << results1[i][j] << "\t ";
		cout << "\n";
	}

	cout << endl;

	cout << "\nFor the discrete knock-out call price the results are - log values : " << endl;
	cout << "mean" << "\t " << "se" << "\t\t " << "# of it" << endl;
	for (unsigned long i = 0; i < results2.size(); i++){
		for (unsigned long j = 0; j < results2[i].size(); j++)	cout << results2[i][j] << "\t ";
		cout << "\n";
	}

	cout << endl;


	double tmp;
	cin >> tmp;

	return 0;

}