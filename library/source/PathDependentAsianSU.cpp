// PathDependentAsianSU.cpp


#include <cmath>
#include <PathDependentAsianSU.h>

PathDependentAsianSU::PathDependentAsianSU(const MJArray& LookAtTimes_,
										   double DeliveryTime_,
										   std::shared_ptr<MyOption::Option> TheOption_)
    : PathDependent(LookAtTimes_), DeliveryTime(DeliveryTime_), TheOption(TheOption_), 
		NumberOfTimes(LookAtTimes_.size()-1), Strike(TheOption_->GetStrike() * LookAtTimes_.size())
{}

unsigned long PathDependentAsianSU::MaxNumberOfCashFlows() const
{
     return 1UL;
}

MJArray PathDependentAsianSU::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long PathDependentAsianSU::CashFlows(const MJArray& SpotValues,
	std::vector<MyCashFlow::CashFlow>& GeneratedFlows, method method_) const
{
    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = 0.0;

  	double sum(0.0), _S(0.0);
	
    if(method_ == logscale){
        for (unsigned long i(0); i < NumberOfTimes; ++i) sum += exp(SpotValues[i]); 
         _S = exp(SpotValues[NumberOfTimes - 1]); 
    }else{
  	    for (unsigned long i(0); i < NumberOfTimes; ++i) sum += SpotValues[i];
        _S = SpotValues[NumberOfTimes - 1]; 
    }
	
	//This method is slower than the previous one.
	/*
	if (method_ == logscale){
		sum = SpotValues.apply(std::exp).sum();
		_S = exp(SpotValues[NumberOfTimes - 1]); //-2
	}else{
		sum = SpotValues.sum();
		_S = SpotValues[NumberOfTimes - 1]; //-2
	}
	*/

	double _Strike(Strike - sum);

  	if (_Strike < 0){ _S += - _Strike; _Strike = 0.0; }

  	TheOption->SetStrike(_Strike);
  	GeneratedFlows[0].Amount = 1.0 / (NumberOfTimes + 1) * TheOption->GetValue(_S); 

  	return 1UL;
}

PathDependent* PathDependentAsianSU::clone() const
{
    return new PathDependentAsianSU(*this);
}

