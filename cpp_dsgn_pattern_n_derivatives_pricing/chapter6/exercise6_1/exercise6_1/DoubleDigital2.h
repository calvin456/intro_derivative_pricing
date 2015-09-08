//
//
//
//                          DoubleDigital2.h
//
//                              

//Edit file to include get and set func.

#ifndef DOUBLEDIGITAL2_H
#define DOUBLEDIGITAL2_H

#include <Payoff3.h>

using namespace std;

class PayOffDoubleDigital : public PayOff
{
public:
    
    PayOffDoubleDigital(double LowerLevel_, double UpperLevel_);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffDoubleDigital(){}
    virtual PayOff* clone() const;

	double GetLowerLevel() const;
	double GetUpperLevel() const;
    void SetStrike(double LowerLevel_, double UpperLevel_);

private:
    double LowerLevel;
    double UpperLevel;
};

#endif

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

