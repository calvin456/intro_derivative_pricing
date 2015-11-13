/*
ex 8.2 Develop a binomial tree for which the memory requirements grow linearly with
the number of steps

*/


#pragma warning( disable : 4786 )


#include <TreeProducts.h>
#include <vector>
#include <Parameters.h>
#include <Arrays.h>


class BinomialTree
{

public:
	BinomialTree(double Spot_,
               const Parameters& r_,
               const Parameters& d_,
               double Volatility_,
               unsigned long Steps,
               double Time);

	double GetThePrice(TreeProduct& TheProduct);

private:
    double Spot;
    Parameters r;
	Parameters d;
    double Volatility;
    unsigned long Steps;
    double Time;
	MJArray Price;
};
