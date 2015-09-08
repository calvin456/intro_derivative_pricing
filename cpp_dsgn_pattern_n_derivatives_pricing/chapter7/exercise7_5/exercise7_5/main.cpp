//main.cpp

#include<ParkMiller.h>
#include<iostream>
using namespace std;
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>
#include<PathDependentAsian.h>

#include<PathDependentDifference.h>



#include<ExoticBSEngine.h>


int main()
{

	double Expiry;
	double Strike;
	double Strike1;

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

	cout << "\nStrike1\n";
	cin >> Strike1;

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

	PayOffCall thePayOff1(Strike1);

	MJArray times(NumberOfDates);

	for (unsigned long i = 0; i < NumberOfDates; i++)
		times[i] = (i + 1.0)*Expiry / NumberOfDates;

	ParametersConstant VolParam(Vol);
	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	//Exercise 7.5

	PathDependentAsian theOption1(times, Expiry, thePayOff);

	PathDependentAsian theOption2(times, Expiry, thePayOff1);

	Wrapper<PathDependent> theOption1_ = theOption1;

	Wrapper<PathDependent> theOption2_ = theOption2;

	//Merge times of the two derivatives 

	MJArray LookAtTimes1(theOption1_->GetLookAtTimes());
	MJArray LookAtTimes2(theOption2_->GetLookAtTimes());

	unsigned long size_ = theOption1_->GetLookAtTimes().size() + theOption2_->GetLookAtTimes().size();

	MJArray LookAtTimes_(size_);

	LookAtTimes_ = LookAtTimes1.merge(LookAtTimes2);

	LookAtTimes_.remove_duplicate();

	PathDependentDifference theOption(LookAtTimes_, theOption1_, theOption2_);

	StatisticsMean gatherer;
	ConvergenceTable gathererTwo(gatherer);

	RandomParkMiller generator(NumberOfDates);

	AntiThetic GenTwo(generator);

	ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot);

	theEngine.DoSimulation(gathererTwo, NumberOfPaths);

	vector<vector<double> > results = gathererTwo.GetResultsSoFar();

	cout << "\nFor the difference in pay-offs of two path-dependent derivatives the results are \n";
	cout << "mean" << "\t " << "# of iterations" << endl;
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