/*
Exercise 8.5

Postby pzling » Wed Mar 07, 2012 6:15 am
Hi

How should the expected value of the Spot prices be taken as a martingale?

I'm using the same risk neutral probabilities as for the payoffs and the Spots are converging to another value other than that used to build the final time layer.
eg. If I use a Spot of 100 to build the final time layer, and then take the expected present values of the Spots all the way back to time 0, I get an initial Spot of say, 71 (which is not equal to 100).

This also results in the American options having the same price as the European options.

Many thanks

pzling	
     
    Posts: 41
    Joined: Sat Jan 14, 2012 8:52 pm

Top
Re: Exercise 8.5

Postby mj » Wed Mar 07, 2012 9:46 am
in this book, i've taken p=0.5 for simplicity and done the Jarrow Rudd tree. However, normally people take

p = (e^{r\delta t) - d)/(u-d)

to ensure E(S_t+\delta t) = e^{r \delta t} S_t

you'll find that the value is close to 0.5 but NOT exactly equal to it.

See More mathematical finance for extensive discussion.

mj	
    Site Admin
     
    Posts: 1348
    Joined: Fri Jul 27, 2007 7:21 am

Top
Re: Exercise 8.5

Postby pzling » Wed Mar 07, 2012 10:58 am
I see thanks. Will definitely order that in once I've gone through this one.

In the meantime, I forgot to mention I did this on the trinomial tree (and used the standard risk neutral probabilities ... looks like [(exp(A)-exp(B))/(exp(C)-exp(B)]^2).

So at the risk of turning this into a math question now, do the trinomial risk neutral probabilities simulate geometric brownian motion like the binomial probabilites do? Or were they derived specifically for a trinomial model?

pzling	
     
    Posts: 41
    Joined: Sat Jan 14, 2012 8:52 pm

Top
Re: Exercise 8.5

Postby pzling » Wed Mar 07, 2012 1:16 pm
Actually, sorry, I just noticed my implemented probabilities are off, which would probably explain why it wasn't converging to the right value
*/

/*
ex. 8.5 

Modify the three so the implied stock price process makes the discounted price a martingale. 

Compare convergence for calls, puts and forwards. Should converge to bs result. i.e. the exact solution

dSt/St = mu * dt + sigma * dWt

Martingale : St * exp( -r * t) = St/Bt

prob_up = (exp(r *dt)- down)/(up -down) 

Tree needs to converge to bs result as n-> infinity

Using call-put parity if call converges to analytical formulas put and forward shall too.

original bs no dvd paying stock
*/



#pragma warning( disable : 4786 )


#include <TreeProducts.h>
#include <vector>
#include <Parameters.h>
#include <Arrays.h>

struct MyStructure{
	double stock_price;
	double prob; //probability under martingale
	double payoff;
	
};

class BinomialTreeMartingale
{

public:
	BinomialTreeMartingale(double Spot_,
						double Strike_,
                       const Parameters& r_,
                       const Parameters& d_, 
                       double Volatility_,
                       unsigned long Steps,
                       double Time);
                  
	
	double GetThePrice(const TreeProduct& TheProduct,unsigned long Steps);
	
private:
  
    double Spot;
	double Strike;
    Parameters r;
	Parameters d;
    double Volatility;
    unsigned long Steps;
    double Time;
    
};












