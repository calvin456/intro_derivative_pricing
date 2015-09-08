//PayOffFactoryCRTP.h

//Use CRTP to implement "pay off factory*

// "factory pattern " = prototype + singleton design pattern
// use helper class as interface to factory. ie. utilty class in this specific case

#ifndef PAYOFF_FACTORY_CRTP_H
#define PAYOFF_FACTORY_CRTP_H

#include<map>
#include<string>
#include "SingletonCRTP.h"
#include <Arrays.h>
#include <PayOff3.h>

using namespace std;

//Factory Class Declaration 

//Use curiously recurring template pattern

class PayOffFactoryCRTP : public Singleton<PayOffFactoryCRTP>
{
public:

	typedef PayOff* (*CreatePayOffFunction)(const MJArray&);

	void RegisterPayOff(std::string, CreatePayOffFunction);
	PayOff* CreatePayOff(std::string PayOffId, const MJArray&);

private:
	std::map<std::string, CreatePayOffFunction> TheCreatorFunctions;
	PayOffFactoryCRTP(){}

	friend class Singleton<PayOffFactoryCRTP>;
};

#endif