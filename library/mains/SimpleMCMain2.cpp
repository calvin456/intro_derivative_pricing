//
//
//	                	SimpleMCMain2.cpp
//
//     
// 

/*
requires 
         PayOff1.cpp
         Random1.cpp, 
         SimpleMC.cpp, 
*/

#include<SimpleMC.h>
#include<iostream>
using namespace std;

int main()
{

	double Expiry;
	double Strike;
	double Strike1;
	double Spot; 
	double Vol; 
	double r; 
	unsigned long NumberOfPaths;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nEnter strike\n";
	cin >> Strike;

	cout << "\nEnter strike1\n";
	cin >> Strike1;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

    PayOff callPayOff(Strike, PayOff::call);
    PayOff putPayOff(Strike, PayOff::put);
	PayOff digitalPayOff(Strike, PayOff::digitalCall);
	PayOff doubleDigitalPayOff(Strike, Strike1, PayOff::doubleDigital);

	double resultCall = SimpleMonteCarlo2(callPayOff,
                                          Expiry,                                           
							              Spot, 
							              Vol, 
							              r, 
						                  NumberOfPaths);
	
    double resultPut = SimpleMonteCarlo2(putPayOff,
                                         Expiry,                                           
							             Spot, 
							             Vol, 
							             r, 
						                 NumberOfPaths);

	double resultDigitalCall = SimpleMonteCarlo2(digitalPayOff,
                                         Expiry,                                           
							             Spot, 
							             Vol, 
							             r, 
						                 NumberOfPaths);

	double resultDoubleDigital = SimpleMonteCarlo2(doubleDigitalPayOff,
                                         Expiry,                                           
							             Spot, 
							             Vol, 
							             r, 
						                 NumberOfPaths);

	cout <<"the prices are " << resultCall << " for the call, \n" 
                                    << resultPut << " for the put, \n"
									<< resultDigitalCall << " for the digital call, \n"
									<< resultDoubleDigital << " and for the double digital \n";

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

