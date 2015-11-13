

#include <BinomialTreeTermStructure.h>
#include <Arrays.h>
#include <cmath>

using namespace std;

BinomialTreeTermStructure::BinomialTreeTermStructure(double Spot_,
									   const Parameters& r_,
									   const Parameters& d_,
									   vector<VolatilityTermStructure> Volatility_,
                                       unsigned long Steps_,
                                       double Time_)
	: Spot(Spot_), r(r_),d(d_), Volatility(Volatility_), 
		Steps(Steps_),Time(Time_),Discounts(Steps)
{
    TreeBuilt=false;
	double deltaT = (double)(Time/Steps);
	ThePath.resize(Steps);
	
	for(unsigned long i =0;i < Steps;++i){		
		ThePath[i].up = exp(Volatility[i].value * sqrt(deltaT));
		ThePath[i].deltaT = log(ThePath[i].up)/Volatility[i].value * log(ThePath[i].up) / Volatility[i].value;
		ThePath[i].prob_up = (exp(r.Integral(0.0, ThePath[i].deltaT) 
								- d.Integral(0.0, ThePath[i].deltaT)) - 1/ThePath[i].up) / (ThePath[i].up - 1/ThePath[i].up);
	}
	
}

void BinomialTreeTermStructure::BuildTree()
{    
    TreeBuilt = true;
    TheTree.resize(Steps);
	
	TheTree[0].resize(1);
	TheTree[0][0].first = Spot;
	
    for (unsigned long i=1; i < Steps; i++){
        TheTree[i].resize(1+i);

		for(unsigned long l=0,k=0;l <i,k<i+1;++l,++k){			
			double tmp= ((l <k) ? -1.0 : 1.0);
			TheTree[i][k].first = Spot * pow(ThePath[l].up,tmp);				
		}							 		  
    }
	
	for (unsigned long l=0; l <Steps; l++)
        Discounts[l] = exp(- r.Integral(0,ThePath[l].deltaT));
}

double BinomialTreeTermStructure::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)	BuildTree();

    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in BinomialTreeTermStructure");

    for (long j = -static_cast<long>(Steps-1), k=0; j <=static_cast<long>( Steps-1); j=j+2,k++)
        TheTree[Steps-1][k].second = TheProduct.FinalPayOff(TheTree[Steps-1][k].first);

    for (unsigned long i=1; i <= Steps-1; i++)
    {
        unsigned long index = Steps - 1 - i;  
        double ThisTime = ThePath[index].deltaT;
   
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+2,k++){
            double Spot = TheTree[index][k].first;
            double futureDiscountedValue = Discounts[index] * (ThePath[index].prob_up*TheTree[index+1][k].second +
											(1 - ThePath[index].prob_up)*TheTree[index+1][k+1].second);
          
			TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue);
        }
        
    }

    return TheTree[0][0].second;
}

