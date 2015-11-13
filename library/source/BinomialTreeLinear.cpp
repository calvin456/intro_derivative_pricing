/*
ex 8.2 Develop a binomial tree for which the memory requirements grow linearly with
the number of steps

General idea is not to store entire tree since memory requirements grow with order 2 O(n2)

Find alternative algo that grows with order 1 O(n)

Should result in speed boost
*/


#include <BinomialTreeLinear.h>
#include <Arrays.h>
#include <cmath>
#include <iostream>

using namespace std;

BinomialTree::BinomialTree(double Spot_,
							const Parameters& r_,
							const Parameters& d_,
							double Volatility_,
                            unsigned long Steps_,
                            double Time_)
	: Spot(Spot_), r(r_), d(d_), Volatility(Volatility_), Steps(Steps_), Time(Time_),Price(Steps+1)
{}

double BinomialTree::GetThePrice(TreeProduct& TheProduct)
{
	double InitialLogSpot = log(Spot);
	double movedLogSpot =  InitialLogSpot+ r.Integral(0.0, Time) - d.Integral(0.0, Time);
	movedLogSpot -= 0.5 * Volatility*Volatility*Time;
	double deltaT = (double)(Time/Steps);
	double sd = Volatility*sqrt(deltaT);

	//Initial value at time TheProduct
	for (long j=-static_cast<long>(Steps), i=0; j <= static_cast<long>(Steps); j=j+2,i++){
		double Spot_final = exp(movedLogSpot + sd*j);
		Price[i] = TheProduct.FinalPayOff(Spot_final);
	}

	double D = .5 * exp(-r.Integral(0.0, deltaT));
	MJArray tmp1;
	unsigned long k = Steps-1;
	double Spot_pre_final;

	//Move to earlier time
	while(k > 0 ){
		tmp1.resize(k+1);
		double thisTime = (k*Time)/(Steps);
		double movedLogSpot = InitialLogSpot + r.Integral(0.0, thisTime) - d.Integral(0.0, thisTime);
		movedLogSpot -= 0.5 * Volatility * Volatility * thisTime;

		for (unsigned long i=0; i <= k ; i++){
			unsigned long index = k-i;
			Spot_pre_final = exp(movedLogSpot + sd * (k - 2.0*i));
			tmp1[index] = D * (Price[index] +  Price[index+1]);
			tmp1[index] = TheProduct.PreFinalValue(Spot_pre_final,deltaT,tmp1[index]);
		}

		Price.resize(k+1);
		Price = tmp1;
		k--;
	}

	return D * (Price[0] +  Price[1]);
}
