//PathDependentDiscreteDO.h

// Use BS value as substitute for final value.See p. 225 and ex 9.12

#ifndef PATH_DEPENDENT_DISCRETE_DO_SU_H
#define PATH_DEPENDENT_DISCRETE_DO_SU_H

#include <PathDependentDiscrete.h>
#include <options.h>
#include <vector>

using namespace std;
using namespace MyOption;

//discrete down-and-out barrier
class PathDependentDiscreteDOSU : public PathDependentDiscrete
{
public:

	PathDependentDiscreteDOSU(const MJArray& LookAtTimes_,
							double DeliveryTime_,
							double Barrier_,
							std::shared_ptr<MyOption::Option> TheOption_,
							double Rebate_ = 0.0);

	virtual unsigned long CashFlows(const MJArray& SpotValues,
									std::vector<MyCashFlow::CashFlow>& GeneratedFlows, method method_ = logscale) const;

	virtual ~PathDependentDiscreteDOSU(){}
	virtual PathDependent* clone() const;

private:
	//double DeliveryTime;
	std::shared_ptr<MyOption::Option> TheOption;
	//unsigned long NumberOfTimes;
	
};


#endif
