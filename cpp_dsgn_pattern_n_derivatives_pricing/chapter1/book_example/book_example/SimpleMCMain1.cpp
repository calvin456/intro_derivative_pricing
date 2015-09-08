//
//
//	          	SimpleMCMain1.cpp
//
//     
//       requires Random1.cpp

//Edit file to include solutions to 1.1, 1.2, 1.3, 1.4 exercises.

#include "Random1.h"
#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

double SimpleMonteCarloCall(double Expiry, 
						 double Strike,
						 double Spot, 
						 double Vol, 
						 double r, 
						 unsigned long NumberOfPaths)
{

	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = Spot*exp(r*Expiry +itoCorrection);
	double thisSpot;
	double runningSum=0;

	for (unsigned long i=0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp( rootVariance*thisGaussian);
		
		// call
		double thisPayoff = thisSpot - Strike;
    	thisPayoff = thisPayoff >0 ? thisPayoff : 0;
		
		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
}

double SimpleMonteCarloPut(double Expiry, 
						 double Strike,
						 double Spot, 
						 double Vol, 
						 double r, 
						 unsigned long NumberOfPaths)
{

	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = Spot*exp(r*Expiry +itoCorrection);
	double thisSpot;
	double runningSum=0;

	for (unsigned long i=0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp( rootVariance*thisGaussian);
		
		// put
		double thisPayoff =  Strike - thisSpot;
    	thisPayoff = thisPayoff >0 ? thisPayoff : 0;

		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
}

double SimpleMonteCarloDoubleDigital(double Expiry, 
						 double Strike,
						 double Strike1,
						 double Spot, 
						 double Vol, 
						 double r, 
						 unsigned long NumberOfPaths)
{

	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = Spot*exp(r*Expiry +itoCorrection);
	double thisSpot;
	double runningSum=0;

	for (unsigned long i=0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp( rootVariance*thisGaussian);
		
		//double digital
		double thisPayoff=0;
    	
		if(thisSpot >= Strike && thisSpot <= Strike1)
		{
			thisPayoff = 1;
		}

		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
}



int main()
{

	double Expiry;
	double Strike; 
	double Strike1; 
	double Spot; 
	double Vol; 
	double r; 
	unsigned long NumberOfPaths;
	int OptionType;
	string st;

	cout << "\nOption type (1) call, (2) put, (3) double digital\n";
	cin >> st;
	stringstream(st) >> OptionType;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	

	double result=0.0;

	switch(OptionType){

		case 1:

			cout << "\nEnter strike\n";
			cin >> Strike;

			result = SimpleMonteCarloCall(Expiry,
												Strike,
												Spot, 
												Vol, 
												r, 
												NumberOfPaths);
			break;
		case 2:

			cout << "\nEnter strike\n";
			cin >> Strike;

			result = SimpleMonteCarloPut(Expiry,
												Strike,
												Spot, 
												Vol, 
												r, 
												NumberOfPaths);
			break;
		case 3:

			cout << "\nEnter strike\n";
			cin >> Strike;

			cout << "\nEnter strike1\n";
			cin >> Strike1;

			result = SimpleMonteCarloDoubleDigital(Expiry,
														Strike,
														Strike1,
														Spot, 
														Vol, 
														r, 
														NumberOfPaths);
			break;
		default:
			cout << "option type is not any of (1) call, (2) put, (3) double digital";

	}

	cout <<"the price is " << result << "\n";
	
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

