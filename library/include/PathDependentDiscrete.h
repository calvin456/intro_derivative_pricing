/*
Exercice 7.2 write a class to do discrete knock-out options

Use definitions of discrete barrier option p.223,
The concepts and practice of mathematical finance, 2n ed, MJ

knock-out = up-and-out barrier


Exercise 7.2

Postby pzling » Tue Feb 28, 2012 7:30 am
Hi

Could I clarify if the rebate paid is intended to be a proportion of the premium paid or a fixed amount?

If it's a proportion of the premium paid, how should this be approached? Can it be done within the one class for the knock-out option?


Re: Exercise 7.2

Postby mj » Wed Feb 29, 2012 10:53 pm
it's generally a fixed amount


*/

#ifndef PATH_DEPENDENT_DISCRETE_H
#define PATH_DEPENDENT_DISCRETE_H

#include <PathDependent.h>
#include <PayOffBridge.h>
#include <wrapper.h>
#include <vector>
using namespace std;

class PathDependentDiscrete : public PathDependent
{
public:

	PathDependentDiscrete(const MJArray& LookAtTimes_,
						  double DeliveryTime_,
						  double Barrier_,
						  const PayOffBridge& ThePayOff_,
						  double Rebate_ = 0.0);

	PathDependentDiscrete(const MJArray& LookAtTimes_,
													double DeliveryTime_,
													double Barrier_,
													double Rebate_ = 0.0);


    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;

    virtual ~PathDependentDiscrete(){}


protected:
		double DeliveryTime;
		double Barrier;
		double Rebate;
		PayOffBridge ThePayOff;
		unsigned long NumberOfTimes;
};


#endif
