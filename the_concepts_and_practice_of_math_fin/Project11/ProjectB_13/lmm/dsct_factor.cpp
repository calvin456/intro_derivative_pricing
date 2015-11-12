//dsct_factor.cpp

#include"dsct_factor.h"

using namespace std;

//decompose into fwd rates

//disct factor

double dsct_factor(const vector<double>& fwd_rtes, const vector<double>& times, size_t a, size_t i) {
//a start date, i time i

	vector<double> tau(times.size() - 1);
	for (size_t j(0); j < times.size() - 1; ++j)
		tau[j] = times[j+1] - times[j];

	double tmp(1.0);
	for (size_t j(a); j <= i; ++j)
		tmp *= 1.0 / (1.0 + tau[j] * fwd_rtes[j]);

	return tmp;
}

double annuity_swap(const vector<double>& fwd_rtes, const vector<double>& times, size_t a, size_t b) {

	vector<double> tau(times.size() - 1);
	for (size_t i(0); i < times.size() - 1; ++i)
		tau[i] = times[i + 1] - times[i];

	double tmp(0.0);
	for (size_t j(a); j <= b; ++j)
		tmp += tau[j] * dsct_factor(fwd_rtes,times, a, j);

	return tmp;
}

double swap_rate(const vector<double>& fwd_rtes, const vector<double>& times, size_t a, size_t b) {

	return (1.0 - dsct_factor(fwd_rtes, times, a, b)) / annuity_swap(fwd_rtes, times, a, b);

}
