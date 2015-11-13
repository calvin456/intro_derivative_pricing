//
//
//                      TreeAmerican.cpp
//
//

#include <TreeAmericanBarrier.h>
#include <minmax.h>

TreeAmericanBarrier::TreeAmericanBarrier(double FinalTime,
                           const PayOffBridge& ThePayOff_)
                 : TreeProduct(FinalTime),
                   ThePayOff(ThePayOff_)
{
}

TreeProduct* TreeAmericanBarrier::clone() const
{
     return new TreeAmericanBarrier(*this);
}

double TreeAmericanBarrier::FinalPayOff(double Spot) const
{
    return ThePayOff(Spot);
}

double TreeAmericanBarrier::PreFinalValue(double Spot,
                                 double Time,  
                                 double DiscountedFutureValue) const
{
    return max(ThePayOff(Spot), DiscountedFutureValue);
}


