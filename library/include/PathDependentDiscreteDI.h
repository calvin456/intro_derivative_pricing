//PathDependentDiscreteDIC.h

#ifndef PATH_DEPENDENT_DISCRETE_DI_H
#define PATH_DEPENDENT_DISCRETE_DI_H

#include <PathDependentDiscrete.h>
#include <PayOffBridge.h>
#include <vector>
using namespace std;

//discrete down-and-in barrier
class PathDependentDiscreteDI : public PathDependentDiscrete
{
public:

	PathDependentDiscreteDI(const MJArray& LookAtTimes_,
							double DeliveryTime_,
							double Barrier_,
							const PayOffBridge& ThePayOff_,
							double Rebate_ = 0.0);

	virtual unsigned long CashFlows(const MJArray& SpotValues,
									std::vector<MyCashFlow::CashFlow>& GeneratedFlows, method method_ = logscale) const;

	virtual ~PathDependentDiscreteDI(){}
	virtual PathDependent* clone() const;

private:

};


#endif
