//PayOffMultiAsset.h



#ifndef PAYOFF_MULTI_H
#define PAYOFF_MULTI_H

#include <PayOff3.h>

class PayOffMulti : public PayOff
{
public:

	PayOffMulti(double Strike_=0.0);


	virtual double operator()(double Spot) const ;
	virtual double operator()(const MJArray& Spots) const = 0;
	virtual ~PayOffMulti(){}
	

private:

};

//Implied fx rate set by default as one
class QuantoCall : public PayOffMulti
{
public:

	QuantoCall(double Strike_, double fxRate_=1.0);
	QuantoCall(const MJArray& args);
	virtual double operator()(const MJArray& Spots) const;
	virtual ~QuantoCall(){}
	virtual PayOff* clone() const;

private:
	double fxRate;
	

};

//Implied fx rate set by default as one
class QuantoPut : public PayOffMulti
{
public:

	QuantoPut(double Strike_, double fxRate_ = 1.0);
	QuantoPut(const MJArray& args);
	virtual double operator()(const MJArray& Spots) const;
	virtual ~QuantoPut(){}
	virtual PayOff* clone() const;

private:
	double fxRate;
	

};

//aka Margrabe option
class ExchangeOption : public PayOffMulti
{
public:
	ExchangeOption();
	ExchangeOption(const MJArray& args);
	virtual double operator()(const MJArray& Spots) const;
	virtual ~ExchangeOption(){}
	virtual PayOff* clone() const;

private:


};

class SpreadOption : public PayOffMulti
{
public:
	SpreadOption(double Strike_);
	SpreadOption(const MJArray& args);
	virtual double operator()(const MJArray& Spots) const;
	virtual ~SpreadOption(){}
	virtual PayOff* clone() const;

private:


};

#endif
