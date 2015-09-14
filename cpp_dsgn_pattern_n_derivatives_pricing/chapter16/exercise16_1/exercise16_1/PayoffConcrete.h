//
//
//										PayOffConcrete.h
//
//
#ifndef PAYOFF_CONCRETE_H
#define PAYOFF_CONCRETE_H

#include "PayOff.h"



class PayOffCall : public PayOff
{
public:

	PayOffCall(double Strike_);

	virtual double operator()(double Spot) const;
	virtual ~PayOffCall(){}
	virtual PayOff* clone() const; // change to PayOffCall* if your compiler is up to date

private:

	double Strike;

};


class PayOffPut : public PayOff
{
public:

	PayOffPut(double Strike_);

	virtual double operator()(double Spot) const;
	virtual ~PayOffPut(){}
	virtual PayOff* clone() const;

private:

	double Strike;

};


#endif
