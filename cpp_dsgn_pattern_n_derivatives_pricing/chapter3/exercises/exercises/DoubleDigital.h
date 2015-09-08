//
//
//
//                          DoubleDigital.h
//
//                              

#ifndef DOUBLEDIGITAL_H
#define DOUBLEDIGITAL_H

#include <Payoff2.h>

class PayOffDoubleDigital : public PayOff
{
public:
    
    PayOffDoubleDigital(double LowerLevel_, double UpperLevel_);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffDoubleDigital(){}

	double GetStrike() const {}
	void SetStrike(double Strike_){}
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

