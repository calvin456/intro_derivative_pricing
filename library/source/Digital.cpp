/*
b3 project 1 :vanilla options in a bs world

*/

#include <Digital.h>

PayOffDigitalCall::PayOffDigitalCall(double Strike_)
                      :  PayOff(Strike_)
{}

double PayOffDigitalCall::operator()(double Spot) const
{
 
    if (Spot > Strike)
        return 1;

    return 0;
}
    

PayOff* PayOffDigitalCall::clone() const
{
    return new PayOffDigitalCall(*this);
}

double PayOffDigitalCall::GetStrike() const{ return Strike; }

void PayOffDigitalCall::SetStrike(double Strike_) { Strike = Strike_; }

PayOffDigitalPut::PayOffDigitalPut(double Strike_)
	: PayOff(Strike_)
{}

double PayOffDigitalPut::operator()(double Spot) const
{
 
    if (Spot < Strike)
        return 1;

    return 0;
}
    

PayOff* PayOffDigitalPut::clone() const
{
    return new PayOffDigitalPut(*this);
}

double PayOffDigitalPut::GetStrike() const{ return Strike; }

void PayOffDigitalPut::SetStrike(double Strike_) { Strike = Strike_; }

