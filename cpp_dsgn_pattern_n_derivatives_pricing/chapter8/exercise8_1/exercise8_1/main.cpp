//main.cpp

/*
Exercise 8.1

price is not stable using binomial model (Jarrow)
control variable, smoothing, Richardson extrapolation

try Richardson extrapolation and control variate method
ref. Joshi, M (2007) The convergence of binomial trees for pricing the American put,
Available at SSRN #1030143

Richardson method - Makes oscillation worse

Control variate method - gain very limited
*/


#include <BinomialTree.h>
#include <TreeAmerican.h>
#include <TreeEuropean.h>

#include <TreeBarrier.h>

#include <BlackScholesFormulas.h>
#include <PayOffForward.h>

#include <barrierOption.h>

#include <iostream>
#include <vector>

#include <fstream>

using namespace std;
#include <cmath>
int main()
{

	double Expiry(.25);
	double Strike(100);

	//double Barrier;

	double Spot(100);
	double Vol(.2);
	double r(.01);
	double d(.03);
	unsigned long Steps(500);


	PayOffKOCall thePayOff1(115, 100);
	PayOffKICall thePayOff2(115, 100);
	PayOffKOPut thePayOff3(85, 100);
	PayOffKIPut thePayOff4(85, 100);

	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	TreeBarrier koCall(Expiry, thePayOff1);
	TreeBarrier kiCall(Expiry, thePayOff2);
	TreeBarrier koPut(Expiry, thePayOff3);
	TreeBarrier kiPut(Expiry, thePayOff4);

	//---------------------------------------------------------------------

	SimpleBinomialTree theTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	cout << "Test barrier parity : " << endl;
	cout << "Call : " << endl;
	cout << "KI + KO = BS : ";

	cout << theTree.GetThePrice(kiCall) + theTree.GetThePrice(koCall) << endl;

	cout << "BS formula euro price : " << BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) << endl;

	cout << "Put : " << endl;
	cout << "KI + KO = BS : ";

	cout << theTree.GetThePrice(kiPut) + theTree.GetThePrice(koPut) << endl;

	cout << "BS formula euro price : " << BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) << endl;

	cout << endl;

	//-----------------------------------------------------------------------

	vector<double> prices_koCall;
	vector<double> prices_kiCall;
	vector<double> prices_koPut;
	vector<double> prices_kiPut;

	prices_koCall.resize(Steps + 1);
	prices_kiCall.resize(Steps + 1);
	prices_koPut.resize(Steps + 1);
	prices_kiPut.resize(Steps + 1);



	ofstream myfile;
	myfile.open("price.txt");

	cout << "computation starts" << endl;

	for (unsigned long i = 0; i <= Steps; ++i){

		SimpleBinomialTree theTree(Spot, rParam, dParam, Vol, i, Expiry);

		prices_koCall[i] = theTree.GetThePrice(koCall);
		prices_kiCall[i] = theTree.GetThePrice(kiCall);
		prices_koPut[i] = theTree.GetThePrice(koPut);
		prices_kiPut[i] = theTree.GetThePrice(kiPut);

	}

	//Richardson extrapolation

	vector<double> richardson_koCall;
	vector<double> richardson_kiCall;
	vector<double> richardson_koPut;
	vector<double> richardson_kiPut;

	richardson_koCall.resize(Steps + 1);
	richardson_kiCall.resize(Steps + 1);
	richardson_koPut.resize(Steps + 1);
	richardson_kiPut.resize(Steps + 1);

	double bn(1.0 / (1.0 - Steps / (2.0*Steps + 1)));

	double an(1.0 - bn);

	for (unsigned long i = 0, j = 1; j <= Steps; ++i, j = 2 * i + 1){

		richardson_koCall[i] = bn*prices_koCall[j] + an*prices_koCall[i];
		richardson_kiCall[i] = bn*prices_kiCall[j] + an*prices_kiCall[i];
		richardson_koPut[i] = bn*prices_koPut[j] + an*prices_koPut[i];
		richardson_kiPut[i] = bn*prices_kiPut[j] + an*prices_kiPut[i];

	}

	//control variate
	//Use European options as a control variable

	vector<double> price_Call;
	vector<double> price_Put;

	price_Call.resize(Steps + 1);
	price_Put.resize(Steps + 1);

	double bsCall = BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);

	double bsPut = BlackScholesPut(Spot, Strike, r, d, Vol, Expiry);

	PayOffCall thePayOff5(Strike);
	PayOffPut thePayOff6(Strike);

	TreeEuropean Call(Expiry, thePayOff5);
	TreeEuropean Put(Expiry, thePayOff6);

	for (unsigned long i = 0; i <= Steps; ++i){

		SimpleBinomialTree theTree(Spot, rParam, dParam, Vol, i, Expiry);

		price_Call[i] = theTree.GetThePrice(Call);
		price_Put[i] = theTree.GetThePrice(Put);

	}

	vector<double> cv_koCall;
	vector<double> cv_kiCall;
	vector<double> cv_koPut;
	vector<double> cv_kiPut;

	cv_koCall.resize(Steps + 1);
	cv_kiCall.resize(Steps + 1);
	cv_koPut.resize(Steps + 1);
	cv_kiPut.resize(Steps + 1);

	for (unsigned long i = 0; i <= Steps; ++i){

		cv_koCall[i] = prices_koCall[i] + bsCall - price_Call[i];
		cv_kiCall[i] = prices_kiCall[i] + bsCall - price_Call[i];
		cv_koPut[i] = prices_koPut[i] + bsPut - price_Put[i];
		cv_kiPut[i] = prices_kiPut[i] + bsPut - price_Put[i];

	}


	//------------------------------------------------------------------------------

	myfile << "i" << ";" << "prices_koCall" << ";" << "prices_kiCall" << ";" << "prices_koPut" << ";" << "prices_kiPut" << ";" <<
		"richardson_koCall" << ";" << "richardson_kiCall" << ";" << "richardson_koPut" << ";" << "richardson_kiPut" << ";" <<
		"cv_koCall" << ";" << "cv_kiCall" << ";" << "cv_koPut" << ";" << "cv_kiPut" << ";\n";


	for (unsigned long i = 0; i < Steps; ++i){

		myfile << i << ";" << prices_koCall[i] << ";" << prices_kiCall[i] << ";" << prices_koPut[i] << ";" << prices_kiPut[i] << ";" <<
			richardson_koCall[i] << ";" << richardson_kiCall[i] << ";" << richardson_koPut[i] << ";" << richardson_kiPut[i] << ";" <<
			cv_koCall[i] << ";" << cv_kiCall[i] << ";" << cv_koPut[i] << ";" << cv_kiPut[i] << ";\n";

	}

	cout << "computation ended" << endl;

	myfile.close();

	double tmp;
	cin >> tmp;

	return 0;
}
