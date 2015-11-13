/*
Trees ex. 8.6 Implement an American knock-in option pricer on a tree.

(Use an additional auxiliary variable to indicate whether or not the option has knocked-in, 
and compute that the value at each node in both cases.)


Ex 8.6

//--------------------------------------------------------------------------------
//do not use
//--------------------------------------------------------------------------------



Postby rer » Mon May 21, 2012 4:47 pm
Hi Mark,

I'm struggling to see how to calculate the price of an American knock in option on a tree.

The dynamic programming (martingale pricing) method on the normal tree iterates backwards in time, 
taking expectations of future payoff to calculate current price. 
The auxiliary variable that indicates whether knock-in has occurred surely needs to 'looks back' in time. 
Do we need to calculate the sum of the probabilities of each path that has knocked in and
 reached the up branch of the future payoff, 
 and also the sum of probabilities of each path that has knocked in and reached 
 the down branch of the future payoff to perform the calculation? Or is there an easier way? 
 Do you know any useful references that cover the necessary method?

Any help would be greatly appreciated! Thanks,

Ross

rer	
     
    Posts: 7
    Joined: Thu Apr 26, 2012 11:27 am

Top
Re: Ex 8.6

Postby mj » Wed May 23, 2012 12:56 am
There are 2 possibles value of the auxiliary variable
that indicates whether knock-in has occurred. We do not know which one is correct so we simply
compute the value at the node for each of them.



*/


#pragma warning( disable : 4786 )


#include <TreeProducts.h>
#include <vector>
#include <Parameters.h>
#include <Arrays.h>


struct PayOffStructure{
	
	double stock_price;
	double payoff;

};

class BinomialTreeAmericanBarrier
{

public:
	BinomialTreeAmericanBarrier(double Spot_,
                       const Parameters& r_,
                       const Parameters& d_, 
                       double Volatility_,
                       unsigned long Steps,
                       double Time);
                  

	double GetThePrice(const TreeProduct& TheProduct);

protected:

    void BuildTree(); 

private:
  
    double Spot;
    Parameters r;
	Parameters d;
    double Volatility;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;
	
    std::vector<std::vector<PayOffStructure > > TheTree;
    MJArray Discounts;
};


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

