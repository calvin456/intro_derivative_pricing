/*
ex 9.3 Write a routine to price a vanilla option by Monte-Carlo or trees where the pay-off is passed in 
as a template param express via a function object

*/

#include <TrinomialTreeTemplate.h>
#include <Arrays.h>
#include <cmath>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

template< class T>
TrinomialTreeTemplateEuropean<T>::TrinomialTreeTemplateEuropean(double Spot_,
																								const Parameters& r_,
																								const Parameters& d_, 
																								double Volatility_,
																								unsigned long Steps_,
																								double Time_,
																								T& ThePayOff_): Spot(Spot_), 
																								r(r_),
																								d(d_), 
																								Volatility(Volatility_),
																								Steps(Steps_),
																								Time(Time_),
																								ThePayOff(ThePayOff_)
{
    TreeBuilt=false;
	
	double deltaT = (double)(Time/Steps);
	
    up = std::exp(Volatility * std::sqrt(2.0*deltaT));
	
	down = 1/up;
	
	double a = std::exp(Volatility * std::sqrt(deltaT/2.0));
	
	prob_up = std::pow((std::exp(r.Integral(0.0, deltaT/2.0) - d.Integral(0.0, deltaT/2.0))-1/a)/(a - 1/a),2) * 
		std::exp(-1.0*r.Integral(0.0, deltaT ));
		
	prob_down = std::pow((a - std::exp(r.Integral(0.0, deltaT/2.0) - d.Integral(0.0, deltaT/2.0)))/(a - 1/a),2) * 
		std::exp(-1.0*r.Integral(0.0, deltaT ));
	
	prob_no_move = std::exp(-1.0*r.Integral(0.0, deltaT ))  - prob_up - prob_down;
	
}

template< class T>
void TrinomialTreeTemplateEuropean<T>::BuildTree()
{    
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
	

    for (unsigned long i=0; i <=Steps; i++)
    {

        TheTree[i].resize(1+i*2);

        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j=j+1,k++)
              TheTree[i][k].first = Spot*std::pow(up,j);
    }
   
 
}

template< class T>
double TrinomialTreeTemplateEuropean<T>::GetThePrice()
{
    if (!TreeBuilt)
        BuildTree();
	
	double deltaT = (double)(Time/Steps);
	
    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>( Steps); j=j+1,k++)
        TheTree[Steps][k].second = ThePayOff(TheTree[Steps][k].first);

    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;  
   
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+1,k++)
        {
            double Spot = TheTree[index][k].first;
										
            TheTree[index][k].second = prob_down*TheTree[index+1][k].second+
				prob_no_move*TheTree[index+1][k+1].second +prob_up*TheTree[index+1][k+2].second;
			
        }
        
    }
    return TheTree[0][0].second;
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