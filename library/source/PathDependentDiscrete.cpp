

#include <cmath>
#include <PathDependentDiscrete.h>

PathDependentDiscrete::PathDependentDiscrete(const MJArray& LookAtTimes_,
											double DeliveryTime_,
											double Barrier_,
											const PayOffBridge& ThePayOff_,
											double Rebate_)
	: PathDependent(LookAtTimes_), DeliveryTime(DeliveryTime_), Barrier(Barrier_), Rebate(Rebate_),
		ThePayOff(ThePayOff_), NumberOfTimes(LookAtTimes_.size())
{}

PathDependentDiscrete::PathDependentDiscrete(const MJArray& LookAtTimes_,
												double DeliveryTime_,
												double Barrier_,
												double Rebate_)
	: PathDependent(LookAtTimes_), DeliveryTime(DeliveryTime_), Barrier(Barrier_), Rebate(Rebate_),
		NumberOfTimes(LookAtTimes_.size()) 
{}

unsigned long PathDependentDiscrete::MaxNumberOfCashFlows() const
{
     return 1UL;
}

MJArray PathDependentDiscrete::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}
