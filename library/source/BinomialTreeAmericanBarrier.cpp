//--------------------------------------------------------------------------------
//do not use
//--------------------------------------------------------------------------------


/*
Trees ex. 8.6 Implement an American knock-in option pricer on a tree.

(Use an additional auxiliary variable to indicate whether or not the option has knocked-in, 
and compute that the value at each node in both cases.)

*/

#include <BinomialTreeAmericanBarrier.h>
#include <Arrays.h>
#include <cmath>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

BinomialTreeAmericanBarrier::BinomialTreeAmericanBarrier(double Spot_,
									   const Parameters& r_,
									   const Parameters& d_,
									   double Volatility_,
                                       unsigned long Steps_,
                                       double Time_)
									   : Spot(Spot_), 
                                         r(r_),
                                         d(d_), 
                                         Volatility(Volatility_),
                                         Steps(Steps_),
                                         Time(Time_),
                                         Discounts(Steps)
{
    TreeBuilt=false;
}

void BinomialTreeAmericanBarrier::BuildTree()
{    
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
    double InitialLogSpot = log(Spot);

    for (unsigned long i=0; i <=Steps; i++)
    {

        TheTree[i].resize(i+1);

        double thisTime = (i*Time)/Steps;

        double movedLogSpot = 
                            InitialLogSpot+ r.Integral(0.0, thisTime) 
                                          - d.Integral(0.0, thisTime);
    
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;

        double sd = Volatility*sqrt(Time/Steps);

        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j=j+2,k++)
              TheTree[i][k].stock_price = exp(movedLogSpot+ j*sd);
    }
   
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double BinomialTreeAmericanBarrier::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");
	
	double deltaT = (double)(Time/Steps);

    double up = std::exp(r.Integral(0.0, deltaT) - d.Integral(0.0, deltaT) + Volatility*std::sqrt(deltaT));
   
    double down = std::exp(r.Integral(0.0, deltaT) - d.Integral(0.0, deltaT) - Volatility*std::sqrt(deltaT));
   
    double prob_up = (std::exp(r.Integral(0.0, deltaT)) - down)/(up - down);
   
    double prob_down = 1 - prob_up;

    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>( Steps); j=j+2,k++){  
			TheTree[Steps][k].payoff  = TheProduct.FinalPayOff(TheTree[Steps][k].stock_price);
	}	
		
    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;  
        double ThisTime = index*Time/Steps;
   
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+2,k++)
        {
            double Spot = TheTree[index][k].stock_price;
            double futureDiscountedValue = 
                            Discounts[index]*
								(TheTree[index+1][k].payoff*prob_down+TheTree[index+1][k+1].payoff*prob_up);
            
			
			TheTree[index][k].payoff = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue);
        }
        
    }
    return TheTree[0][0].payoff;
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

