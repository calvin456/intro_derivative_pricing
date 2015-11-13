//interest_derivatives_analytical.cpp

#include<cmath>
#include<iterator>
#include<algorithm>
#include <normals.h>
#include "interest_derivatives_analytical.h"

using namespace std;

double p_t(double rate, double tenor){ return 1.0 / (1.0 + rate*tenor); }

double annuity_swap(const vector<vector<double>>& zcps, size_t start, size_t end) {
//compute annuity of swap

	//compute tau
	vector<double> tau(zcps.size() - 1);
	for (size_t i(0); i < zcps.size() - 1; ++i){
		tau[i] = zcps[i + 1][0] - zcps[i][0];
	}

	double annuity(0.0);

	for (size_t i(start); i < end; ++i)
		annuity += tau[i] * zcps[i+1][1];

	return annuity;
}

//swap-rate formulas
double swap_rate(const vector<vector<double>>& zcps, double tenor) {
	//dynamic array i = times, j = values discount factors
	//compute swap rate	co-terminal

	size_t i(0);
	for (size_t j(0); j < zcps.size(); ++j){
		if (zcps[j][0] == tenor) {
			i = j;
			break;
		}
	}

	return (zcps[i][1] - zcps[zcps.size() - 1][1]) / annuity_swap(zcps, i, zcps.size()-1);
}

double swap_rate_co_initial(const vector<vector<double>>& zcps, double tenor) {

	size_t i(0);
	for (size_t j(0); j < zcps.size(); ++j){
		if (zcps[j][0] == tenor){
			i = j;
			break;
		}
	}

	//compute tau
	vector<double> tau(zcps.size() - 1);
	for (size_t i(0); i < zcps.size() - 1; ++i){
		tau[i] = zcps[i + 1][0] - zcps[i][0];
	}

	double annuity(0.0);

	for (size_t j(1); j <= i; ++j)
		annuity += tau[j-1] * zcps[j][1];

	return (1.0 - zcps[i][1]) / annuity;
}

//discount from swap-rates bootstraping?

//do the same for co-initial rate. i.e.  w/equal start date and variable end date
void discount_from_swap_rate_co_initial(const vector<vector<double>> & swap_rates, vector<vector<double>>& dsct_factors) {

	//compute tau
	vector<double> tau(swap_rates.size() - 1);
	for (size_t i(0); i < swap_rates.size()-1; ++i){
		tau[i] = swap_rates[i + 1][0] - swap_rates[i][0];
	}

	dsct_factors[0][0] = swap_rates[0][0];
	dsct_factors[0][1] = 1.0;

	dsct_factors[1][0] = swap_rates[1][0];
	dsct_factors[1][1] = 1.0 / (1.0 + swap_rates[1][1]*tau[0]);

	double tmp(0.0);

	for (size_t i(2); i< swap_rates.size(); ++i){
		dsct_factors[i][0] = swap_rates[i][0];

		for (size_t j(1); j < i; ++j){
			tmp += tau[j - 1] * dsct_factors[j][1];
		}
		dsct_factors[i][1] = (1.0 - swap_rates[i][1] * tmp) / (1.0 + swap_rates[i][1] * tau[i-1]);
		tmp = 0.0;
	}
}

//co-terminal swap rate, i.e. All fwd swap rate shares the same terminal date
void discount_from_swap_rate_co_terminal(const vector<vector<double>>& swap_rates, vector<vector<double>>& dsct_factors) {
//ex 13.6 compute ratios of dsct factors to the value of final dsct factors

	//compute tau
	vector<double> tau(swap_rates.size() - 1);
	for (size_t i(0); i < swap_rates.size() - 1; ++i){
		tau[i] = swap_rates[i + 1][0] - swap_rates[i][0];
	}

	size_t n_1(swap_rates.size() - 2);

	//compute ratios
	vector<double> ratios(swap_rates.size() - 1);
	ratios[n_1] = swap_rates[n_1][1] * tau[n_1] + 1.0;

	double tmp(0.0);

	for (size_t i(swap_rates.size() - 3); i !=-1 ; --i){

		for (size_t j(n_1); j != i; --j){
			tmp += tau[j] * ratios[j];
		}
		tmp *= swap_rates[i][1];

		ratios[i] = swap_rates[i][1] * tau[n_1] + 1.0 + tmp;
		tmp = 0.0;
	}

	//compute dsct ratios
	size_t n(swap_rates.size() - 1);

	dsct_factors[n][0] = swap_rates[n][0];
	dsct_factors[n][1] = 1/ratios[0];

	for (size_t i(dsct_factors.size() - 2); i > 0; --i){
		dsct_factors[i][0] = swap_rates[i][0];
		dsct_factors[i][1] = dsct_factors[n][1] * ratios[i];
	}

	dsct_factors[0][0] = swap_rates[0][0];
	dsct_factors[0][1] = 1.0;
}

//Black formulas - European options analytical formulas
//caplet call option on libor rate
double black_formula_caplet(double annuity, double fwd_libor, double t1, double t2, double strike, double vol){

	double d1((log(fwd_libor / strike) + vol*vol*t1*.5) / (vol*sqrt(t1)));

	double d2(d1 - vol*sqrt(t1));

	return 10.0 * (t2 - t1)*annuity*(fwd_libor*CumulativeNormal(d1) - strike*CumulativeNormal(d2));

	//return p_t(fwd_libor, t2)*(t2 - t1)*(fwd_libor*CumulativeNormal(d1) - strike*CumulativeNormal(d2));
}

//floorlet put option on libor rate
double black_formula_floorlet(double annuity, double fwd_libor, double t1, double t2, double strike, double vol){

	double d1((log(fwd_libor / strike) + vol*vol*t1*.5) / (vol*sqrt(t1)));
	double d2(d1 - vol*sqrt(t1));

	return 10.0 * (t2 - t1)*annuity*(strike*CumulativeNormal(-d2) - fwd_libor*CumulativeNormal(-d1));
}

//payer swaption - call option on option on swap contract. Pays swap rate
double black_formula_payer_swaption(double annuity, double swap_rate, double strike, double vol, double expiry){

	double d1((log(swap_rate / strike) + (vol*vol)*expiry*.5) / (vol*sqrt(expiry)));
	double d2(d1 - vol*sqrt(expiry));

	return 10.0 * annuity*(swap_rate*CumulativeNormal(d1) - strike*CumulativeNormal(d2));
}

//receiver swaption - put option on option on swap contract. Receive swap rate
double black_formula_rec_swaption(double annuity, double swap_rate, double strike, double vol, double expiry){

	double d1((log(swap_rate / strike) + (vol*vol)*expiry*.5) / (vol*sqrt(expiry)));
	double d2(d1 - vol*sqrt(expiry));

	return 10.0 * annuity*(strike*CumulativeNormal(-d2) - swap_rate*CumulativeNormal(-d1));
}

//compute vega for payer swaption
double black_swaption_vega(double annuity, double swap_rate, double strike, double vol, double expiry){

	double d1((log(swap_rate / strike) + (vol*vol)*expiry*.5) / (vol*sqrt(expiry)));
	double d2(d1 - vol*sqrt(expiry));

	return 10.0 * annuity * swap_rate * sqrt(expiry) * NormalDensity(d1) ;
	
}