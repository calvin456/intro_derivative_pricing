//hedging_strategy_sv.h

#ifndef HEDGE_STAT_SV_H
#define HEDGE_STAT_SV_H

#include <hedging_strategy.h>
#include <path_generation_heston.h>

template<typename U>
class HedgingStrategySV : public HedgingStrategy<U>{
	//delta hedging
	//Sell option and delta hedge by buying stocks
public:
		HedgingStrategySV(double OptionValue0, double r, shared_ptr<U> TheOption,
								shared_ptr<PathGenerationHeston> ThePathGeneration_,
								double T);

		virtual ~HedgingStrategySV();
		virtual double DoOnePath(args& args_) = 0;
		virtual unsigned long GetSteps() const;
protected:
		shared_ptr<PathGenerationHeston> ThePathGeneration;
};



//Time-dependent volatility
template<typename U>
class DeltaHedgingRMS : public HedgingStrategySV<U>{
	//rms vol [0,T]
	//Sell option and delta hedge by buying stocks

public:
		DeltaHedgingRMS(double OptionValue0, double r, shared_ptr<U> TheOption,
							shared_ptr<PathGenerationHeston> ThePathGeneration,
							double T);

	  virtual ~DeltaHedgingRMS(){}
	  virtual double DoOnePath(args& args_);
private:

};

template<typename U>
class DeltaHedgingRMSDec : public HedgingStrategySV<U>{
	//rms vol [s,T]
	//Sell option and delta hedge by buying stocks

public:
	DeltaHedgingRMSDec(double OptionValue0, double r, shared_ptr<U> TheOption,
							shared_ptr<PathGenerationHeston> ThePathGeneration,
							double T);
		virtual ~DeltaHedgingRMSDec(){}
		virtual double DoOnePath(args& args_);
private:

};

template<typename U>
class DeltaHedgingCurrentVol : public HedgingStrategySV<U>{
	//current volatility
	//Sell option and delta hedge by buying stocks

public:
	DeltaHedgingCurrentVol(double OptionValue0, double r, shared_ptr<U> TheOption,
								shared_ptr<PathGenerationHeston> ThePathGeneration,
								double T);
	  virtual ~DeltaHedgingCurrentVol(){}
	  virtual double DoOnePath(args& args_);
private:

};

template<typename U>
class DeltaHedgingInstantVol : public HedgingStrategySV<U>{
	//current volatility
	//Sell option and delta hedge by buying stocks

public:
	DeltaHedgingInstantVol(double OptionValue0, double r, shared_ptr<U> TheOption,
								shared_ptr<PathGenerationHeston> ThePathGeneration,
								double T);
	virtual ~DeltaHedgingInstantVol(){}
	virtual double DoOnePath(args& args_);
private:

};


#endif
