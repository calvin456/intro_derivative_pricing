/*
ex. 8.5 Martingale tree should converge to bs price
*/


#include <BinomialTree.h>
#include <BinomialTreeMartingale.h>
#include <TreeEuropean.h>
#include <BlackScholesFormulas.h>
#include <PayOff3.h>

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{

	double Expiry(.25);
	double Strike(100.0);

	double Spot(100.0);
	double Vol(.2);
	double r(.01);
	double d(0.0);
	unsigned long Steps(2);

	double BSPrice = BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);
	cout << "BS formula euro price " << BSPrice << "\n";
	cout << endl;

	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	PayOffCall thePayOff(Strike);

	TreeEuropean europeanOption(Expiry, thePayOff);

	BinomialTreeMartingale theTree1(Spot, Strike, rParam, dParam, Vol, Steps, Expiry);

	ofstream myfile;
	myfile.open("price.txt");

	cout << "computation starts" << endl;

	for (unsigned long i = Steps; i < 1e+9; i *= 2){

		double euroPrice1 = theTree1.GetThePrice(europeanOption, i);

		cout << "euro price (Martingale) : " << i << "," << euroPrice1 << endl;

		myfile << i << "," << euroPrice1 << ";\n";
	}

	cout << "computation ended" << endl;



	myfile.close();

	double tmp;
	cin >> tmp;

	return 0;
}


