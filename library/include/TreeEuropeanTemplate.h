//TreeEuropeanTemplate.h

#ifndef TREE_EUROPEAN_TEMPLATE_H
#define TREE_EUROPEAN_TEMPLATE_H

#include <TreeProducts.h>

template<typename T>
class TreeEuropeanTemplate : public TreeProduct
{
public:
	TreeEuropeanTemplate(double FinalTime,
						const T& ThePayOff_);
	~TreeEuropeanTemplate(){}
	TreeProduct* clone() const;

	double FinalPayOff(double Spot) const;

	double PreFinalValue(double Spot,
						double Time,
						double DiscountedFutureValue) const;
	 
	 double GetFinalTime() const{ return FinalTime; }
private:
	T ThePayOff;
	double FinalTime;
};

#endif