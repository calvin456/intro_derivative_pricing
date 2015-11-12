//fwd_vol_structure.cpp

#include "fwd_vol_structure.h"
#include <cmath>



FwdVolStructure::FwdVolStructure(double beta_)
	:beta(beta_)
{}

void FwdVolStructure::setBeta(double beta_){ beta = beta_;}

double FwdVolStructure::correlation(double ti, double tj) const {
	return exp(-beta*fabs(ti - tj));
}

FwdVolStructure1::FwdVolStructure1(double a_, double b_, double c_, double d_, double beta_)
	:a(a_), b(b_), c(c_), d(d_), FwdVolStructure(beta_)
{}

void FwdVolStructure1::bumpVol(double param) { d += param;}

double FwdVolStructure1::volatility(double tj, double t) const {
//assume vol term structure starts at time t
	return (a + b * tj) * exp(-c * (tj-t)) + d;
}

matrix<double> FwdVolStructure1::integral(const std::vector<double>& time, double t) const {
	//formulas comes from Jaeckel + Rebonato,  the link btn caplet and swaption vol in a bgm/j framework, 2000	
	//available at http://www.risk.net/digital_assets/4445/v6n4a3.pdf	

	//compute integral from 0 to t. 
	matrix<double> I_t(time.size(), time.size());
		
	for (size_t i(0); i < time.size(); ++i)
		for (size_t j(0); j <time.size(); ++j){

			double tau_i(t - time[i]), tau_j(t - time[j]); 

			I_t(i,j) = (a * d) / c *(exp(c * tau_i) + exp(c * tau_j)) + d * d * t
				- (b * d) / (c* c) * (exp(c * tau_i) * (c * tau_i - 1.0) + exp(c * tau_j)*(c * tau_j - 1.0))
					+ exp(c * (tau_i + tau_j)) / (4.0* c * c * c)
						* (2.0 * a * a* c * c + 2.0 * a* b* c * (1.0 - c * (tau_i + tau_j))
							+ b * b * (1.0 + 2.0 * c * c * tau_i  * tau_j - c*  (tau_i + tau_j)));
		}
	
	return I_t;
}

void FwdVolStructure1::covariance(matrix<double>& cov_matrix,
									const std::vector<double>& K,
									const std::vector<double>& time,
									double t, double T) const {
//compute covariance matrix from time t up to T
//K scaling factor. Should be close to 1 if model well calibrated

//taken from Changwei Xiong, interest rate models, 2013. 
//available at http://www.cs.utah.edu/~cxiong/

	matrix<double> I_t = this->integral(time, t);
	matrix<double> I_T = this->integral(time, T);

	//the accumulated coveriance from time t up to time T
	for (size_t i(0); i < cov_matrix.size1(); ++i)
		for (size_t j(0); j < cov_matrix.size2(); ++j)
			cov_matrix(i,j) = this->correlation(time[i], time[j]) * K[i] * K[j] * (I_T(i,j) - I_t(i,j));
}


FwdVolStructureFlat::FwdVolStructureFlat(double vol_, double beta_)
	:vol(vol_), vol2(vol_ * vol_), FwdVolStructure(beta_)
{}

void FwdVolStructureFlat::bumpVol(double param) { 
	vol += param; 
	vol2 = vol * vol;
}

double FwdVolStructureFlat::volatility(double tj, double t) const {
	//constant vol struct up to time t
	return vol;
}

void FwdVolStructureFlat::covariance(matrix<double>& cov_matrix,
										const std::vector<double>& K,
										const std::vector<double>& time,
										double t, double T) const {
	
	//the accumulated coveriance from time t up to time T
	for (size_t i(0); i < cov_matrix.size1(); ++i)
		for (size_t j(0); j < cov_matrix.size2(); ++j)
			cov_matrix(i, j) = this->correlation(time[i], time[j]) * K[i] * K[j] * vol2;
		
}

