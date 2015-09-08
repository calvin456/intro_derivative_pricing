//  PayOffConstructibleMono.h

//ex 11.1 implement the factory from chap. 10 using the monostate pattern instead of the singleton pattern.

#ifndef PAYOFF_CONSTRUCTIBLE_MONO_H
#define  PAYOFF_CONSTRUCTIBLE_MONO_H

#include <iostream>
#include <string>

#include <PayOff3.h>
#include "PayOffFactoryMono.h"

template <class T>
class PayOffHelperMono{
public:
	PayOffHelperMono(std::string);
	static PayOff* Create(const MJArray&);
};

template <class T>
PayOff* PayOffHelperMono<T>::Create(const MJArray& Strike){
	return new T(Strike);
}

template <class T>
PayOffHelperMono<T>::PayOffHelperMono(std::string id){
	PayOffFactoryMono theObject = PayOffFactoryMono(); // create new PayOffFactoryMono object
	theObject.RegisterPayOff(id, PayOffHelperMono<T>::Create);
}

#endif 