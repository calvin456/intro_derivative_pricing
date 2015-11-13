/*
ex 8.4 Modify the code so that it will work under variable volatile

The key is to ensure that the integral of the square of the vol across each time step is the same

This means that the time steps will be of unequal length


Ex 8.4

Postby rer » Fri May 18, 2012 2:37 pm
Hi Mark,

When you mention variable volatility in the binomial tree setting, do you have in mind volatility varying with time, or volatility varying with the Stock price, or both?

Thanks,

Ross

rer	
     
    Posts: 7
    Joined: Thu Apr 26, 2012 11:27 am

Top
Re: Ex 8.4

Postby mj » Wed May 23, 2012 12:56 am
i meant time

dSt/St = mu*dt + sigma(t)*dWt

log S(tn+1) - log S(tn) = (mu - .5*sigma(n)^2) * deltaT + Z(n+1), Z(n+1) ~ N(0,sigma(n)^2*deltaT)

1. Choose # steps N, lifetime of option T

2. Calculate each up move using up = exp(sigma(n)*sqrt(T/N))  -> S(t) = S(t-1)*up (approx)

3. Calculate date using exp(sigma(n)*T/N) = exp(sigma(n) * sqrt(deltaT))

4. Build binomial tree

5. Calculate risk-neutral prob : prob_up = (exp( mu * deltaT) - 1/u)/(u - +/u)

*/


#pragma warning( disable : 4786 )


#include <TreeProducts.h>
#include <vector>
#include <Parameters.h>
#include <Arrays.h>


struct VolatilityTermStructure{ //volatility term structure depicting sigma dependent of time
	
	double time;
	double value;
	
};

struct PathSructure{
	
	double up;
	double deltaT;
	double prob_up;
	
};

class BinomialTreeTermStructure
{

public:
	BinomialTreeTermStructure(double Spot,
                       const Parameters& r,
                       const Parameters& d, 
                       std::vector<VolatilityTermStructure> Volatility,
                       unsigned long Steps,
                       double Time);
                  

	double GetThePrice(const TreeProduct& TheProduct);

protected:
    void BuildTree(); 

private:
  
    double Spot;
    Parameters r;
	Parameters d;
    std::vector<VolatilityTermStructure> Volatility;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;
	
	std::vector<PathSructure> ThePath;

    std::vector<std::vector<std::pair<double, double> > > TheTree;
	MJArray Discounts;
   
};




