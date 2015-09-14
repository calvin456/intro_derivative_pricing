//
//
//												PayOffConcrete.cpp
//
//

#include "PayOffConcrete.h"


PayOffCall::PayOffCall(double Strike_) : Strike(Strike_)
{
}

double PayOffCall::operator () (double Spot) const
{
	return Spot - Strike > 0.0 ? Spot - Strike : 0.0;
}

PayOff* PayOffCall::clone() const
{
	return new PayOffCall(*this);
}


double PayOffPut::operator () (double Spot) const
{
	return Strike - Spot > 0.0 ? Strike - Spot : 0.0;
	;
}

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_)
{
}

PayOff* PayOffPut::clone() const
{
	return new PayOffPut(*this);
}


