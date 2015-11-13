//
//
//              SolveMain2.cpp
//
//
/*
Needs
    BlackScholesFormulas.cpp
    BSCallTwo.cpp
    Normals.cpp
*/

//Add ex 9.1

#include <NewtonRaphson.h>
#include <cmath>
#include <iostream>
#include <BSCallTwo.h>
#include <BlackScholesFormulas.h>

#include<Terminator.h>

using namespace std;

int main()
{
  	double Expiry;
	double Strike; 
	double Spot; 
	double r;
    double d;
    double Price;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nStrike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter price\n";
	cin >> Price;

	cout << "\nr\n";
	cin >> r;

    cout << "\nd\n";
    cin >> d;
   
    double start;

    cout << "\nstart guess\n";
    cin >> start;

    double tolerance;

    cout << "\nTolerance\n";
    cin >> tolerance;

    BSCallTwo theCall(r,d,Expiry,Spot,Strike);

    double vol=NewtonRaphson<BSCallTwo, &BSCallTwo::Price, &BSCallTwo::Vega>(Price,
                                                                           start,
                                                                           tolerance,
                                                                           theCall);

    double PriceTwo = BlackScholesCall(Spot,Strike,r,d,vol,Expiry);
	cout << "No terminator class : " << endl;
    cout << "\n vol " << vol << " \nprice two:" << PriceTwo << "\n";

	//ex. 9.1
	//Modify the Newton-Raphson routine so it does not endlessly loop if a root is not found
	Terminator terminator(1,2); //1 sec, 2 max iter
	
	double vol1=NewtonRaphson1<BSCallTwo, &BSCallTwo::Price, &BSCallTwo::Vega>(Price,
																			start,
																			tolerance,
																			theCall,
																			terminator);

    double PriceTwo1 = BlackScholesCall(Spot,Strike,r,d,vol1,Expiry);
	cout << "Terminator class added : " << endl;
    cout << "\n vol " << vol1 << " \nprice two:" << PriceTwo1 << "\n";
	
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

