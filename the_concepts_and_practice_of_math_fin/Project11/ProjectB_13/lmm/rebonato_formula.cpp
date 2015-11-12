//rebonato_formula.cpp

#include "rebonato_formula.h"
#include "dsct_factor.h"


//The approx formula
//Using Rebonato's formula to approx vol and plug it into Black formula to approx swaption price.

//Rebonato's formula for vol

double rebonato_formula(double swap_rte,
						size_t a,
						size_t b,
						std::vector<double>fwd_rates,
						std::vector<double> times,
						matrix<double>& cov){
						//a swap start time, b swap end time	

	//taken from Chang Wei Xiong, interest rate models, 2013. 
	//available at http://www.cs.utah.edu/~cxiong/

	std::vector<double> tau(times.size() - 1);
	for (size_t i(0); i < times.size() - 1; ++i)	tau[i] = times[i + 1] - times[i];
	
	double annuity(annuity_swap(fwd_rates, times, a, b));
	
	std::vector<double> omega(fwd_rates.size());
	for (size_t i(0); i < fwd_rates.size(); ++i)
		omega[i] = tau[i] * dsct_factor(fwd_rates, times, a, i) / annuity;
	
	double sum(0.0);
	for (size_t i(a); i <= b; ++i)
		for (size_t j(a); j <= b; ++j)
			sum += omega[i] * omega[j] * fwd_rates[i] * fwd_rates[j] * cov(i,j);
		
	return sum / (swap_rte*swap_rte);

}