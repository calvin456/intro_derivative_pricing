//dsct_factor.h

#ifndef DSCT_FACTOR_H
#define DSCT_FACTOR_H

#include<vector>
using namespace std;

double dsct_factor(const std::vector<double>& fwd_rtes, 
					const std::vector<double>& times, 
					size_t a, 
					size_t i);
					//a start date, i time i

double annuity_swap(const std::vector<double>& fwd_rtes, 
					const std::vector<double>& times, 
					size_t a, 
					size_t b);
					//a start date, b end date

double swap_rate(const std::vector<double>& fwd_rtes, 
				const std::vector<double>& times, 
				size_t a, 
				size_t b);
				//a start date, b end date

#endif
