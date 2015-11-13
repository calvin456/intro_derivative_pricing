//TreeEuropeanTemplate.cpp

#include "TreeEuropeanTemplate.h"
//#include <minmax.h>

template<class T>
TreeEuropeanTemplate<T>::TreeEuropeanTemplate(double FinalTime,
											  const T& ThePayOff_)
	: TreeProduct(FinalTime), ThePayOff(ThePayOff_)
{}

template<class T>
double TreeEuropeanTemplate<T>::FinalPayOff(double Spot) const
{
	return ThePayOff(Spot);
}

template<class T>
double TreeEuropeanTemplate<T>::PreFinalValue(double Spot,
											  double Time,
											  double DiscountedFutureValue) const
{
	return DiscountedFutureValue;
}

template<class T>
TreeProduct* TreeEuropeanTemplate<T>::clone() const
{
	return new TreeEuropeanTemplate(*this);
}

