//	SimpleMCMain5_2.cpp

//Exercises 3.1 and 3.2

#include<SimpleMC2.h>
#include<DoubleDigital.h>
#include"Power.h"
#include<iostream>
#include<sstream>
using namespace std;

int main()
{

	double Expiry;
	double Strike,Order; 
	double Lower,Upper;
	double Spot; 
	double Vol; 
	double r; 
	unsigned long NumberOfPaths;
	unsigned long optionType;

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

	cout << "\nEnter 0 for call, 1 for put, 2 for double digital, 3 for power call, and 4 for power put\n";
	cin >> optionType;

	double result = 0.0;

	PayOff* thePayOffPtr;

	switch(optionType){

		case 0:

			cout << "\nEnter strike\n";
			cin >> Strike;

			thePayOffPtr = new PayOffCall(Strike);

			result = SimpleMonteCarlo2(* thePayOffPtr,
                                      Expiry,
                                      Spot, 
                                      Vol,
                                      r,
                                      NumberOfPaths);
			
			break;
	
		case 1:

			cout << "\nEnter strike\n";
			cin >> Strike;

			thePayOffPtr = new PayOffPut(Strike);

			result = SimpleMonteCarlo2(* thePayOffPtr,
                                      Expiry,
                                      Spot, 
                                      Vol,
                                      r,
                                      NumberOfPaths);
			
			break;
		case 2:

			cout << "\nEnter lower barrier\n";
			cin >> Lower;

			cout << "\nEnter upper barrier\n";
			cin >> Upper;

			thePayOffPtr = new PayOffDoubleDigital(Lower, Upper);

			result = SimpleMonteCarlo2(* thePayOffPtr,
                                      Expiry,
                                      Spot, 
                                      Vol,
                                      r,
                                      NumberOfPaths);
			
			break;
		case 3:

			cout << "\nEnter strike\n";
			cin >> Strike;

			cout << "\nEnter power order\n";
			cin >> Order;

			thePayOffPtr = new PayOffPowerCall(Strike, Order);

			result = SimpleMonteCarlo2(* thePayOffPtr,
                                      Expiry,
                                      Spot, 
                                      Vol,
                                      r,
                                      NumberOfPaths);
		
			break;

		case 4:

			cout << "\nEnter strike\n";
			cin >> Strike;

			cout << "\nEnter power order\n";
			cin >> Order;

			thePayOffPtr = new PayOffPowerPut(Strike, Order);

			result = SimpleMonteCarlo2(* thePayOffPtr,
                                      Expiry,
                                      Spot, 
                                      Vol,
                                      r,
                                      NumberOfPaths);
		
			break;


		default:
			cout << "option type is not any of (0) call, (1) put, (2) double digital, (3) power";

	}

	cout <<"\nthe price is " << result << "\n";
    double tmp;
    cin >> tmp;

	return 0;

}