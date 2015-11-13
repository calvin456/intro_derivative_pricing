//PathDependentDiscreteDI.cpp


#include <cmath>
#include <PathDependentDiscreteDI.h>

PathDependentDiscreteDI::PathDependentDiscreteDI(const MJArray& LookAtTimes_,
												double DeliveryTime_,
												double Barrier_,
												const PayOffBridge& ThePayOff_,
												double Rebate_)
	: PathDependentDiscrete(LookAtTimes_, DeliveryTime_, Barrier_, ThePayOff_, Rebate_)
{}

unsigned long PathDependentDiscreteDI::CashFlows(const MJArray& SpotValues,
												std::vector<MyCashFlow::CashFlow>& GeneratedFlows, method method_) const
{
	GeneratedFlows[0].TimeIndex = 0;
	GeneratedFlows[0].Amount = Rebate;

	bool Touched(false);

	double _Barrier(Barrier);
	if(method_ == logscale)
		_Barrier = log(Barrier);

	//compute products of heaviside functions
	for (unsigned long i = 0; i < NumberOfTimes - 1; i++)
		if (_Barrier >= SpotValues[i])	{
			Touched = true;
			break;
		}

	if(Touched){
		if (method_ == logscale)
			GeneratedFlows[0].Amount = ThePayOff(exp(SpotValues[NumberOfTimes - 1]));
		else
			GeneratedFlows[0].Amount = ThePayOff(SpotValues[NumberOfTimes - 1]);
	}

	return 1;
}

PathDependent* PathDependentDiscreteDI::clone() const
{
	return new PathDependentDiscreteDI(*this);
}
