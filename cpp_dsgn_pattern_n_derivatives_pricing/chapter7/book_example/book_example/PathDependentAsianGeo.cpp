
//#include <math.h>
#include <cmath>
#include <PathDependentAsianGeo.h>

using namespace std;

PathDependentAsianGeo::PathDependentAsianGeo(const MJArray& LookAtTimes_,
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_)
                                       :
                                        PathDependent(LookAtTimes_),
                                        DeliveryTime(DeliveryTime_),
                                        ThePayOff(ThePayOff_),
                                        NumberOfTimes(LookAtTimes_.size())
{
}

unsigned long PathDependentAsianGeo::MaxNumberOfCashFlows() const
{
     return 1UL;
}

MJArray PathDependentAsianGeo::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long PathDependentAsianGeo::CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows) const
{
    double sum(0.0);

	//compute geometric average of spot prices
	//A(0,T) = exp(1/t * sum(ln(St)) ca. Wikipedia
	//use log instead of level. level result in overflow for large value # of dates

	for (unsigned long i =0; i < NumberOfTimes; i++)	sum+=log(SpotValues[i]);

	double mean = exp(sum / NumberOfTimes);

    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = ThePayOff(mean);

    return 1UL;
}

PathDependent* PathDependentAsianGeo::clone() const
{
    return new PathDependentAsianGeo(*this);
}


