/*
Excercice 6.1 For various cases compare convergence of MC sim w/ and w/o anti-thetic sampling

For definition of antithetic var see notes, Numerical Methods II, Prof. Mike Giles, Oxford
http://people.maths.ox.ac.uk/~gilesm/mc/

For three cases, antithetic method achieves lower se and price computed is more stable over iteration.

*/

#include<SimpleMC8.h>
#include<ParkMiller.h>
#include<iostream>
#include <fstream>

#include<Vanilla3.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<AntiThetic.h>

#include<DoubleDigital2.h>

using namespace std;

int main()
{

	double Expiry_;
	double Strike;
	double Spot;
	double Vol_;
	double r_;
	unsigned long NumberOfPaths;

	cout << "\nEnter expiry\n";
	cin >> Expiry_;

	cout << "\nStrike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol_;

	cout << "\nr\n";
	cin >> r_;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	//construction of three different options call, put, double digital

	PayOffCall PayOffcall(Strike);
	PayOffPut PayOffput(Strike);
	PayOffDoubleDigital PayOffdouble_digital(Strike, Strike * 1.10);

	VanillaOption Optioncall(PayOffcall, Expiry_);
	VanillaOption Optionput(PayOffput, Expiry_);
	VanillaOption Option_double_digital(PayOffdouble_digital, Expiry_);

	ParametersConstant Vol(Vol_);
	ParametersConstant r(r_);

	StatisticsMean gatherer_mean;

	//exercice 6.1
	StatisticsSE gatherer_se;

	vector<Wrapper<StatisticsMC>> stat_vec;
	stat_vec.resize(2);
	stat_vec[0] = gatherer_mean;
	stat_vec[1] = gatherer_se;
	StatsGatherer gathererOne(stat_vec);

	StatsGatherer gathererTwo(stat_vec);

	StatsGatherer gathererThree(stat_vec);
	StatsGatherer gathererFour(stat_vec);

	StatsGatherer gathererFive(stat_vec);
	StatsGatherer gathererSix(stat_vec);


	//Generate convergence tables - antithetic vs non-antithetic

	//call
	ConvergenceTable gatherer1(gathererOne); //antithetic
	ConvergenceTable gatherer2(gathererTwo); //non-antithetic

	//put
	ConvergenceTable gatherer3(gathererThree); //antithetic
	ConvergenceTable gatherer4(gathererFour); //non-antithetic

	//double digital
	ConvergenceTable gatherer5(gathererFive); //antithetic
	ConvergenceTable gatherer6(gathererSix); //non-antithetic

	RandomParkMiller generator(1);

	generator.ResetDimensionality(1);

	cout << "computation starts" << endl;

	double Expiry = Optioncall.GetExpiry();
	double variance = Vol.IntegralSquare(0, Expiry);
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double movedSpot = Spot*exp(r.Integral(0, Expiry) + itoCorrection);

	double thisSpotplus;
	double thisSpotminus;
	double discounting = exp(-r.Integral(0, Expiry));

	MJArray VariateArray(1);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		generator.GetGaussians(VariateArray);

		thisSpotplus = movedSpot*exp(rootVariance*VariateArray[0]);
		thisSpotminus = movedSpot*exp(-1.0*rootVariance*VariateArray[0]);

		//call
		double thisPayOffplus = Optioncall.OptionPayOff(thisSpotplus);
		double thisPayOffminus = Optioncall.OptionPayOff(thisSpotminus);

		double thisPayOffavg = 0.5 * (thisPayOffplus + thisPayOffminus); //antithetic variable

		gatherer1.DumpOneResult(thisPayOffavg*discounting); //antithetic gatherer
		gatherer2.DumpOneResult(thisPayOffplus*discounting); //non-antithetic gatherer

		//put		
		thisPayOffplus = Optionput.OptionPayOff(thisSpotplus);
		thisPayOffminus = Optionput.OptionPayOff(thisSpotminus);

		thisPayOffavg = 0.5 * (thisPayOffplus + thisPayOffminus); //antithetic variable 

		gatherer3.DumpOneResult(thisPayOffavg*discounting); //antithetic gatherer
		gatherer4.DumpOneResult(thisPayOffplus*discounting); //non-antithetic gatherer

		//double digital		 
		thisPayOffplus = Option_double_digital.OptionPayOff(thisSpotplus);
		thisPayOffminus = Option_double_digital.OptionPayOff(thisSpotminus);

		thisPayOffavg = 0.5 * (thisPayOffplus + thisPayOffminus); //antithetic variable

		gatherer5.DumpOneResult(thisPayOffavg*discounting); //antithetic gatherer
		gatherer6.DumpOneResult(thisPayOffplus*discounting); //non-antithetic gatherer

	}

	//call
	vector<vector<double> > results1 = gatherer1.GetResultsSoFar(); //antithetic
	vector<vector<double> > results2 = gatherer2.GetResultsSoFar(); //non-antithetic

	//put
	vector<vector<double> > results3 = gatherer3.GetResultsSoFar(); //antithetic
	vector<vector<double> > results4 = gatherer4.GetResultsSoFar(); //non-antithetic

	//double digital
	vector<vector<double> > results5 = gatherer5.GetResultsSoFar(); //antithetic
	vector<vector<double> > results6 = gatherer6.GetResultsSoFar(); //non-antithetic

	//----------------------------------------------

	ofstream myfile;
	myfile.open("price.txt");



	myfile << "nb paths" << "," <<
		"vanilla anti call px" << "," << "vanilla anti call se" << "," << "vanilla call px" << "," << "vanilla call se" << "," <<
		"vanilla put anti px" << "," << "vanilla put anti se" << "," << "vanilla put px" << "," << "vanilla put se" << "," <<
		"double barrier anti px" << "," << "double barrier anti se" << "," << "double barrier px" << "," << "double barrier se" << "\n";

	for (unsigned long i = 0; i < results1.size(); i++)
	{
		myfile << results1[i][2] << "," <<
			results1[i][0] << "," << results1[i][1] << "," <<
			results2[i][0] << "," << results2[i][1] << "," <<
			results3[i][0] << "," << results3[i][1] << "," <<
			results4[i][0] << "," << results4[i][1] << "," <<
			results5[i][0] << "," << results5[i][1] << "," <<
			results6[i][0] << "," << results6[i][1] << "\n";
	}

	cout << "computation ended" << endl;
	myfile.close();

	double tmp;
	cin >> tmp;

	return 0;
}