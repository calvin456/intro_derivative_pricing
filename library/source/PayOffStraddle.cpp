//
//
//                          PayOff3.cpp
//
//

#include <PayOffStraddle.h>
#include <minmax.h>

PayOffStraddle::PayOffStraddle(double Strike_) :PayOff(Strike_)
{}

PayOffStraddle::PayOffStraddle(const MJArray& args) : PayOff(args[0])
{}

double PayOffStraddle::operator()(double Spot) const
{
   
	if(Spot <= Strike)
		return Strike - Spot;
	
	else
		return Spot -Strike ;
		
}

PayOff* PayOffStraddle::clone() const
{
    return new PayOffStraddle(*this);
}
