//
//
//                      TreeEuropean.cpp
//
//

//Minor editing

#include <TreeEuropean.h>
#include <minmax.h>

TreeEuropean::TreeEuropean(double FinalTime,
                           const PayOffBridge& ThePayOff_)
                 : TreeProduct(FinalTime),
                   ThePayOff(ThePayOff_)
{
}

double TreeEuropean::FinalPayOff(double Spot) const
{
    return ThePayOff(Spot);
}

double TreeEuropean::PreFinalValue(double, //Spot, Borland compiler
                                 double, //Time,   doesnt like unused named variables
                                 double DiscountedFutureValue) const
{
    return DiscountedFutureValue;
}

TreeProduct* TreeEuropean::clone() const
{
    return new TreeEuropean(*this);
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

