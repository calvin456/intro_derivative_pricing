//
//
//                          PayOff3.cpp
//
//

#include <PayOff3.h>
//#include <minmax.h>
#include <algorithm> //part of VC12 no need anymore for header minmax anymore

using namespace std;

PayOff::PayOff(double Strike_) :Strike(Strike_){}

double PayOff::GetStrike() const{ return Strike; }

void PayOff::SetStrike(double Strike_) { Strike =  Strike_; }

PayOffCall::PayOffCall(double Strike_) : PayOff(Strike_)
{}

PayOffCall::PayOffCall(const MJArray& args) : PayOff(args[0])
{}

double PayOffCall::operator () (double Spot) const
{
    return max(Spot-Strike,0.0);
}

PayOff* PayOffCall::clone() const
{
    return new PayOffCall(*this);
}

PayOffPut::PayOffPut(double Strike_) : PayOff(Strike_)
{}

PayOffPut::PayOffPut(const MJArray& args) : PayOff(args[0])
{}

double PayOffPut::operator () (double Spot) const
{
    return max(Strike-Spot,0.0);
}

PayOff* PayOffPut::clone() const
{
    return new PayOffPut(*this);
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

