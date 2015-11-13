//path_generation_heston.h

#ifndef PATH_GEN_HESTON_H
#define PATH_GEN_HESTON_H

#include <path_generation.h>
#include <Parameters.h>

#include <ql/quantlib.hpp>

//stochastic volatility model. Implement Heston model

class PathGenerationHeston : public PathGeneration
{
public:
	PathGenerationHeston(shared_ptr<RandomBase> TheGenerator_,
						 double Spot0_,
						 double T_,
						 const Parameters& drift_,
						 const Parameters& vol_,
						 unsigned long steps_,
						 double correl_,
						 double kappa_,
						 double epsilon_ = 1.0);


	PathGenerationHeston(shared_ptr<RandomBase> TheGenerator_,
						 double Spot0_,
						 double T_,
						 const Parameters& drift_,
						 const Parameters& vol_,
						 unsigned long steps_, //steps stock path
						 unsigned long steps1_,  //steps volatility process
						 double correl_,
						 double kappa_,
						 double epsilon_ = 1.0);

	virtual ~PathGenerationHeston(){}

	virtual double GetOnePath(args& args_) const;
	virtual MJArray GetWholePath(args& args_);

	double rms_sigma(size_t  s, size_t t) const;
	MJArray GetSigma() const {return vol_path;}

	MJArray GetWholePathInstant(args& args_);

	//----project13 ---------------------------------
	double GetOnePathLS(args& args_); //Long stepping, short stepping
	double GetOnePathVol(args& args_);
	//-----------------------------------------------
private:
	double lambda;
	Parameters drift;
	Parameters vol;
	double correl;
	double kappa;
	double epsilon;
	unsigned long steps1;
	MJArray vol_path;
};

#endif
