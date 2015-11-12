//engine.h

/*
Implement BGM engine
Full rank. No reduction using PCA

*/

#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <vector>
#include <Random2.h>
#include "products.h"
#include "fwd_vol_structure.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp >

using namespace boost::numeric::ublas;
using namespace std;
using namespace Product;

/*
The layout of this class mirrors exotic engine class of chap.7 in c++ design pattern
and derivatives pricing, 2nd ed, joshi
*/

typedef enum { EULER, PC } method; //PC: predictor-corrector

class TheEngine{
public:

	TheEngine(shared_ptr<BGMProducts>& the_product_,
				FwdVolStructure& term_structure,
				shared_ptr<RandomBase>& the_generator_,
				const std::vector<double>& fwd_rtes_, //fwd_rte time 0 Li(0), i = 0,1, ..., n
				const std::vector<double>& times_,
				double sub_stepping_,  // amount of substeps within steps delta_t/n
				unsigned int numeraire_, //numéraire eg t0 = 0 (spot)
				double initial_numeraire_); // initial value of numéraire

	virtual ~TheEngine(){}

	matrix<double> getCovariance() const;

	void setCovariance(const matrix<double>& cov);

	void setNumeraire(unsigned int numeraire_, double initial_numeraire_);

	void GetOnePath(std::vector<std::vector<double>>& fwd_rtes, MJArray& z, method m = EULER);

	double DoOnePath(const std::vector<std::vector<double>>& fwd_rtes);

	double DoSimulation(unsigned int number_paths, method m);

protected:
	std::vector<double> drifts(const std::vector<double>& times, const std::vector<double>& fwd_rtes, size_t p);

private:
	unsigned long M;
	
	shared_ptr<BGMProducts> the_product;
	matrix<double> cov; //covariance matrix

	shared_ptr<RandomBase> the_generator;

	std::vector<std::vector<double>> fwd_rtes; //m rates, n times. m x n mat 
	unsigned int numeraire;
	double initial_numeraire;
	double sub_stepping; //sub-amount of time within one step

	std::vector<double> mu; //drift
	matrix<double> A; //pseudo-square mat
	std::vector<double> times;

	std::vector<Product::CashFlow> cashflows; //cash flows stream from product
};

#endif