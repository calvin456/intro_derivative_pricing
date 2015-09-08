//main.cpp

//Test encapsulation of Boost's MT rng in current framework

#include<iostream>
#include<vector>

#include<ParkMiller.h>
#include<MersenneTwister.h>
#include<AntiThetic.h>

using namespace std;

int main(){

	unsigned long NumberOfPaths;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	RandomParkMiller generator(1);
	RandomMersenneTwister generator1(1);
	
	generator.ResetDimensionality(1);
	generator1.ResetDimensionality(1);

	MJArray VariateArray(1);
	MJArray VariateArray1(1);

	vector<double> results(NumberOfPaths);
	vector<double> results1(NumberOfPaths);
	vector<double> results2(NumberOfPaths);
	vector<double> results3(NumberOfPaths);

	cout << "\n";

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		generator.GetGaussians(VariateArray);
		generator1.GetGaussians(VariateArray1);
		results[i] = VariateArray[0];
		results1[i] = VariateArray1[0];

	}

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		generator.GetGaussians(VariateArray);
		generator1.GetGaussians(VariateArray1);
		results2[i] = VariateArray[0];
		results3[i] = VariateArray1[0];

	}

	cout << "test random number generator Park-Miller" << endl;
	cout << "1st run" << "\t " << "2nd run" << endl;

	for (unsigned long i = 0; i < results.size(); i++)
	{

		cout << results[i] << "\t " << results2[i];

		cout << "\n";
	}
	cout << "\n";

	cout << "test random number generator Mersenne-Twister" << endl;
	cout << "1st run" << "\t " << "2nd run" << endl;

	for (unsigned long i = 0; i < results1.size(); i++)
	{

		cout << results1[i] << "\t " << results3[i];

		cout << "\n";
	}
	cout << "\n";

	//----------------------------------------------------------------------------

	
	VariateArray[0] = 0.0;
	VariateArray1[0] = 0.0;

	AntiThetic _generator(generator);
	AntiThetic _generator1(generator1);

	cout << "\n";

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		_generator.GetGaussians(VariateArray);
		_generator1.GetGaussians(VariateArray1);
		results[i] = VariateArray[0];
		results1[i] = VariateArray1[0];

	}

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		_generator.GetGaussians(VariateArray);
		_generator1.GetGaussians(VariateArray1);
		results2[i] = VariateArray[0];
		results3[i] = VariateArray1[0];

	}

	cout << "test random number generator Park-Miller - antithetic" << endl;
	cout << "1st run" << "\t " << "2nd run" << endl;

	for (unsigned long i = 0; i < results.size(); i++)
	{

		cout << results[i] << "\t " << results2[i];

		cout << "\n";
	}
	cout << "\n";

	cout << "test random number generator Mersenne-Twister - antithetic" << endl;
	cout << "1st run" << "\t " << "2nd run" << endl;

	for (unsigned long i = 0; i < results1.size(); i++)
	{

		cout << results1[i] << "\t " << results3[i];

		cout << "\n";
	}
	cout << "\n";

	//----------------------------------------------------------------------------

	double tmp;
	cin >> tmp;

	return 0;

}