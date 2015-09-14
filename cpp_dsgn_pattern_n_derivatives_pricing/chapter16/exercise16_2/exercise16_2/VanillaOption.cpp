//VanillaOption.cpp
#include "VanillaOption.h"
#include "VanillaOptionImpl.h"


VanillaOption::VanillaOption(PayOff* ThePayOffPtr_, double Expiry_)
	: pimpl(new VanillaOptionImpl(ThePayOffPtr_, Expiry_))
{}

double VanillaOption::GetExpiry() const
{
	return pimpl->GetExpiry();
}

double VanillaOption::OptionPayOff(double Spot) const
{
	return pimpl->OptionPayOff(Spot);
}