//PayOffMulti.cpp

#include <PayOffMulti.h>
#include <algorithm>
#include <iostream>

using namespace std;

PayOffMulti::PayOffMulti(double Strike_) : PayOff(Strike_)
{
}

double PayOffMulti::operator()(double Spot) const {
	cout << "derived class PayOffMulti : use operator()(const MJArray& args) instead" << endl;

	return 0.0;
}

QuantoCall::QuantoCall(double Strike_, double fxRate_) : PayOffMulti(Strike_), fxRate(fxRate_)
{
}

QuantoCall::QuantoCall(const MJArray& args) : PayOffMulti(args[0])
{}

double QuantoCall::operator()(const MJArray& Spots) const
{
	return fxRate * max(Spots[0]  - GetStrike(), 0.0); 
}

PayOff* QuantoCall::clone() const
{
	return new QuantoCall(*this);
}

QuantoPut::QuantoPut(double Strike_, double fxRate_) : PayOffMulti(Strike_), fxRate(fxRate_)
{
}

QuantoPut::QuantoPut(const MJArray& args) : PayOffMulti(args[0])
{}

double QuantoPut::operator () (const MJArray& Spots) const
{
	return fxRate * max(GetStrike() - Spots[0], 0.0); 
}

PayOff* QuantoPut::clone() const
{
	return new QuantoPut(*this);
}

ExchangeOption::ExchangeOption() : PayOffMulti()
{
}

ExchangeOption::ExchangeOption(const MJArray& args) : PayOffMulti(args[0])
{}

double ExchangeOption::operator()(const MJArray& Spots) const
{
	return max(Spots[0] - Spots[1], 0.0);
}

PayOff* ExchangeOption::clone() const
{
	return new ExchangeOption(*this);
}

SpreadOption::SpreadOption(double Strike_) : PayOffMulti(Strike_)
{
}

SpreadOption::SpreadOption(const MJArray& args) : PayOffMulti(args[0])
{}

double SpreadOption::operator()(const MJArray& Spots) const
{
	return max(Spots[0] - Spots[1] - GetStrike(), 0.0);
}

PayOff* SpreadOption::clone() const
{
	return new SpreadOption(*this);
}
