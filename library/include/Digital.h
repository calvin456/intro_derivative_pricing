/*
b3 project 1 :vanilla options in a bs world

*/

#ifndef DIGITAL_H
#define DIGITAL_H

#include <Payoff3.h>

class PayOffDigitalCall : public PayOff
{
public:

    PayOffDigitalCall(double Strike_);

    virtual double operator()(double Spot) const;
	virtual ~PayOffDigitalCall(){}
    virtual PayOff* clone() const;
	virtual double GetStrike() const;
	virtual void SetStrike(double Strike_);
private:

    //double Strike;

};

class PayOffDigitalPut : public PayOff
{
public:

    PayOffDigitalPut(double Strike_);

    virtual double operator()(double Spot) const;
    virtual ~PayOffDigitalPut(){}
    virtual PayOff* clone() const;
	virtual double GetStrike() const;
	virtual void SetStrike(double Strike_);
private:

    //double Strike;

};


#endif


