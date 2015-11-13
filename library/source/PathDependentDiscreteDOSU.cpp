//PathDependentDiscreteDOSU.cpp


#include <cmath>
#include <PathDependentDiscreteDOSU.h>

PathDependentDiscreteDOSU::PathDependentDiscreteDOSU(const MJArray& LookAtTimes_,
													double DeliveryTime_,
													double Barrier_,
													std::shared_ptr<MyOption::Option> TheOption_,
													double Rebate_)
	: PathDependentDiscrete(LookAtTimes_, DeliveryTime_, Barrier_, Rebate_), 
		TheOption(TheOption_) 
{}

unsigned long PathDependentDiscreteDOSU::CashFlows(const MJArray& SpotValues,
	std::vector<MyCashFlow::CashFlow>& GeneratedFlows, method method_) const
{
	GeneratedFlows[0].TimeIndex = 0;
	GeneratedFlows[0].Amount = Rebate;

	unsigned long _NumberOfTimes = NumberOfTimes - 1;

	double _Barrier;
	if (method_ == logscale)
		_Barrier = log(Barrier);
	else
		_Barrier = Barrier;

	//compute products of heaviside functions
	for (unsigned long i = 0; i < _NumberOfTimes; i++)
		if (_Barrier >= SpotValues[i])	return 1UL;

	if (method_ == logscale)
		GeneratedFlows[0].Amount = TheOption->GetValue(exp(SpotValues[_NumberOfTimes - 1]));
	else
		GeneratedFlows[0].Amount = TheOption->GetValue(SpotValues[_NumberOfTimes - 1]);

	return 1UL;
}

PathDependent* PathDependentDiscreteDOSU::clone() const
{
	return new PathDependentDiscreteDOSU(*this);
}
