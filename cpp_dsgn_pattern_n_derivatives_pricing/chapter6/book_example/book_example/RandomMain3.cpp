//
//
//		RandomMain3.cpp
//
//       
//
/*
    uses source files 
    AntiThetic.cpp
    Arrays.cpp,  
    ConvergenceTable.cpp, 
    MCStatistics.cpp
    Normals.cpp
    Parameters.cpp,
    ParkMiller.cpp
    PayOff3.cpp, 
    PayOffBridge.cpp,
    Random2.cpp,
    SimpleMC8.cpp 
    Vanilla3.cpp, 
  */

//Edit file to include gatherer w/ standard error.

#include<SimpleMC8.h>
#include<ParkMiller.h>
#include<iostream>
using namespace std;
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

    PayOffCall thePayOff(Strike);

    VanillaOption theOption(thePayOff, Expiry);

    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);

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

    RandomParkMiller generator(1);
  
    AntiThetic GenTwo(generator);

	SimpleMonteCarlo6(theOption,
                                      Spot, 
                                      VolParam,
                                      rParam,
                                      NumberOfPaths,
                                      gatherer, 
                                      GenTwo);

   
	vector<vector<double> > results =gatherer.GetResultsSoFar();

	cout <<"\nFor the call price the results are \n";
	cout <<"with antithetic variables \n";
	cout <<"mean\t se\t path\n";
    for (unsigned long i=0; i < results.size(); i++)
    {
        for (unsigned long j=0; j < results[i].size(); j++)
            cout << results[i][j] << " ";

        cout << "\n";
    }

    double tmp;
    cin >> tmp;

	return 0;
}

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

