//hedging_strategy.cpp

#include <algorithm>
#include <hedging_strategy.h>

using namespace std;

//price of option sold to client. Sold w/ premium over fair value
template<typename U>
HedgingStrategy<U>::HedgingStrategy(double OptionValue0_, double r_, shared_ptr<U> TheOption_,
									double T_)
	:OptionValue0(OptionValue0_), r(r_), TheOption(TheOption_), T(T_)
{}

template<typename U>
DeltaHedging<U>::DeltaHedging(double OptionValue0, double r, shared_ptr<U> TheOption,
							  PathGenerationGBM* ThePathGeneration,
							  double T)
	: HedgingStrategy(OptionValue0, r, TheOption,  T), ThePathGeneration(ThePathGeneration)
{}



template<typename U>
double DeltaHedging<U>::DoOnePath(args& args_) {

	MJArray stock_path = ThePathGeneration->GetWholePath(args_);

	double vol(TheOption->GetVol());
	double t(TheOption->GetExpiry());
	double delta(TheOption->GetDelta(stock_path[0], vol, t));
	double borrow(delta * stock_path[0] - OptionValue0);
	double PnL(0.0);
	double deltaT(T / ThePathGeneration->GetSteps());

	//simple interest calculation. no compounding
	double a(1.0 + r * deltaT);

	for (size_t i(1); i < stock_path.size() -1; ++i){
		double delta_0(delta);
		t -= deltaT;
		delta = TheOption->GetDelta(stock_path[i], vol, t);
		double b((delta - delta_0) * stock_path[i]);
		PnL += delta_0 * stock_path[i] - borrow * a - TheOption->GetValue(stock_path[i], vol, t);
		borrow += b;
	}

	PnL += delta * stock_path[stock_path.size() - 1]  - borrow * a;
	PnL -= TheOption->GetPayOff(stock_path[stock_path.size() - 1]);

	return PnL;
}

//----------------------------------------------------------------------------------------------

template<typename U>
SnLHedging<U>::SnLHedging(double OptionValue0, double r, shared_ptr<U> TheOption,
						  PathGenerationGBM* ThePathGeneration,
						  double T)
	:HedgingStrategy(OptionValue0, r, TheOption,  T), ThePathGeneration(ThePathGeneration)
{}

template<typename U>
double SnLHedging<U>::DoOnePath(args& args_) {

	MJArray stock_path = ThePathGeneration->GetWholePath(args_);

	double vol(TheOption->GetVol());
	double t(TheOption->GetExpiry());
	long I(TheOption->IsTouched(stock_path[0]));

	double borrow(0.0);
	if (I == 1)	borrow = stock_path[0] - OptionValue0;

	double PnL(0.0);
	if (I == 0)	PnL = OptionValue0;

	double deltaT(T / ThePathGeneration->GetSteps());

	//simple interest calculation. no compounding
	double a(1.0 + r * deltaT);

	for (size_t i(1); i <stock_path.size()-1; ++i){
	
		t -= deltaT;
		I = TheOption->IsTouched(stock_path[i]);
		PnL += I * (stock_path[i] - borrow * a) - TheOption->GetValue(stock_path[i], vol, t);

		if (I == 0)	borrow = 0.0;
		else	if (borrow == 0.0)	borrow = stock_path[i];
	}

	PnL += I * (stock_path[stock_path.size() - 1] - borrow * a);

	return PnL - TheOption->GetPayOff(stock_path[stock_path.size() - 1]);
}

template<typename U, typename V>
GammaHedging<U,V>::GammaHedging(double OptionValue0, double r,
								shared_ptr<U> TheOption, shared_ptr<V> TheOption1,
								PathGenerationGBM* ThePathGeneration,
								double T)
	:HedgingStrategy(OptionValue0, r, TheOption,  T), ThePathGeneration(ThePathGeneration), TheOption1(TheOption1)
{}

template<typename U, typename V>
double GammaHedging<U, V>::DoOnePath(args& args_) {

	MJArray stock_path = ThePathGeneration->GetWholePath(args_);

	double vol(TheOption->GetVol());
	double t(TheOption->GetExpiry());

	double gamma(-TheOption->GetGamma(stock_path[0], vol, t)
								/ TheOption1->GetGamma(stock_path[0], vol, t)); //gamma ptf

	double delta(TheOption->GetDelta(stock_path[0], vol, t)
								+ gamma * TheOption1->GetDelta(stock_path[0], vol, t)); //delta ptf

	double borrow(delta* stock_path[0] + gamma * TheOption1->GetValue(stock_path[0], vol, t) - OptionValue0);

	double PnL(0.0);
	double deltaT(T / ThePathGeneration->GetSteps());

	//simple interest calculation. no compounding
	double a(1.0 + r * deltaT);

	for (size_t i(1); i < stock_path.size() - 1; ++i){

		t -= deltaT;

		double gamma_0(gamma);

		gamma = -TheOption->GetGamma(stock_path[i], vol, t)
							/ TheOption1->GetGamma(stock_path[i], vol, t);

		double b((gamma - gamma_0) *TheOption1->GetValue(stock_path[i], vol, t));
		double delta_0(delta);

		delta = TheOption->GetDelta(stock_path[i], vol, t)
							+ gamma * TheOption1->GetDelta(stock_path[i], vol, t);

		double c((delta - delta_0) * stock_path[i]);

		PnL += delta_0 * stock_path[i] + gamma_0 * TheOption1->GetValue(stock_path[i], vol, t) - borrow * a
						- TheOption->GetValue(stock_path[i], vol, t);

		borrow += b + c;
	}

	PnL += delta * stock_path[stock_path.size() - 1] + gamma * TheOption1->GetPayOff(stock_path[stock_path.size() - 1]) - borrow * a;

	return PnL - TheOption->GetPayOff(stock_path[stock_path.size() - 1]);
}
