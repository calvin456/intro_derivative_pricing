//
//
//		EquityFXMain.cpp
//
//       
//
/*
    uses source files 
    AntiThetic.cpp
    Arrays.cpp,  
    ConvergenceTable.cpp, 
    ExoticBSEngine.cpp
    ExoticEngine
    MCStatistics.cpp
    Normals.cpp
    Parameters.cpp,
    ParkMiller.cpp,
    PathDependent.cpp
    PathDependentAsian.cpp
    PayOff3.cpp, 
    PayOffBridge.cpp,
    Random2.cpp,
  */

//Edit file to include exercise 7.1 and exercise 7.4

#include<ParkMiller.h>
#include<iostream>
using namespace std;
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>
#include<PathDependentAsian.h>

#include<PathDependentAsianGeo.h>


#include<ExoticBSEngine.h>
#include<ExoticNormalEngine.h>

int main()
{

	double Expiry;
	double Strike; 
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

    for (unsigned long i=0; i < NumberOfDates; i++)
        times[i] = (i+1.0)*Expiry/NumberOfDates;

    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

	
    PathDependentAsian theOption(times, Expiry, thePayOff);

	//Exercice 7.1 geometric Asian options
	PathDependentAsianGeo _theOption(times, Expiry, thePayOff);

    StatisticsMean gatherer;
    ConvergenceTable gathererTwo(gatherer);
	ConvergenceTable gathererTwo1(gatherer);
	ConvergenceTable gathererTwo2(gatherer);
	ConvergenceTable gathererTwo3(gatherer);

    RandomParkMiller generator(NumberOfDates);
    
    AntiThetic GenTwo(generator);

    ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot);
	ExoticBSEngine theEngine1(_theOption, rParam, dParam, VolParam, GenTwo, Spot);

	theEngine.DoSimulation(gathererTwo, NumberOfPaths);
	theEngine1.DoSimulation(gathererTwo1, NumberOfPaths);

	//Exercice 7.4 implementation of Normal model 
	ExoticNormalEngine _theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot);
	ExoticNormalEngine _theEngine1(_theOption, rParam, dParam, VolParam, GenTwo, Spot);

	_theEngine.DoSimulation(gathererTwo2, NumberOfPaths);
	_theEngine1.DoSimulation(gathererTwo3, NumberOfPaths);

    vector<vector<double> > results = gathererTwo.GetResultsSoFar();
	vector<vector<double> > results1 = gathererTwo1.GetResultsSoFar();
	vector<vector<double> > results2 = gathererTwo2.GetResultsSoFar();
	vector<vector<double> > results3 = gathererTwo3.GetResultsSoFar();

	cout << "For the Asian call price the results are \n";
	
	cout << "GBM process" << "\t " << "Bachelier model" << "\t " <<  "# of iterations" << endl;

    for (unsigned long i=0; i < results.size(); i++)
		cout << results[i][0] << "\t\t " << results2[i][0] << "\t\t " << results2[i][1] << endl; 
    
	cout << endl;

	cout << "For the Asian geometric call price the results are \n";

	cout << "GBM process" << "\t " << "Bachelier model" << "\t " <<  "# of iterations" << endl;

	for (unsigned long i = 0; i < results.size(); i++)
		cout << results1[i][0] << "\t\t " << results3[i][0] << "\t\t " << results3[i][1] << endl;

	cout << endl;

    double tmp;
    cin >> tmp;

	return 0;

}
