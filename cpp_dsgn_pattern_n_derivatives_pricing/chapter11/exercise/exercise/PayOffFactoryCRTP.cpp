// PayOffFactoryCRTP.cpp 


#include "PayOffFactoryCRTP.h"
#include <iostream>
using namespace std;

void PayOffFactoryCRTP::RegisterPayOff(string PayOffId, CreatePayOffFunction CreatorFunction)
{
	TheCreatorFunctions.insert(pair<string, CreatePayOffFunction>(PayOffId, CreatorFunction));
}


PayOff* PayOffFactoryCRTP::CreatePayOff(string PayOffId, const MJArray& args)
{
	map<string, CreatePayOffFunction>::const_iterator
		i = TheCreatorFunctions.find(PayOffId);

	if (i == TheCreatorFunctions.end())
	{
		std::cout << PayOffId << " is an unknown payoff" << std::endl;
		return NULL;
	}

	return (i->second)(args);
}
