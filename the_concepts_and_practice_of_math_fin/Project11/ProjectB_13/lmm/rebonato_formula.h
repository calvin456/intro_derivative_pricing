//rebonato_formula.h

#ifndef REBONATO_FORMULA_H
#define REBONATO_FORMULA_H

#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp >

using namespace boost::numeric::ublas;
using namespace std;

double rebonato_formula(double swap_rte, 
						size_t a, 
						size_t b,
						std::vector<double>fwd_rates, 
						std::vector<double> times, 
						matrix<double>& cov);

#endif