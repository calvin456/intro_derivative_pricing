//hedging_strategy_sv.cpp

#include <algorithm>
#include "hedging_strategy_sv.h"

template<typename U>
HedgingStrategySV<U>::HedgingStrategySV(double OptionValue0, double r, shared_ptr<U> TheOption,
										shared_ptr<PathGenerationHeston> ThePathGeneration_,
										double T)
	: HedgingStrategy<U>(OptionValue0, r, TheOption, T), ThePathGeneration(ThePathGeneration_)
{}

template<typename U>
HedgingStrategySV<U>::~HedgingStrategySV(){}

template<typename U>
unsigned long HedgingStrategySV<U>::GetSteps() const{
	return ThePathGeneration->GetSteps();
}

template<typename U>
DeltaHedgingRMS<U>::DeltaHedgingRMS(double OptionValue0, double r, shared_ptr<U> TheOption,
									shared_ptr<PathGenerationHeston> ThePathGeneration_,
									double T)
	:HedgingStrategySV(OptionValue0, r, TheOption, ThePathGeneration_, T)
{}

template<typename U>
double DeltaHedgingRMS<U>::DoOnePath(args& args_) {

	MJArray stock_path = ThePathGeneration->GetWholePath(args_);

	double vol(sqrt(ThePathGeneration->rms_sigma(0, stock_path.size()-1)));
	double t(TheOption->GetExpiry());
	double delta(TheOption->GetDelta(stock_path[0], vol, t));
	double borrow(delta * stock_path[0] - OptionValue0);
	double PnL(0.0);
	double deltaT(T / ThePathGeneration->GetSteps());

	//simple interest calculation. no compounding
	double a(1.0 + r * deltaT);

	for (size_t i(1); i < stock_path.size() - 1; ++i){
		double delta_0(delta);
		t -= deltaT;
		delta = TheOption->GetDelta(stock_path[i], vol, t);
		double b((delta - delta_0) * stock_path[i]);
		PnL += delta_0 * stock_path[i] - borrow * a - TheOption->GetValue(stock_path[i], vol, t);
		borrow += b;
	}

	PnL += delta * stock_path[stock_path.size() - 1] - borrow * a;

	return PnL - TheOption->GetPayOff(stock_path[stock_path.size() - 1]);
}

template<typename U>
DeltaHedgingRMSDec<U>::DeltaHedgingRMSDec(double OptionValue0, double r, shared_ptr<U> TheOption,
										  shared_ptr<PathGenerationHeston> ThePathGeneration_,
										  double T)
	:HedgingStrategySV(OptionValue0, r, TheOption, ThePathGeneration_, T)
{}

template<typename U>
double DeltaHedgingRMSDec<U>::DoOnePath(args& args_) {

	MJArray stock_path = ThePathGeneration->GetWholePath(args_);

	double vol(sqrt(ThePathGeneration->rms_sigma(0, stock_path.size() - 1)));
	double t(TheOption->GetExpiry());
	double delta(TheOption->GetDelta(stock_path[0], vol, t));
	double borrow(delta * stock_path[0] - OptionValue0);
	double PnL(0.0);
	double deltaT(T / ThePathGeneration->GetSteps());

	//simple interest calculation. no compounding
	double a(1.0 + r * deltaT);

	for (size_t i(1); i < stock_path.size() - 1; ++i){
		vol = sqrt(ThePathGeneration->rms_sigma(i, stock_path.size() - 1));
		double delta_0(delta);
		t -= deltaT;
		delta = TheOption->GetDelta(stock_path[i], vol, t);
		double b((delta - delta_0) * stock_path[i]);
		PnL += delta_0 * stock_path[i] - borrow * a - TheOption->GetValue(stock_path[i], vol, t);
		borrow += b;
	}

	PnL += delta * stock_path[stock_path.size() - 1] - borrow * a;

	return PnL - TheOption->GetPayOff(stock_path[stock_path.size() - 1]);
}

template<typename U>
DeltaHedgingCurrentVol<U>::DeltaHedgingCurrentVol(double OptionValue0, double r, shared_ptr<U> TheOption,
												  shared_ptr<PathGenerationHeston> ThePathGeneration_,
												  double T)
	:HedgingStrategySV(OptionValue0, r, TheOption, ThePathGeneration_, T)
{}

template<typename U>
double DeltaHedgingCurrentVol<U>::DoOnePath(args& args_) {

	MJArray stock_path = ThePathGeneration->GetWholePath(args_);
	MJArray vol_path = ThePathGeneration->GetSigma();

	//stock_path.print();
	//vol_path.print();

	double t(TheOption->GetExpiry());
	double delta(TheOption->GetDelta(stock_path[0], sqrt(vol_path[0]), t));
	double borrow(delta * stock_path[0] - OptionValue0);
	double PnL(0.0);
	double deltaT(T / ThePathGeneration->GetSteps());

	//simple interest calculation. no compounding
	double a(1.0 + r * deltaT);

	for (size_t i(1); i < stock_path.size() - 1; ++i){
		double delta_0(delta);
		t -= deltaT;
		delta = TheOption->GetDelta(stock_path[i], vol_path[i], t);
		double b((delta - delta_0) * stock_path[i]);
		PnL += delta_0 * stock_path[i] - borrow * a - TheOption->GetValue(stock_path[i], vol_path[i], t);
		borrow += b;
	}

	PnL += delta * stock_path[stock_path.size() - 1] - borrow * a;

	return PnL - TheOption->GetPayOff(stock_path[stock_path.size() - 1]);
}

//-----------------------

template<typename U>
DeltaHedgingInstantVol<U>::DeltaHedgingInstantVol(double OptionValue0, double r, shared_ptr<U> TheOption,
												  shared_ptr<PathGenerationHeston> ThePathGeneration_,
												  double T)
	:HedgingStrategySV(OptionValue0, r, TheOption, ThePathGeneration_, T)
{}

template<typename U>
double DeltaHedgingInstantVol<U>::DoOnePath(args& args_) {

	MJArray stock_path = ThePathGeneration->GetWholePathInstant(args_);
	MJArray vol_path = ThePathGeneration->GetSigma();

	double t(TheOption->GetExpiry());
	double delta(TheOption->GetDelta(stock_path[0], vol_path[0], t));
	double borrow(delta * stock_path[0] - OptionValue0);
	double PnL(0.0);
	double deltaT(T / ThePathGeneration->GetSteps());

	//simple interest calculation. no compounding
	double a(1.0 + r * deltaT);

	for (size_t i(1); i < stock_path.size() - 1; ++i){
		double delta_0(delta);
		t -= deltaT;
		delta = TheOption->GetDelta(stock_path[i], vol_path[i], t);
		double b((delta - delta_0) * stock_path[i]);
		PnL += delta_0 * stock_path[i] - borrow * a - TheOption->GetValue(stock_path[i], vol_path[i], t);
		borrow += b;
	}

	PnL += delta * stock_path[stock_path.size() - 1] - borrow * a;

	return PnL - TheOption->GetPayOff(stock_path[stock_path.size() - 1]);
}
