/*
Exercise 8.1 Find a class that does barrier options in the same TreeProduct class hierarchy.
Try it out.
How stable is the price? 
How might you improve the stability?

*/

#ifndef TREE_BARRIER_H
#define TREE_BARRIER_H

#include <TreeProducts.h>
#include <PayOffBridge.h>

class TreeBarrier : public TreeProduct
{

public: 

    TreeBarrier(double FinalTime,
                 const PayOffBridge& ThePayOff_);

    virtual TreeProduct* clone() const;
    virtual double FinalPayOff(double Spot) const;
    virtual double PreFinalValue(double Spot,
                                 double Time,
                                 double DiscountedFutureValue) const;
    virtual ~TreeBarrier(){}

private:

    PayOffBridge ThePayOff;

};

#endif

