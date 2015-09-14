//VanillaOption.h

/*
ex 16.2 implement a class using the PIMPL idiom

VanillaOption.h - public part
VanillaOptionImpl.h - private part

PIMPL = Private Implementation
synomym = opaque pointer, cheshire cat

see herbsutter.com, Guru of the Week, #7a-7c  
*/

#ifndef VANILLA_H
#define VANILLA_H
#include<PayOff3.h>
#include<memory>

using namespace std;

class VanillaOptionImpl; //fwd decl

class VanillaOption{

public:
	VanillaOption(PayOff* ThePayOffPtr_, double Expiry);
	~VanillaOption(){}
	double OptionPayOff(double Spot) const;
	double GetExpiry() const;
private:

	shared_ptr<VanillaOptionImpl> pimpl; //pointer to impl
};

#endif
