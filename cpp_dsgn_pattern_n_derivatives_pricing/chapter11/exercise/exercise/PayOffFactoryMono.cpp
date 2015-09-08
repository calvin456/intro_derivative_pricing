//   PayOffFactoryMono.cpp 


#include "PayOffFactoryMono.h"
#include <iostream>


map<string, CreatePayOffFunction> PayOffFactoryMono::TheCreatorFunctions; //definition

void PayOffFactoryMono::RegisterPayOff(string PayOffId, CreatePayOffFunction CreatorFunction)
{
	TheCreatorFunctions.insert(pair<string, CreatePayOffFunction>(PayOffId, CreatorFunction));
}

unique_ptr<PayOff> PayOffFactoryMono::CreatePayOff(string PayOffId, const MJArray& Strike)
{
	map<string, CreatePayOffFunction>::const_iterator	i = TheCreatorFunctions.find(PayOffId);

	if (i == TheCreatorFunctions.end()){
		cout << PayOffId << " is an unknown payoff" << std::endl;
		return NULL;
	}

	return unique_ptr<PayOff>(i->second(Strike));
}

