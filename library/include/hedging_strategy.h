//hedging_strategy.h

#ifndef HEDGE_STAT_H
#define  HEDGE_STAT_H

#include <BlackScholesFormulas.h>
#include <path_generation_gbm.h>
#include <vector>
#include <memory>
#include <options.h>

//Assume market maker's role
//Will not close out the position once sold
//Final p&l against option payoff

template<typename U>
class HedgingStrategy{
	//abstract class
public:
		HedgingStrategy(double OptionValue0_, double r_, shared_ptr<U> TheOption_,
						double T_);

		virtual ~HedgingStrategy(){}
		virtual double DoOnePath(args& args_) = 0;
		virtual unsigned long GetSteps() const = 0;
protected:
		shared_ptr<U> TheOption;
		double r;
		double OptionValue0;
		double T;

};



template<typename U>
class DeltaHedging : public HedgingStrategy<U>{
	//delta hedging
	//Sell option and delta hedge by buying stocks
public:
		DeltaHedging(double OptionValue0, double r, shared_ptr<U> TheOption,
					PathGenerationGBM* ThePathGeneration,
					double T);

		virtual ~DeltaHedging(){}
		virtual double DoOnePath(args& args_);
		virtual unsigned long GetSteps() const{return ThePathGeneration->GetSteps();}
private:
		unique_ptr<PathGenerationGBM> ThePathGeneration;
};

//---------------------------------------------------------------------------------------------
template<typename U>
class SnLHedging : public HedgingStrategy<U>{
	// stop-and-loss hedging

public:
	SnLHedging(double OptionValue0, double r, shared_ptr<U> TheOption,
					PathGenerationGBM* ThePathGeneration,
					double T);

		virtual ~SnLHedging(){}
		virtual double DoOnePath(args& args_);
		virtual unsigned long GetSteps() const{return ThePathGeneration->GetSteps();}
private:
	unique_ptr<PathGenerationGBM> ThePathGeneration;
};

template<typename U, typename V>
class GammaHedging : public HedgingStrategy<U>{
	//gamma hedging
	//Use option with next available strike and same other params (eg. Eurex +4,+2,+1,+.5) ?
	//What if use sme option to hedge gamma ?

public:
		GammaHedging(double OptionValue0, double r,
					shared_ptr<U> TheOption, shared_ptr<V> TheOption1,
					PathGenerationGBM* ThePathGeneration,
					double T);

		virtual ~GammaHedging(){}
		virtual double DoOnePath(args& args_);
		virtual unsigned long GetSteps() const{return ThePathGeneration->GetSteps();}
private:
		shared_ptr<V> TheOption1; //hedging option
		unique_ptr<PathGenerationGBM> ThePathGeneration;
};

#endif
