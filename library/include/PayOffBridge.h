//
//
//                       PayOffBridge.h
//
//

//include get and set func. to bridge class 
//insert null constructor

#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H

#include<PayOff3.h>


class PayOffBridge
{
public:
	PayOffBridge();
    PayOffBridge(const PayOffBridge& original);
    PayOffBridge(const PayOff& innerPayOff);

    inline double operator()(double Spot) const;
    ~PayOffBridge();
    PayOffBridge& operator=(const PayOffBridge& original);
	inline double GetStrike() const;
	inline void SetStrike(double Strike);
private:

    PayOff* ThePayOffPtr;

};

inline double PayOffBridge::operator()(double Spot) const
{
    return ThePayOffPtr->operator ()(Spot);
}

inline double PayOffBridge::GetStrike() const
{
	return ThePayOffPtr->GetStrike();
}

inline void PayOffBridge::SetStrike(double Strike)
{
	return ThePayOffPtr->SetStrike(Strike);
}

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

