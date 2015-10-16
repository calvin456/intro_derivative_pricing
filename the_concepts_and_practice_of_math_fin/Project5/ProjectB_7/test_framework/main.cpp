//main.cpp

#include <iostream>

#include "asian_option.h"
#include <BlackScholesFormulas.h>

using namespace std;
using namespace BSFunction;


int main(){

	cout << "Forward : ";
	cout << Forward(100.0,103.0,0.05,0.03,1.0) << endl;

	double call = BlackScholesCall(100.0, 103.0, 0.05, 0.03, .1, 1.0);
	double put = BlackScholesPut(100.0, 103.0, 0.05, 0.03, .1, 1.0);

	cout << "BS call : ";
	cout << call << endl;

	cout << "BS put : ";
	cout << put << endl;

	cout << "put-call parity : ";
	cout << call - put << endl;

	call = asian_geo_call(100.0, 12, 103.0, .05, 0.03, .1, 1.0);
	put = asian_geo_put(100.0, 12, 103.0, .05, 0.03, .1, 1.0);

	cout << "Asian geo option call : " ;
	cout << call << endl;

	cout << "Asian geo option put : " ;
	cout << put << endl;

	double tmp;
	cin >> tmp;

	return 0;
}