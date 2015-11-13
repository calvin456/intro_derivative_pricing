
//engine_ls.h

//use quantlib and boost for linear algebra

//http://quantlib.10058.n7.nabble.com/Multiple-linear-regression-weighted-regression-td5716.html

//ref. mc simul algo for the pricing of American options
//Peter BQ Lin , MSc dissertation, 2008

//code adapted from matlab code taken from ref. 


#ifndef ENGINE_LS_H
#define ENGINE_LS_H

#include <cmath>
#include <Vanilla3.h>
#include <Parameters.h>
#include <path_generation.h>

#include <ql/quantlib.hpp>

using namespace QuantLib;
using namespace std;

//func def
double weight_laguerre_poly(double x, int a);


//compute price w/o convergence table
template<typename T>
double mc_pricer_ls(const T& TheOption,
								const Parameters& r,
								unique_ptr<PathGeneration>&  ThePaths,
								unsigned long M,
								unsigned long N)
{
	//ref. 2.2.1 Longstaff-Schwartz algorithm
	//With the technique of estimating continuation values through regression discussed,
	//one can now present the Longstaff-Schwartz algorithm.

	double deltaT(TheOption.GetExpiry() / N);

	// Discount value for each time step:

	double Disc(exp(-r.Integral(0.0, deltaT)));

	//1. Start by simulating b independent sample paths Markov chain
	// Simulate M independent paths first, for regression.

	Matrix Spots(M, N + 1);

	MJArray Variates(N + 1);
	vector<MJArray> args(1);
	args[0] = Variates;

	for (size_t i(0); i < M; ++i){

		MJArray stock_path(N + 1);
		stock_path = ThePaths->GetOnePath(args);

		for (size_t j(0); j < N + 1; ++j)	Spots[i][j] = stock_path[j];

	}

	//2. At the final state, assign each Vmj
	//Discount all values to become time-0 units

	Matrix PayOff(M, N);

	for (size_t i(0); i < M; ++i){
		for (size_t j(0); j < N; ++j)
			PayOff[i][j] = std::pow(Disc, static_cast<double>(j + 1)) * TheOption.OptionPayOff(Spots[i][j + 1]);
	}

	std::vector<Real> Y(M);
	Y.assign(PayOff.column_begin(N - 1), PayOff.column_end(N - 1));

	std::vector<boost::function1<Real, Real> > v;
	v.push_back(std::bind(weighted_laguerre_poly, std::placeholders::_1, 0));
	v.push_back(std::bind(weighted_laguerre_poly, std::placeholders::_1, 1));
	v.push_back(std::bind(weighted_laguerre_poly, std::placeholders::_1, 2));
	v.push_back(std::bind(weighted_laguerre_poly, std::placeholders::_1, 3));
	//v.push_back(std::bind(weighted_laguerre_poly, std::placeholders::_1, 4));
	//v.push_back(std::bind(weighted_laguerre_poly, std::placeholders::_1, 5));
	//v.push_back(std::bind(weighted_laguerre_poly, std::placeholders::_1, 6));

	//3. Apply the following backward recursion

	// Working backwards to evaluate continuation values
	// and then Max(payoff, continuation).

	for (size_t i(N-1); i > 0; --i)
	{
		std::vector<Real> X(M);

		for (size_t j(0);j < M -1;++j)	X[j] = Spots[j+1][i];

		// L-S recommends taking only in-the-money nodes

		LinearRegression m(X, Y, v);

		// Estimated continuation values:
		// Comparing exercise values and continuation values
		// Longstaff-Schwartz method:

		for (size_t j(0); j < M; ++j){
			double RegVal(0.0);
			for (size_t k(0);k < 4;++k)	RegVal += m.coefficients()[k] * v[k](X[j]);

			double _Y(PayOff[j][i - 1]);

			if (_Y >= RegVal) Y[j] = _Y ;
		}
	}

	//4. Finally let V0 = (V11 + ... + V1b)/b

	return std::accumulate(Y.begin(), Y.end(), 0.0) / M;


}

//Laguerre polynomials
//ref. https://en.wikipedia.org/wiki/Laguerre_polynomials

double weighted_laguerre_poly(double x, int a){
//compute 1st six polynomials
	switch(a){
	case 0: {return exp(.5 * x); }
	case 1: {return exp(.5 * x) * (1.0 - x); }
	case 2: {return exp(.5 * x) * 1.0 / 2.0 * (std::pow(x,2.0) - 4.0 * x + 2.0); }
	case 3: {return exp(.5 * x) * 1.0 / 6.0 * (-std::pow(x, 3.0) + 9.0 * std::pow(x, 2.0) - 18.0 * x + 6.0); }
	case 4: {return exp(.5 * x) * 1.0 / 24.0 * (std::pow(x, 4.0) - 16.0 * std::pow(x, 3.0) + 72.0 * std::pow(x, 2.0) - 96.0 * x + 24.0); }
	case 5: {return exp(.5 * x) * 1.0 / 120.0 * (-std::pow(x, 5.0) + 25.0 * std::pow(x, 4.0) - 200.0 * std::pow(x, 3.0) + 600.0 * std::pow(x, 2.0) - 600.0 * x + 120.0); }
	case 6:  {return exp(.5 * x) * 1.0 / 720.0 * (std::pow(x, 6.0) - 36.0 * std::pow(x, 5.0) + 450.0 * std::pow(x, 4.0) - 2400.0 * std::pow(x, 3.0) + 5400.0 * std::pow(x, 2.0) - 4320.0 * x + 720.0); }
	default: {return 0.0; }

	}

}

#endif
