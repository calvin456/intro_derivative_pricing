//
//
//                  Vanilla3.cpp
//
//
#include <Vanilla3.h>

using namespace std;
using namespace Vanilla;

VanillaOption::VanillaOption(const PayOffBridge& ThePayOff_, double Expiry_)
                               :  ThePayOff(ThePayOff_), Expiry(Expiry_)
{
}

double VanillaOption::GetExpiry() const
{
    return Expiry;
}

double VanillaOption::GetStrike() const
{
	return ThePayOff.GetStrike();
}

void VanillaOption::SetExpiry(double Expiry_)
{
	Expiry = Expiry_;
}

void VanillaOption::SetStrike(double Strike_)
{
	return ThePayOff.SetStrike(Strike_);
}

double VanillaOption::OptionPayOff(double Spot) const
{
    return ThePayOff(Spot);
}

//10.3

VanillaOption1::VanillaOption1(PayOff* ThePayOffPtr_, double Expiry_)
	:  ThePayOffPtr(ThePayOffPtr_), Expiry(Expiry_)
{}

VanillaOption1::VanillaOption1(unique_ptr<PayOff>& ThePayOffPtr_, double Expiry_)
	: ThePayOffPtr(move(ThePayOffPtr_)), Expiry(Expiry_)
{}

double VanillaOption1::GetExpiry() const
{
    return Expiry;
}

double VanillaOption1::OptionPayOff(double Spot) const
{
    return ThePayOffPtr->operator ()(Spot);
}




/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/
