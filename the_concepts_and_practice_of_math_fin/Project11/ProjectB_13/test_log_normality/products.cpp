#include "products.h"
#include "dsct_factor.h"
#include <algorithm>

using namespace std;

BGMProducts::BGMProducts(const std::vector<double>& times_, double Strike_)
	:times(times_), Strike(Strike_), M(times_.size()-1)
{}

void BGMProducts::setStrike(double Strike_){ Strike = Strike_; }

Swaption::Swaption(const vector<double>& times_, double Strike_)
	: BGMProducts(times_, Strike_)
{}

vector<double> Swaption::GetUnderlyingTimes() const{ return times; }

vector<double> Swaption::GetEvolutionTimes() const {
	vector<double> _times(1);
	_times[0] = times[1];
	return _times;
}

bool Swaption::DoNextStep(const vector<double>& fwd_rtes, vector<CashFlow>& cf) {

	double swap_rte = swap_rate(fwd_rtes, times, 0, M-1);
	double annuity = annuity_swap(fwd_rtes, times, 0, M-1);
	
	CashFlow a;
	a.time = times[0];
	a.amount = 100.0 * max(swap_rte - Strike, 0.0) * annuity; //intrinsic value

	cf.push_back(a);
	
	return true;
}

TriggerSwap::TriggerSwap(const vector<double>& times_, double Strike_, double ref_rate_)
	:BGMProducts(times_, Strike_), ref_rate(ref_rate_)
{
	_i_ = 0;
}

vector<double> TriggerSwap::GetUnderlyingTimes() const{ return times; }

vector<double> TriggerSwap::GetEvolutionTimes() const{
	vector<double> _times;
	_times.assign(times.begin(), times.end() - 1);
	return _times;
}

void TriggerSwap::reset() {
	_i_ = 0;
}

void TriggerSwap::set_i(unsigned long a){
	_i_ = a;
}

bool TriggerSwap::DoNextStep(const vector<double>& fwd_rtes, vector<CashFlow>& cf)  {
	CashFlow a;
	double swap_rte = swap_rate(fwd_rtes, times, _i_, M-1);
	
	if (swap_rte >= ref_rate){ 
		a.time = times[_i_]; 
		a.amount = 0.0; 
		cf.push_back(a); 
		return false; 
	}
	
	if (!(_i_ < this->GetEvolutionTimes().size() - 1)){ 
		a.time = times[_i_]; 
		a.amount = 0.0; 
		cf.push_back(a); 
		return false; 
	}

	a.time = times[_i_];
	a.amount = (fwd_rtes[_i_] - Strike)*(times[_i_ + 1] - times[_i_]);
	cf.push_back(a);
	
	++_i_;

	return true;
}

Caplet::Caplet(const vector<double>& times_, double Strike_)
	: BGMProducts(times_, Strike_)
{}

vector<double> Caplet::GetUnderlyingTimes() const{	return times;}

vector<double> Caplet::GetEvolutionTimes() const {
	vector<double> _times(1);
	_times[0] = times[1];
	return _times;
}

bool Caplet::DoNextStep(const vector<double>& fwd_rtes, vector<CashFlow>& cf) {

	CashFlow a;
	a.time = times[0];
	a.amount = 100.0 * max(fwd_rtes[0] - Strike, 0.0) * (times[1] - times[0]); //intrinsic value
	cf.push_back(a);

	return true;
}