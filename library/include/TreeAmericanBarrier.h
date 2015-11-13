/*
Trees ex. 8.6 Implement an American knock-in option pricer on a tree.

(Use an additional auxiliary variable to indicate whether or not the option has knocked-in, 
and compute that the value at each node in both cases.)

*/

#ifndef TREE_AMERICAN_BARRIER_H
#define TREE_AMERICAN_BARRIER_H

#include <TreeProducts.h>
#include <PayOffBridge.h>

class TreeAmericanBarrier : public TreeProduct
{

public: 

	enum Type {PayOffKOCall, PayOffKOPut, PayOffKICall, PayOffKIPut};

	Type ThePayOff_;
	
    TreeAmericanBarrier(double FinalTime,
                 const PayOffBridge& ThePayOff_);

    virtual TreeProduct* clone() const;
    virtual double FinalPayOff(double Spot) const;
    virtual double PreFinalValue(double Spot,
                                 double Time,
                                 double DiscountedFutureValue) const;
    virtual ~TreeAmericanBarrier(){}

private:

    PayOffBridge ThePayOff;

};

#endif

