/*
Exercice 7.1 write a class to do geomatric Asian options
*/

#ifndef PATH_DEPENDENT_ASIAN_GEO_H
#define PATH_DEPENDENT_ASIAN_GEO_H

#include <PathDependent.h>
#include <PayOffBridge.h>

class PathDependentAsianGeo : public PathDependent
{
public:

    PathDependentAsianGeo(const MJArray& LookAtTimes_, 
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);

    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~PathDependentAsianGeo(){}
    virtual PathDependent* clone() const;

private:

    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};


#endif

