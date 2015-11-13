//OptionsToReplicate.cpp

#include "OptionsToReplicate.h"
//#include<options.h>
#include <map>

#include<iostream>

using namespace std;

OptionToReplicate::OptionToReplicate(double Strike,
	double Barrier,
	double r,
	double Vol,
	double Expiry,
	double d)
	:Strike(Strike), Barrier(Barrier), r(r), Vol(Vol), Expiry(Expiry), d(d)
{}

OptionToReplicate::OptionToReplicate(const OptionToReplicate& other)
	:Strike(other.Strike), Barrier(other.Barrier), r(other.r), Vol(other.Vol), Expiry(other.Expiry), d(other.d)
{}

DownAndOutCall::DownAndOutCall(double Strike,
	double Barrier,
	double r,
	double Vol,
	double Expiry,
	double d)
	: OptionToReplicate(Strike, Barrier, r, Vol, Expiry, d)
{}

void DownAndOutCall::GeneratePtf(unsigned long steps, shared_ptr<Option> OptionFinal){

	Portfolio.clear();

	double deltaT(Expiry / steps);
	double time_(Expiry);

	CallOption c0(Strike, Strike, r, d, Vol, Expiry);

	//PutOption p0(Barrier, Barrier, r, d, Vol, Expiry); //option (B,tj)
	//double ratio = -(c0.GetValue(Barrier, Vol, Expiry) / p0.GetValue(Barrier, Vol, Expiry)); // option ratio
	//Portfolio.insert(pair<double, PutOption>(ratio, p0));

	if (steps > 1){
		for (size_t i(1); i < steps; ++i){
			time_ -= deltaT;

			PutOption p(Barrier, Barrier, r, d, Vol, time_); //option (B,tj)
			double ratio = -((c0.GetValue(Barrier, Vol, time_) - OptionFinal->GetValue(Barrier, Vol, time_) * c0.GetValue(Barrier, Vol, Expiry)) /
				p.GetValue(Barrier, Vol, time_)); // option ratio
			Portfolio.insert(pair<double, PutOption>(ratio, p));
		}
	}
}

//shorten time steps as one come close to expiry

void DownAndOutCall::GeneratePtf1(unsigned long steps, shared_ptr<Option> OptionFinal){

	Portfolio.clear();

	double deltaT(Expiry / steps);
	double time_(Expiry);

	CallOption c0(Strike, Strike, r, d, Vol, Expiry);

	//PutOption p0(Barrier, Barrier, r, d, Vol, Expiry); //option (B,tj)
	//double ratio = -(c0.GetValue(Barrier, Vol, time_) / p0.GetValue(Barrier, Vol, Expiry)); // option ratio
	//Portfolio.insert(pair<double, PutOption>(ratio, p0));;

	if (steps > 1){
		for (size_t i(1); i < steps; ++i){
			time_ -= deltaT / i;

			for (size_t j(0); j < i; ++j){
				PutOption p(Barrier, Barrier, r, d, Vol, time_); //option (B,tj)
				double ratio = -((c0.GetValue(Barrier, Vol, time_) - OptionFinal->GetValue(Barrier, Vol, time_) * c0.GetValue(Barrier, Vol, Expiry)) /
					p.GetValue(Barrier, Vol, time_)); // option ratio
				Portfolio.insert(pair<double, PutOption>(ratio, p));
			}
		}
	}
}

//time-dep vol
void  DownAndOutCall::GeneratePtf(unsigned long steps, const vector<double>& Vol, shared_ptr<Option> OptionFinal){

	Portfolio.clear();

	double deltaT(Expiry / steps);
	double time_(Expiry);

	CallOption c0(Strike, Strike, r, d, Vol[0], Expiry);

	//PutOption p0(Barrier, Barrier, r, d, Vol[0], Expiry); //option (B,tj)
	//double ratio = -(c0.GetValue(Barrier, Vol[0], time_) / p0.GetValue(Barrier, Vol[0], Expiry)); // option ratio
	//Portfolio.insert(pair<double, PutOption>(ratio, p0));

	if (steps > 1){
		for (size_t i(1); i < steps; ++i){
			time_ -= deltaT;

			PutOption p(Barrier, Barrier, r, d, Vol[i], time_); //option (B,tj)
			double ratio = -((c0.GetValue(Barrier, Vol[i], time_) - OptionFinal->GetValue(Barrier, Vol[i], time_) * c0.GetValue(Barrier, Vol[0], Expiry)) /
				p.GetValue(Barrier, Vol[i], time_)); // option ratio
			Portfolio.insert(pair<double, PutOption>(ratio, p));
		}
	}
}

double DownAndOutCall::GetValue(double _Spot, double _t, shared_ptr<Option> OptionFinal) const {

	double sum(0.0); //cout << sum << " ";

	CallOption c0(Strike, Strike, r, d, Vol, Expiry);

	sum = c0.GetValue(_Spot, Vol, _t);

	sum -= OptionFinal->GetValue(_Spot, Vol, _t) * c0.GetValue(Barrier, Vol, Expiry);

	for (map<double, PutOption>::iterator itr = Portfolio.begin(); itr != Portfolio.end(); ++itr){
		sum += itr->second.GetValue(_Spot, Vol, _t) * itr->first;
	}
	return sum;
}


double DownAndOutCall::GetValue(double _Spot, const vector<double>& _Vol, double _t, shared_ptr<Option> OptionFinal) const{

	double sum(0.0); //cout << sum << " ";

	CallOption c0(Strike, Strike, r, d, _Vol[0], Expiry);

	sum = c0.GetValue(_Spot, Vol, _t);

	sum -= OptionFinal->GetValue(_Spot, Vol, _t) * c0.GetValue(Barrier, Vol, Expiry);

	size_t i(0);

	for (map<double, PutOption>::iterator itr = Portfolio.begin(); itr != Portfolio.end(); ++itr){
		sum += itr->second.GetValue(_Spot, _Vol[i], _t) * itr->first;
		++i;
	}
	return sum;
}

UpAndOutCall::UpAndOutCall(double Strike,
	double Barrier,
	double r,
	double Vol,
	double Expiry,
	double d)
	:OptionToReplicate(Strike, Barrier, r, Vol, Expiry, d)
{}

void UpAndOutCall::GeneratePtf(unsigned long steps, shared_ptr<Option> OptionFinal){

	Portfolio.clear();

	double deltaT(Expiry / steps);
	double time_(Expiry);

	CallOption c0(Strike, Strike, r, d, Vol, Expiry);
	Portfolio.insert(pair<double, CallOption>(1.0, c0));

	CallOption c1(Barrier, Barrier, r, d, Vol, Expiry);
	Portfolio.insert(pair<double, CallOption>(-1.0, c1));

	if (steps > 1){
		for (size_t i(1); i < steps; ++i){
			time_ -= deltaT;

			CallOption c(Barrier, Barrier, r, d, Vol, time_); //option (B,tj)
			double ratio = -((c0.GetValue(Barrier, Vol, time_) - c1.GetValue(Barrier, Vol, time_) - OptionFinal->GetValue(Barrier, Vol, time_) * (Barrier - Strike)) /
				c.GetValue(Barrier, Vol, time_)); // option ratio
			Portfolio.insert(pair<double, CallOption>(ratio, c));
		}
	}
}

//shorten time steps as one come close to expiry
void UpAndOutCall::GeneratePtf1(unsigned long steps, shared_ptr<Option> OptionFinal){

	Portfolio.clear();

	double deltaT(Expiry / steps);
	double time_(Expiry);

	CallOption c0(Strike, Strike, r, d, Vol, Expiry);
	Portfolio.insert(pair<double, CallOption>(1.0, c0));

	CallOption c1(Barrier, Barrier, r, d, Vol, Expiry);
	Portfolio.insert(pair<double, CallOption>(-1.0, c1));

	if (steps > 1){
		for (size_t i(1); i < steps; ++i){

			time_ -= deltaT / i;

			for (size_t j(0); j < i; ++j){
				CallOption c(Barrier, Barrier, r, d, Vol, time_); //option (B,tj)
				double ratio = -((c0.GetValue(Barrier, Vol, time_) - c1.GetValue(Barrier, Vol, time_) - OptionFinal->GetValue(Barrier, Vol, time_) * (Barrier - Strike)) /
					c.GetValue(Barrier, Vol, time_)); // option ratio
				Portfolio.insert(pair<double, CallOption>(ratio, c));
			}
		}
	}
}

//time-dep vol
void  UpAndOutCall::GeneratePtf(unsigned long steps, const vector<double>& Vol, shared_ptr<Option> OptionFinal){

	Portfolio.clear();

	double deltaT(Expiry / steps);
	double time_(Expiry);

	CallOption c0(Strike, Strike, r, d, Vol[0], Expiry);
	Portfolio.insert(pair<double, CallOption>(1.0, c0));

	CallOption c1(Barrier, Barrier, r, d, Vol[0], Expiry);
	Portfolio.insert(pair<double, CallOption>(-1.0, c1));

	if (steps > 1){
		for (size_t i(1); i < steps; ++i){

			time_ -= deltaT;

			CallOption c(Barrier, Barrier, r, d, Vol[i], time_); //option (B,tj)
			double ratio = -((c0.GetValue(Barrier, Vol[i], time_) - c1.GetValue(Barrier, Vol[i], time_) - OptionFinal->GetValue(Barrier, Vol[i], time_) * (Barrier - Strike)) /
				c.GetValue(Barrier, Vol[i], time_)); // option ratio
			Portfolio.insert(pair<double, CallOption>(ratio, c));
		}
	}
}

double UpAndOutCall::GetValue(double _Spot, double _t, shared_ptr<Option> OptionFinal) const{

	double sum(0.0);

	sum -= OptionFinal->GetValue(_Spot, Vol, _t) * (Barrier - Strike); //cout << sum << " ";

	for (map<double, CallOption>::iterator itr = Portfolio.begin(); itr != Portfolio.end(); ++itr){
		sum += itr->second.GetValue(_Spot, Vol, _t) * itr->first; //cout << sum << " ";
	}
	return sum;
}

double UpAndOutCall::GetValue(double _Spot, const vector<double>& _Vol, double _t, shared_ptr<Option> OptionFinal) const{

	double sum(0.0);

	sum -= OptionFinal->GetValue(_Spot, _Vol[0], _t) * (Barrier - Strike);

	size_t i(0);

	for (map<double, CallOption>::iterator itr = Portfolio.begin(); itr != Portfolio.end(); ++itr){
		sum += itr->second.GetValue(_Spot, _Vol[i], _t) * itr->first;
		++i;
	}
	return sum;
}
