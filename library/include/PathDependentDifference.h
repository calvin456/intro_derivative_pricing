/*
Exercise 7.5 Write a class that pays the difference in pay-offs of
two arbitrary path-dependent derivatives

Re: Chap. 7, pb 5

Postby emza0114 � Sun Feb 24, 2013 11:48 am

*/

//
//
//                  PathDependentDifference.h
//
//

#ifndef PATH_DEPENDENT_DIFFERENCE_H
#define PATH_DEPENDENT_DIFFERENCE_H

#include <PathDependent.h>
#include <PayOffBridge.h>
#include <wrapper.h>
#include <vector>

class PathDependentDifference : public PathDependent
{
public:

    PathDependentDifference(const MJArray& LookAtTimes_,
							Wrapper<PathDependent>& PathDep1_,
                            Wrapper<PathDependent>& PathDep2_);

    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
                                    std::vector<CashFlow>& GeneratedFlows, method method_ = logscale) const;
    virtual ~PathDependentDifference(){}
    virtual PathDependent* clone() const;

private:
    Wrapper<PathDependent> PathDep1;
    Wrapper<PathDependent> PathDep2;


};


#endif
