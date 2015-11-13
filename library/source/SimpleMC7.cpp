//
//
//
//                      SimpleMC7.cpp
//                         
//

#include <SimpleMC7.h>
#include <Random1.h>
#include <cmath>
#include<iostream>

#include <time.h>
#include<Terminator.h>
#include<Timer.h>

// the basic math functions should be in namespace std but aren't in VCPP6
//#if !defined(_MSC_VER)
using namespace std;
//#endif

void SimpleMonteCarlo5(const VanillaOption& TheOption, 
						 double Spot, 
						 const Parameters& Vol, 
						 const Parameters& r, 
                         unsigned long NumberOfPaths,
						 StatisticsMC& gatherer)
{
    double Expiry = TheOption.GetExpiry();
	double variance = Vol.IntegralSquare(0,Expiry);
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double movedSpot = Spot*exp(r.Integral(0,Expiry) +itoCorrection);
	double thisSpot;
    double discounting = exp(-r.Integral(0,Expiry));

	for (unsigned long i=0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp( rootVariance*thisGaussian);
		double thisPayOff = TheOption.OptionPayOff(thisSpot);
        gatherer.DumpOneResult(thisPayOff*discounting);
	}

    return;
};

void SimpleMonteCarlo51(const VanillaOption& TheOption, 
						 double Spot,
						 const Parameters& Vol, 
						 const Parameters& r,
                         unsigned long NumberOfPaths,
						 StatisticsMC& gatherer,
						 Terminator& Terminator_)
{
    double Expiry = TheOption.GetExpiry();
	double variance = Vol.IntegralSquare(0,Expiry);
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double movedSpot = Spot*exp(r.Integral(0,Expiry) +itoCorrection);
	double thisSpot;
    double discounting = exp(-r.Integral(0,Expiry));
	
	
	double maxIterration;
	if (NumberOfPaths < Terminator_.getPathsDone())
		maxIterration = NumberOfPaths;
	else
		maxIterration = Terminator_.getPathsDone();
    
	unsigned long seconds = Terminator_.getTimeSpent();
	timer t;
	t.start();
	cout << "timer started . . ." << endl;
	
	unsigned long i(0);

	while (i < maxIterration){
		if(t.elapsedTime() >= seconds) {
			
			break;
		}
		else {
			double thisGaussian = GetOneGaussianByBoxMuller();
			thisSpot = movedSpot*exp( rootVariance*thisGaussian);
			double thisPayOff = TheOption.OptionPayOff(thisSpot);
			gatherer.DumpOneResult(thisPayOff*discounting);
		}
		i++;
	}
	
	if (i == Terminator_.getPathsDone())
		cout << "Max iteration reached - " << Terminator_.getPathsDone() << endl;


	cout << t.elapsedTime() <<  " seconds elapsed" << endl;
	
};

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


