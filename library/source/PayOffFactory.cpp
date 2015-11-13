// pay_off_factory_multi.cpp

//ex 10.2 Our class cannot handle a double digital as it needs two strikes.
//Work out a solution that will handle options w / multiple parameters

#include <PayOffFactory.h>
#include <iostream>
#include <utility>
using namespace std;


void PayOffFactory::RegisterPayOff(string PayOffId, CreatePayOffFunction CreatorFunction)
{
	TheCreatorFunctions.insert(pair<string, CreatePayOffFunction>(PayOffId, CreatorFunction));
}


PayOff* PayOffFactory::CreatePayOff(string PayOffId, const MJArray& args)
{
	map<string, CreatePayOffFunction>::const_iterator	i = TheCreatorFunctions.find(PayOffId);
	
	if (i == TheCreatorFunctions.end())
	{
		cout << PayOffId << " is an unknown payoff" << endl;
		return NULL;
	}

	return (i->second)(args);
	
}


PayOffFactory& PayOffFactory::Instance()
{
	static PayOffFactory theFactory;
	return theFactory;
}

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
