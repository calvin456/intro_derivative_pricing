//
//
//
//                            DoubleDigital2.cpp
//
//

#include <DoubleDigital2.h>

PayOffDoubleDigital::PayOffDoubleDigital(double LowerLevel_, double UpperLevel_)
	: PayOff(), LowerLevel(LowerLevel_), UpperLevel(UpperLevel_)
{}

double PayOffDoubleDigital::operator()(double Spot) const
{
    if (Spot <= LowerLevel)
        return 0;
    if (Spot >= UpperLevel)
        return 0;

    return 1;
}
    

PayOff* PayOffDoubleDigital::clone() const
{
    return new PayOffDoubleDigital(*this);
}

double PayOffDoubleDigital::GetLowerLevel() const { return LowerLevel; }
double PayOffDoubleDigital::GetUpperLevel() const { return UpperLevel; }

void  PayOffDoubleDigital::SetStrike(double LowerLevel_, double UpperLevel_)
{
	LowerLevel = LowerLevel_;
	UpperLevel = UpperLevel_;
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

