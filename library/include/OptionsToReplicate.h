//OptionsToReplicate.h

/*Joshi, The concepts and pratice of mathematical finance
10.2 continuous barrier option, p. 245-246

Joshi, RBS
Pricing discretely sampled path-dependent exotic options using replication methods
*/

#ifndef OPTION_TO_REPLI_H
#define OPTION_TO_REPLI_H

#include <vector>
#include <map>
#include <options.h>

using namespace std;


class OptionToReplicate{

public:
	OptionToReplicate(double Strike,
		double Barrier,
		double r,
		double Vol,
		double Expiry,
		double d = 0.0);

	OptionToReplicate(const OptionToReplicate& other);


	virtual ~OptionToReplicate(){}
	virtual void GeneratePtf(unsigned long steps, shared_ptr<Option> OptionFinal) = 0;  //final payoff digital, call spread
	virtual void GeneratePtf1(unsigned long steps, shared_ptr<Option> OptionFinal) = 0;//unequal time step
	virtual void GeneratePtf(unsigned long steps, const vector<double>& Vol, shared_ptr<Option> OptionFinal) = 0; //time-dep vol

	virtual double GetValue(double Spot, double t, shared_ptr<Option> OptionFinal) const = 0; //t = time left to expiry
	virtual double GetValue(double Spot, const vector<double>& Vol, double t, shared_ptr<Option> OptionFinal) const = 0; //time-dep vol
	virtual void setRate(double r_){ r = r_; }
protected:
	double Strike;
	double Barrier;
	double Expiry;
	double r;
	double d;
	double Vol;

};


class DownAndOutCall : public OptionToReplicate{

public:
	DownAndOutCall(double Strike,
		double Barrier,
		double r,
		double Vol,
		double Expiry,
		double d = 0.0);
	virtual ~DownAndOutCall(){}
	virtual void GeneratePtf(unsigned long steps, shared_ptr<Option> OptionFinal);
	virtual void GeneratePtf1(unsigned long steps, shared_ptr<Option> OptionFinal);
	virtual void GeneratePtf(unsigned long steps, const vector<double>& Vol, shared_ptr<Option> OptionFinal);

	virtual double GetValue(double _Spot, double _t, shared_ptr<Option> OptionFinal) const;
	virtual double GetValue(double _Spot, const vector<double>& _Vol, double _t, shared_ptr<Option> OptionFinal) const;
private:

	mutable map<double, PutOption> Portfolio;
};


class UpAndOutCall : public OptionToReplicate{

public:
	UpAndOutCall(double Strike,
		double Barrier,
		double r,
		double Vol,
		double Expiry,
		double d = 0.0);
	virtual ~UpAndOutCall(){}
	virtual void GeneratePtf(unsigned long steps, shared_ptr<Option> OptionFinal);
	virtual void GeneratePtf1(unsigned long steps, shared_ptr<Option> OptionFinal);
	virtual void GeneratePtf(unsigned long steps, const vector<double>& Vol, shared_ptr<Option> OptionFinal);

	virtual double GetValue(double _Spot, double _t, shared_ptr<Option> OptionFinal) const;
	virtual double GetValue(double _Spot, const vector<double>& _Vol, double _t, shared_ptr<Option> OptionFinal) const;
private:

	mutable map<double, CallOption> Portfolio;
};

#endif
