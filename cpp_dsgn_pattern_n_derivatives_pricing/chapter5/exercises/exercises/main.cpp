#include<iostream>
#include <cmath>
#include <vector>
#include <Random1.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
using namespace std;

int main(){

	unsigned long NumberOfPaths;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	StatisticsMean gatherer_mean;

	//exercice 5.1
	StatisticsMoments4 gatherer_m4;

	//exercice 5.2
	ValueAtRisk gatherer_var(0.05);

	//exercice 5.3
	//With current setup cannot use m4 class. Dimensions mistach
	vector<Wrapper<StatisticsMC>> stat_vec;
	stat_vec.resize(2);
	stat_vec[0] = gatherer_mean;
	stat_vec[1] = gatherer_var;
	StatsGatherer gatherer(stat_vec);

	//Generate convergence tables
	ConvergenceTable gathererOne(gatherer_m4);
	ConvergenceTable gathererTwo(gatherer);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		gathererOne.DumpOneResult(thisGaussian);
		gathererTwo.DumpOneResult(thisGaussian);
	}

	vector<vector<double> > results1 = gathererOne.GetResultsSoFar();
	vector<vector<double> > results2 = gathererTwo.GetResultsSoFar();

	cout << "\nconvergence table 1 results: \n";
	cout << "m1\t\t m2\t\t m3\t\t m4\t\t path\n";

	for (unsigned long i = 0; i < results1.size(); i++)
	{
		for (unsigned long j = 0; j < results1[i].size(); j++)
			cout << results1[i][j] << "\t ";

		cout << "\n";
	}

	cout << "\nconvergenc table 2 results: \n";
	cout << "mean\t\t var\t\t path\n";

	for (unsigned long i = 0; i < results2.size(); i++)
	{
		for (unsigned long j = 0; j < results2[i].size(); j++)
			cout << results2[i][j] << "\t ";

		cout << "\n";
	}

	double tmp;
	cin >> tmp;

	return 0;
}