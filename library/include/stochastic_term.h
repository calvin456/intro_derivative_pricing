//stochastic_term.h

#include <Arrays.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp >

using namespace boost::numeric::ublas;

inline double StochasticTerm(const matrix<double>& A, size_t k, const MJArray& VariateArray);

inline MJArray StochasticTerm(const matrix<double>& A, const MJArray& VariateArray);

double StochasticTerm(const matrix<double>& A, size_t k, const MJArray& VariateArray){
// generate z normal correlated vars

	double tmp(0.0);

	for (size_t i(0); i <= k; ++i)
		tmp += A(k, i) * VariateArray[i];

	return tmp;
}

MJArray StochasticTerm(const matrix<double>& A, const MJArray& VariateArray){
// generate z normal correlated vars

	MJArray tmp(VariateArray.size());

	for (size_t i(0); i < A.size1(); ++i)
		for (size_t j(0); j < A.size2(); ++j)
			tmp[i] = A(j, i) * VariateArray[j];

	return tmp;
}
