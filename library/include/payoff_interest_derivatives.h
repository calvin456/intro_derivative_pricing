//payoff_interest_derivatives.h

#include <payoff3.h>

class FRA :public PayOff{
public:
	FRA(double Strike_, double t1_, double t2_);

	virtual double operator()(double Spot) const; //read fwd instead of spot. abstract base class payoff
	virtual ~FRA(){}
	virtual PayOff* clone() const;

private:
	double t1;
	double t2;
};

class Caplet :public PayOff{
	//call option on interst rate
public:
	Caplet(double Strike_, double t1_, double t2_);

	virtual double operator()(double Spot) const; //idem
	virtual ~Caplet(){}
	virtual PayOff* clone() const;

private:
	double t1;
	double t2;
};

//IA in-arrear

class FRAIA :public PayOff{
public:
	FRAIA(double Strike_, double t1_, double t2_);

	virtual double operator()(double Spot) const; //read fwd instead of spot. abstract base class payoff
	virtual ~FRAIA(){}
	virtual PayOff* clone() const;

private:
	double t1;
	double t2;
};

class CapletIA :public PayOff{
	//call option on interst rate
public:
	CapletIA(double Strike_, double t1_, double t2_);

	virtual double operator()(double Spot) const; //idem
	virtual ~CapletIA(){}
	virtual PayOff* clone() const;

private:
	double t1;
	double t2;
};

class FloorletIA :public PayOff{
	//call option on interst rate
public:
	FloorletIA(double Strike_, double t1_, double t2_);

	virtual double operator()(double Spot) const; //idem
	virtual ~FloorletIA(){}
	virtual PayOff* clone() const;

private:
	double t1;
	double t2;
};