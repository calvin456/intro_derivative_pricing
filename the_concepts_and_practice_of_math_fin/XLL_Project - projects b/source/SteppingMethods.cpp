/*
b3 project 1 :vanilla options in a bs world
*/


#include <SteppingMethods.h>
#include <Normals.h>
#include <cmath>
#include<Arrays.h>

#include<ParkMiller.h>
#include<AntiThetic.h>

#if !defined(_MSC_VER)
using namespace std;
#endif

double FinalPrice_EulerStepping( double Spot,
                         double Steps,
                         double r,
                         double d,
                         double Vol,
                         double Expiry)
{
    double deltaT = Expiry/Steps;
	
	double PriceT = Spot;
		
	 RandomParkMiller generator(Steps,123456);
  
    AntiThetic GenTwo(generator);
	//GenTwo.ResetDimensionality(1);

	MJArray VariateArray(Steps);

	GenTwo.GetGaussians(VariateArray);

	double theta1 = 1 + (r-d)*deltaT;
	double theta2 = Vol*std::sqrt(deltaT);

	for(unsigned long i=0;i <Steps;++i){
		
		PriceT *= (theta1 + theta2* VariateArray[i]);
	}
	
    return PriceT; 
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
