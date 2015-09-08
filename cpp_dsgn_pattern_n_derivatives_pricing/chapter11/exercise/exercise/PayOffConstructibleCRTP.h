// PayOffConstructibleCRTP.h

#ifndef PAYOFF_CONSTRUCTIBLE_CRTP_H
#define PAYOFF_CONSTRUCTIBLE_CRTP_H

#include <iostream>

#include "PayOffFactoryCRTP.h"

#include <PayOff3.h>
#include <PayOffStraddle.h>
#include <DoubleDigital2.h>

#include <string>

template <class T>
class PayOffHelperCRTP
{
public:

	PayOffHelperCRTP(std::string);
	static PayOff* Create(const MJArray&);

};

template <class T>
PayOff* PayOffHelperCRTP<T>::Create(const MJArray& args)
{
	return new T(args);
}

template <class T>
PayOffHelperCRTP<T>::PayOffHelperCRTP(std::string id)
{
	PayOffFactoryCRTP& thePayOffFactory = PayOffFactoryCRTP::Instance();
	thePayOffFactory.RegisterPayOff(id, PayOffHelperCRTP<T>::Create);
}

#endif 