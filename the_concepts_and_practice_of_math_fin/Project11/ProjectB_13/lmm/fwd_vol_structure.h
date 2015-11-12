//fwd_vol_structure.h
#ifndef FWD_VOL_STRUCTURE_H
#define FWD_VOL_STRUCTURE_H

#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp >

using namespace boost::numeric::ublas;
using namespace std;

//abstract base class
class FwdVolStructure{
public:
	FwdVolStructure(double beta_ = 0.1);
	virtual ~FwdVolStructure(){}
	virtual void setBeta(double beta_);
	virtual void bumpVol(double param)  = 0;
	virtual double volatility(double tj,double t) const = 0;
	virtual double correlation(double ti, double tj) const;
	virtual void covariance(matrix<double>& cov_matrix,
							const std::vector<double>& K,
							const std::vector<double>& time,
							double t, double T) const = 0;
protected:
	double beta;
};

class FwdVolStructure1 :public FwdVolStructure{
	//param volatility term structure
public:
	FwdVolStructure1(double a_, double b_, double c_, double d_, double beta_);
	virtual ~FwdVolStructure1(){}
	virtual void bumpVol(double param);
	virtual double volatility(double tj, double t) const;
	virtual void covariance(matrix<double>& cov_matrix,
							const std::vector<double>& K,
							const std::vector<double>& time,
							double t, double T) const;

protected:
	std::vector<std::vector<double>> integral(const std::vector<double>& time, double t) const;
private:
	double a;
	double b;
	double c;
	double d;
	
};

class FwdVolStructureFlat :public FwdVolStructure{
	//flat volatility term structure. i.e. straight line
public:
	FwdVolStructureFlat(double vol_, double beta_);
	virtual ~FwdVolStructureFlat(){}
	virtual void bumpVol(double param);
	virtual double volatility(double tj, double t) const;
	virtual void covariance(matrix<double>& cov_matrix,
							const std::vector<double>& K,
							const std::vector<double>& time,
							double t, double T) const;
private:
	double  vol; //const vol
	
};

#endif