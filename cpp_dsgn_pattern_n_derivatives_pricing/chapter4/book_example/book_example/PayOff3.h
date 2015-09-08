//
//
//                            PayOff3.h
//
//

#ifndef PAYOFF3_H
#define PAYOFF3_H

class PayOff
{
public:

    PayOff(){};

    virtual double operator()(double Spot) const=0;
    virtual ~PayOff(){}
    virtual PayOff* clone() const=0;
	virtual double GetStrike() const = 0;
	virtual void SetStrike(double Strike_) = 0;

private:
    
};

class PayOffCall : public PayOff
{
public:

    PayOffCall(double Strike_);

    virtual double operator()(double Spot) const;
    virtual ~PayOffCall(){}
    virtual PayOff* clone() const;
	virtual double GetStrike() const;
	virtual void SetStrike(double Strike_);
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
	virtual double GetStrike() const;
	virtual void SetStrike(double Strike_);
private:

    double Strike;

};

#endif

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

