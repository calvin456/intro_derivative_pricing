//payoff_interest_derivatives.cpp

#include <payoff_interest_derivatives.h>

#include <minmax.h>

FRA::FRA(double Strike_, double t1_, double t2_) 
: PayOff(Strike_), t1(t1_), t2(t2_)
{}

double FRA::operator () (double Spot) const
{
	return (Spot - Strike)*(t2 - t1) ;
}

PayOff* FRA::clone() const
{
	return new FRA(*this);
}

Caplet::Caplet(double Strike_, double t1_, double t2_)
	: PayOff(Strike_), t1(t1_), t2(t2_)
{}

double Caplet::operator () (double Spot) const
{
	return max(Spot - Strike, 0.0)*(t2 - t1) ;
}

PayOff* Caplet::clone() const
{
	return new Caplet(*this);
}


FRAIA::FRAIA(double Strike_, double t1_, double t2_)
	: PayOff(Strike_), t1(t1_), t2(t2_)
{}

double FRAIA::operator () (double Spot) const
{
	return (Spot - Strike)*(t2 - t1) * (1.0 + Spot*(t2 - t1));
}

PayOff* FRAIA::clone() const
{
	return new FRAIA(*this);
}

CapletIA::CapletIA(double Strike_, double t1_, double t2_)
	: PayOff(Strike_), t1(t1_), t2(t2_)
{}

double CapletIA::operator () (double Spot) const
{
	return max(Spot - Strike, 0.0)*(t2 - t1) * (1.0 + Spot*(t2 - t1));
}

PayOff* CapletIA::clone() const
{
	return new CapletIA(*this);
}

FloorletIA::FloorletIA(double Strike_, double t1_, double t2_)
	: PayOff(Strike_), t1(t1_), t2(t2_)
{}

double FloorletIA::operator () (double Spot) const
{
	return max(Strike - Spot, 0.0)*(t2 - t1) * (1.0 + Spot*(t2 - t1));
}

PayOff* FloorletIA::clone() const
{
	return new FloorletIA(*this);
}