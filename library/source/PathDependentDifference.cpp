/*
Re: Chap. 7, pb 5

Postby emza0114 » Sun Feb 24, 2013 11:48 am
*/

//
//
/*


Re: Chap. 7, pb 5

Postby mj » Tue Sep 28, 2010 12:10 am
Whilst merging the cash-flow times and look-at times would be a pain, it would only need to be done once at construction time so it would not be an efficiency issue.


Re: Chap. 7, pb 5

Postby mj » Mon Feb 25, 2013 9:47 am
you haven't initialized
PayOffBridge ThePayOff;
in the constructor list

so it's looking for a default constructor for the PayOffBridge class and not finding one.

*/


//
//                    PathDependentDifference.cpp
//
//

#include <PathDependentDifference.h>
#include <PathDependent.h>
#include <cmath>
#include <algorithm>
#include <vector>

#include<iostream>

PathDependentDifference::PathDependentDifference(const MJArray& LookAtTimes_,
												Wrapper<PathDependent>& PathDep1_,
												Wrapper<PathDependent>& PathDep2_)
    :PathDep1(PathDep1_), PathDep2(PathDep2_), PathDependent(LookAtTimes_)
{}

unsigned long PathDependentDifference::MaxNumberOfCashFlows() const
{
   return std::max(PathDep1->MaxNumberOfCashFlows(), PathDep2->MaxNumberOfCashFlows());

 }

//Merge possible cash flow times of the two derivatives

MJArray PathDependentDifference::PossibleCashFlowTimes() const
{
   MJArray PossibleCFTimes1(PathDep1->PossibleCashFlowTimes());
   MJArray PossibleCFTimes2(PathDep2->PossibleCashFlowTimes());

   unsigned long size_ = PathDep1->PossibleCashFlowTimes().size() + PathDep2->PossibleCashFlowTimes().size();

   MJArray PossibleCFTimes(size_);

   PossibleCFTimes = PossibleCFTimes1.merge(PossibleCFTimes2);

   PossibleCFTimes.remove_duplicate();

   return PossibleCFTimes;
}

unsigned long PathDependentDifference::CashFlows(const MJArray& SpotValues,
												std::vector<CashFlow>& GeneratedFlows, method method_) const
{
	std::vector<CashFlow> GeneratedFlows1(PathDep1->MaxNumberOfCashFlows());
	std::vector<CashFlow> GeneratedFlows2(PathDep2->MaxNumberOfCashFlows());

	PathDep1->CashFlows(SpotValues, GeneratedFlows1);
	PathDep2->CashFlows(SpotValues, GeneratedFlows2);

	//Allow for possibility of asymetric payoffs

	unsigned long k = 0;

	for(unsigned long i=0;i < GeneratedFlows.size();++i){

		while (PossibleCashFlowTimes()[i] != PathDep1->PossibleCashFlowTimes()[i])	{ ++k; }

		if(k >= GeneratedFlows1.size())	break;

		GeneratedFlows[k].TimeIndex = k;
		GeneratedFlows[k].Amount = GeneratedFlows1[k].Amount;
	}

	k = 0;

	for(unsigned long i=0;i < GeneratedFlows.size();++i){
		while (PossibleCashFlowTimes()[i] != PathDep2->PossibleCashFlowTimes()[i]) { ++k; }

		if (k >= GeneratedFlows2.size())	break;

		GeneratedFlows[k].TimeIndex = k;
		GeneratedFlows[k].Amount -= GeneratedFlows2[k].Amount;
	}

    return MaxNumberOfCashFlows();
}

PathDependent* PathDependentDifference::clone() const
{
    return new PathDependentDifference(*this);
}
