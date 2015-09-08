//	PayOffFactoryMono.h

//ex 11.1 Implement  the factory from chap. 10 using the monostate pattern
//instead of the Singleton pattern

#ifndef PAYOFF_FACTORY_MONO_H
#define PAYOFF_FACTORY_MONO_H
#include <PayOff3.h>

#include <map>
#include <string>
#include <memory>
#include <Arrays.h>

using namespace std;


typedef PayOff* (*CreatePayOffFunction)(const MJArray&);

class PayOffFactoryMono{

public:
	PayOffFactoryMono(){}
	PayOffFactoryMono(const PayOffFactoryMono&){}
	PayOffFactoryMono& operator=(const PayOffFactoryMono&){ return *this; }
	~PayOffFactoryMono(){};

	void RegisterPayOff(string PayOffId, CreatePayOffFunction CreatorFunction);

	unique_ptr<PayOff> CreatePayOff(string PayOffId, const MJArray&);

private:
	static map<string, CreatePayOffFunction> TheCreatorFunctions; //declaration

};



#endif 