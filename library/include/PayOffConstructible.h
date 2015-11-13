// pay_off_construct_multi.h

//ex 10.2 Our class cannot handle a double digital as it needs two strikes.
//Work out a solution that will handle options with multiple parameters

#ifndef PAYOFF_CONSTRUCTIBLE_MULTI_H
#define PAYOFF_CONSTRUCTIBLE_MULTI_H

#include <iostream>
#include <string>
#include <arrays.h>

#include <PayOff3.h>
#include <PayOffStraddle.h>
#include <DoubleDigital2.h>

#include <PayOffFactory.h>

template<class T>
class PayOffHelper
{
public:
	PayOffHelper(std::string);
	static PayOff* Create(const MJArray& );
	~PayOffHelper(){}
};

template<class T>
PayOff* PayOffHelper<T>::Create(const MJArray& args)
{
	return new T(args);
}

template<class T>
PayOffHelper<T>::PayOffHelper(std::string id)
{
	PayOffFactory& thePayOffFactory = PayOffFactory::Instance();
	thePayOffFactory.RegisterPayOff(id, PayOffHelper<T>::Create);
	
}

#endif

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/
