//
//
//																PayOffRegistration.cpp
//
//
#include <ArgListFactoryHelper.h>

#include <ToyLibrary/ToyLibrary.h>

namespace
{
	FactoryHelper<PayOff, PayOffCall> callHelper("call");
	FactoryHelper<PayOff, PayOffPut> putHelper("put");
	FactoryHelper<PayOff, PayOffSpread> spreadHelper("spread");
}
