//
//
//
//                          Power.h
//
//                              

#ifndef POWER_H
#define POWER_H

#include <Payoff2.h>

class PayOffPowerCall : public PayOff
{
public:
    
    PayOffPowerCall(double Strike_, double Order_);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffPowerCall(){}

private:

    double Strike;
    double Order;


};


class PayOffPowerPut : public PayOff
{
public:
    
    PayOffPowerPut(double Strike_, double Order_);
    
    virtual double operator()(double Spot) const;
    virtual ~PayOffPowerPut(){}

private:

    double Strike;
    double Order;


};


#endif