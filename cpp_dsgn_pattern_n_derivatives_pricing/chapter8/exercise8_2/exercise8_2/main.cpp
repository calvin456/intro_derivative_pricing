/*
Ex 8.2 Develop a binomial tree for which the memory requirements
grow linearly with the number of steps
*/

#include <BinomialTreeLinear.h>
#include <BinomialTree.h>
#include <TreeAmerican.h>
#include <TreeEuropean.h>
#include <BlackScholesFormulas.h>

#include <iostream>
#include <ctime>
using namespace std;

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

	std::clock_t start;
	double duration;

	start = std::clock();

	BinomialTree theTree(Spot, rParam, dParam, Vol, Steps, Expiry);
	double euroPrice = theTree.GetThePrice(europeanOption);
	double americanPrice = theTree.GetThePrice(americanOption);
	cout << endl << "linear tree : ";
	cout << "euro price " << euroPrice << " amer price " << americanPrice << "\n";

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "duration: " << duration << '\n';

	start = std::clock();

	SimpleBinomialTree  theTree1(Spot, rParam, dParam, Vol, Steps, Expiry);
	double euroPrice1 = theTree1.GetThePrice(europeanOption);
	double americanPrice1 = theTree1.GetThePrice(americanOption);
	cout << endl << "original tree : ";
	cout << "euro price " << euroPrice1 << " amer price " << americanPrice1 << "\n";

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "duration: " << duration << '\n';

	cout << endl;

	double tmp;
	cin >> tmp;

	return 0;
}