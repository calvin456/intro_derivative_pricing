/*
Exercise 8.1
*/

#include <TreeBarrier.h>
#include <minmax.h>

TreeBarrier::TreeBarrier(double FinalTime,
                           const PayOffBridge& ThePayOff_)
                 : TreeProduct(FinalTime),
                   ThePayOff(ThePayOff_)
{
}

double TreeBarrier::FinalPayOff(double Spot) const
{
    return ThePayOff(Spot);
}

double TreeBarrier::PreFinalValue(double Spot, 
                                 double Time,  
                                 double DiscountedFutureValue) const
{
    return DiscountedFutureValue;
}

TreeProduct* TreeBarrier::clone() const
{
    return new TreeBarrier(*this);
}


