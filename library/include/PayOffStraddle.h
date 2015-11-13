//PayOffStraddl.h

/*
ex 10.1 Write a straddle class and register it with the factory
*/

#ifndef PAYOFFSTRADDLE_H
#define PAYOFFSTRADDLE_H

#include <PayOff3.h>

class PayOffStraddle : public PayOff
{
public:

    PayOffStraddle(double Strike_);
	  PayOffStraddle(const MJArray& args);
	  virtual double operator()(double Spot) const;
    virtual ~PayOffStraddle(){}
    virtual PayOff* clone() const;

private:

};

#endif
