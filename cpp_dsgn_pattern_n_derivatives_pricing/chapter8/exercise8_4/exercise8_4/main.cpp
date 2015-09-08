/*
test learn tree
atm options
*/



#include <BinomialTreeTermStructure.h>
#include <TreeAmerican.h>
#include <TreeEuropean.h>

#include <vector>
#include <iostream>
using namespace std;
#include <cmath>
int main()
{

	double Expiry(.25); //3-month 
	double Strike(100.0);

	double Spot(100.0);

	double r(.01);
	double d(.03);
	unsigned long Steps(10);

	//initiate volatility term structure
	//http://www.cboe.com/data/volatilityindexes/volatilityindexes.aspx spx 
	//4 Feb 2015


	std::vector<VolatilityTermStructure> Vol;

	Vol.resize(Steps);

	Vol[0].time = .0833; //1-mth
	Vol[0].value = .1690;

	Vol[1].time = .1666;//2-mth
	Vol[1].value = .1848;

	Vol[2].time = .2499; //3-mth
	Vol[2].value = .1914;

	Vol[3].time = .3332; //4-mth
	Vol[3].value = .2006;

	Vol[4].time = .4165; //5-mth
	Vol[4].value = .2018;

	Vol[5].time = .4998; //6-mth
	Vol[5].value = .2078;

	Vol[6].time = .5831; //7-mth
	Vol[6].value = .2144;

	Vol[7].time = .6664; //8-mth
	Vol[7].value = .21;

	Vol[8].time = .7497; //9-mth
	Vol[8].value = .2176;

	Vol[9].time = .833; //10-mth
	Vol[9].value = .2273;

	PayOffCall thePayOff(Strike);

	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	TreeEuropean europeanOption(Expiry, thePayOff);
	TreeAmerican americanOption(Expiry, thePayOff);


	BinomialTreeTermStructure theTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	double euroPrice = theTree.GetThePrice(europeanOption);
	double americanPrice = theTree.GetThePrice(americanOption);
	cout << endl << "binomial tree pricing - variable vol: " << endl;
	cout << "euro price " << euroPrice << " amer price " << americanPrice << "\n";



	double tmp;
	cin >> tmp;

	return 0;
}



