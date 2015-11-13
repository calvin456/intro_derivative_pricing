//PathDependentDiscreteDO.h


#ifndef PATH_DEPENDENT_DISCRETE_DO_H
#define PATH_DEPENDENT_DISCRETE_DO_H

#include <PathDependentDiscrete.h>
#include <PayOffBridge.h>
#include <vector>
using namespace std;

//discrete down-and-out barrier
class PathDependentDiscreteDO : public PathDependentDiscrete
{
public:

	PathDependentDiscreteDO(const MJArray& LookAtTimes_,
							double DeliveryTime_,
							double Barrier_,
							const PayOffBridge& ThePayOff_,
							double Rebate_ = 0.0);

	virtual unsigned long CashFlows(const MJArray& SpotValues,
									std::vector<MyCashFlow::CashFlow>& GeneratedFlows, method method_ = logscale) const;

	virtual ~PathDependentDiscreteDO(){}
	virtual PathDependent* clone() const;

private:

};


#endif
