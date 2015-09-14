//VanillaOptionImpl.h

#ifndef VANILLA_IMPL_H
#define VANILLA_IMPL_H

#include<memory>

using namespace std;

class PayOff; //fwd decl

class VanillaOptionImpl
{
public:
	VanillaOptionImpl(PayOff* ThePayOffPtr_, double Expiry_);
	VanillaOptionImpl(){}
	double OptionPayOff(double Spot) const;
	double GetExpiry() const;

private:

	double Expiry;
	unique_ptr<PayOff> ThePayOffPtr; //smart pointer

};

VanillaOptionImpl::VanillaOptionImpl(PayOff* ThePayOffPtr_, double Expiry_)
	: ThePayOffPtr(ThePayOffPtr_), Expiry(Expiry_)
{}

double VanillaOptionImpl::GetExpiry() const
{
	return Expiry;
}

double VanillaOptionImpl::OptionPayOff(double Spot) const
{
	return ThePayOffPtr->operator ()(Spot);
}


#endif // !VANILLA_IMPL