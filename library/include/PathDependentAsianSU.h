//  PathDependentAsianSU.h

//Use BS value as substitute for final value. See p. 225 and ex 9.12


#ifndef PATH_DEPENDENT_ASIAN_SU_H
#define PATH_DEPENDENT_ASIAN_SU_H

#include <PathDependent.h>
#include <options.h>

using namespace std;
using namespace MyOption;
using namespace MyCashFlow;


class PathDependentAsianSU : public PathDependent
{
public:

	PathDependentAsianSU(const MJArray& LookAtTimes_,
                       double DeliveryTime_,
					   std::shared_ptr<MyOption::Option> TheOption_);

    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues,
		std::vector<MyCashFlow::CashFlow>& GeneratedFlows, method method_ = logscale) const;
    virtual ~PathDependentAsianSU(){}
    virtual PathDependent* clone() const;

private:

    double DeliveryTime;
	std::shared_ptr<MyOption::Option> TheOption;
    unsigned long NumberOfTimes;
	double Strike;
};


#endif

