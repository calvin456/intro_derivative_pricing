/*
Exercice 7.2 Price discrete barrier options which pay a rebate once barrier trigger

8 different options types encapsulated in given architecture

*/

#include <BarrierOption.h>
#include <algorithm>

using namespace std;

PayOffBarrier::PayOffBarrier(double Barrier_, double Strike_, double Rebate_)
	: Barrier(Barrier_), Rebate(Rebate_), PayOff(Strike_)
{
	if (Rebate < 0.0)	Rebate = 0.0;
}

 PayOffKOCall::PayOffKOCall(double Barrier_, double Strike_,double Rebate_)
	 : PayOffBarrier(Barrier_, Strike_, Rebate_)
{}

double PayOffKOCall::operator()(double Spot) const
{
	if (Spot  < Barrier)	return max(Spot-GetStrike(),0.0);
	else	return Rebate;
}

bool PayOffKOCall::IsTouched(double Spot) const
{
	if (Barrier <= Spot)	return true;
	else return false;
}

PayOff* PayOffKOCall::clone() const
{
    return new PayOffKOCall(*this);
}

PayOffKOPut::PayOffKOPut(double Barrier_, double Strike_, double Rebate_)
	: PayOffBarrier(Barrier_, Strike_, Rebate_)
{}

double PayOffKOPut::operator()(double Spot) const
{
	if (Spot  > Barrier)	return max(GetStrike()-Spot,0.0);
	else	return Rebate;
}

bool PayOffKOPut::IsTouched(double Spot) const
{
	if ( Barrier <= Spot)	return true;
	else return false;
}

PayOff* PayOffKOPut::clone() const
{
    return new PayOffKOPut(*this);
}

PayOffKICall::PayOffKICall(double Barrier_, double Strike_, double Rebate_)
	: PayOffBarrier(Barrier_, Strike_, Rebate_)
{}

double PayOffKICall::operator()(double Spot) const
{
	if (Spot  < Barrier)	return Rebate;
	else	return max(Spot-GetStrike(),0.0);
}

bool PayOffKICall::IsTouched(double Spot) const
{
	if ( Barrier <= Spot)	return true;
	else return false;
}

PayOff* PayOffKICall::clone() const
{
    return new PayOffKICall(*this);
}

PayOffKIPut::PayOffKIPut(double Barrier_, double Strike_, double Rebate_)
	: PayOffBarrier(Barrier_, Strike_, Rebate_)
{}

double PayOffKIPut::operator()(double Spot) const
{
	if (Spot  > Barrier)	return Rebate;
	else	return max(GetStrike()-Spot,0.0);
}

bool PayOffKIPut::IsTouched(double Spot) const
{
	if ( Barrier <= Spot)	return true;
	else return false;
}

PayOff* PayOffKIPut::clone() const
{
    return new PayOffKIPut(*this);
}

PayOffDownOutCall::PayOffDownOutCall(double Barrier_, double Strike_, double Rebate_)
	: PayOffBarrier(Barrier_, Strike_, Rebate_)
{}

double PayOffDownOutCall::operator()(double Spot) const
{
	if (Spot < Barrier)	return Rebate;
	else	return max(Spot - GetStrike(), 0.0);
}

bool PayOffDownOutCall::IsTouched(double Spot) const
{
	if (Spot <= Barrier)	return true;
	else return false;
}

PayOff* PayOffDownOutCall::clone() const
{
	return new PayOffDownOutCall(*this);
}

PayOffUpOutPut::PayOffUpOutPut(double Barrier_, double Strike_, double Rebate_)
	: PayOffBarrier(Barrier_, Strike_, Rebate_)
{}

double PayOffUpOutPut::operator()(double Spot) const
{
	if (Spot > Barrier)	return Rebate;
	else	return max(Spot - GetStrike(), 0.0);
}

bool PayOffUpOutPut::IsTouched(double Spot) const
{
	if (Spot >= Barrier)	return true;
	else return false;
}

PayOff* PayOffUpOutPut::clone() const
{
	return new PayOffUpOutPut(*this);
}