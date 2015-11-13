/*
ex 8.3 write a trinomail tree class

S(i,j) = S0 * u^nu * d^nd

n = nu + nm + nd

*/

#include <TrinomialTree.h>
#include <Arrays.h>
#include <cmath>


using namespace MyTrinomialTree;
using namespace std;


TrinomialTree::TrinomialTree(double Spot_,
						     const Parameters& r_,
							 const Parameters& d_,
							 double Volatility_,
                             unsigned long Steps_,
                             double Time_)								   
	: Spot(Spot_), r(r_), d(d_), Volatility(Volatility_), Steps(Steps_), Time(Time_)
{
	TreeBuilt=false;
	
	double deltaT = (double)(Time/Steps);
	up = exp(Volatility * sqrt(2.0*deltaT));
	down = 1/up;
	double a = exp(Volatility * sqrt(deltaT/2.0));
	
	prob_up = pow((exp(r.Integral(0.0, deltaT/2.0) - d.Integral(0.0, deltaT/2.0))-1/a)/(a - 1/a),2) * 
					exp(-1.0*r.Integral(0.0, deltaT ));
		
	prob_down = pow((a - exp(r.Integral(0.0, deltaT/2.0) - d.Integral(0.0, deltaT/2.0)))/(a - 1/a),2) * 
					exp(-1.0*r.Integral(0.0, deltaT ));
	
	prob_no_move = exp(-1.0*r.Integral(0.0, deltaT ))  - prob_up - prob_down;	
}

void TrinomialTree::BuildTree()
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

double TrinomialTree::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();
	
    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in trinomial tree");

	double deltaT = (double)(Time/Steps);
	
    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>( Steps); j=j+1,k++)
        TheTree[Steps][k].second = TheProduct.FinalPayOff(TheTree[Steps][k].first);

    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;  
        double ThisTime = index*Time/Steps;
   
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+1,k++)
        {
            double Spot = TheTree[index][k].first;
            double futureDiscountedValue = prob_down*TheTree[index+1][k].second+
				prob_no_move*TheTree[index+1][k+1].second +prob_up*TheTree[index+1][k+2].second;
										
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue);
        }
        
    }
    return TheTree[0][0].second;
}

