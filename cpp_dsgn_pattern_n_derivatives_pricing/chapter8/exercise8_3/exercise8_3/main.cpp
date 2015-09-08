//main.cpp

/*Test trinomial tree class with European and American option

Trinomial tree result in accuracy improvement compared to binomial tree for same number of steps
using black-sholes model as benchmark.

*/

#include <TrinomialTree.h>
#include <BinomialTreeLinear.h>
#include <TreeAmerican.h>
#include <TreeEuropean.h>
#include <BlackScholesFormulas.h>
#include <PayOffForward.h>

#include <iostream>
using namespace std;
#include <cmath>
int main()
{

	double Expiry;
	double Strike;

	double Spot;
	double Vol;
	double r;
	double d;
	unsigned long Steps;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nStrike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nd\n";
	cin >> d;

	cout << "\nNumber of steps\n";
	cin >> Steps;

	PayOffCall thePayOff(Strike);

	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	TreeEuropean europeanOption(Expiry, thePayOff);
	TreeAmerican americanOption(Expiry, thePayOff);

	double BSPrice = BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);
	cout << endl << "BS formula euro price " << BSPrice << "\n";

	BinomialTree theTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	double euroPrice = theTree.GetThePrice(europeanOption);
	double americanPrice = theTree.GetThePrice(americanOption);
	cout << endl << "binomial tree pricing:" << endl;
	cout << "euro price " << euroPrice << " amer price " << americanPrice << "\n";

	TrinomialTree theTree1(Spot, rParam, dParam, Vol, Steps, Expiry);

	double euroPrice1 = theTree1.GetThePrice(europeanOption);
	double americanPrice1 = theTree1.GetThePrice(americanOption);
	cout << endl << "trinomial tree pricing" << endl;
	cout << "euro price " << euroPrice1 << " amer price " << americanPrice1 << "\n";


	double tmp;
	cin >> tmp;

	return 0;
}
