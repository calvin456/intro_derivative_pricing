//path_generation_gbm_sv.h


//GBM process with stochastic volatility

/*

- Fit a BSM model w/ time-dependent vol so that it gives the sme implied vol
to ATM call options at the monthly reset times

- Reprice the Asian option w/this model

- Do a discrete barrier call option

- Compare w/ BSM prices obtained by calibrating ATM and at-the-barrier prices

*/

#ifndef PATH_GEN_GBM_SV_H
#define PATH_GEN_GBM_SV_H

#include <path_generation.h>
#include <Parameters.h>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

using namespace boost::numeric::ublas;

class PathGenerationGBM_SV : public PathGeneration
{
public:
		PathGenerationGBM_SV(shared_ptr<RandomBase>& TheGenerator_,
													double Spot0_,
													double T_,
													const Parameters& drift_,
													matrix<double> vol_, // t, vol , t = 1, 2, ..., 12
													unsigned long steps_);

		 virtual ~PathGenerationGBM_SV(){}
		 virtual double GetOnePath(args& args_) const;
		 virtual MJArray GetWholePath(args& args_);

private:
		 Parameters drift;
		 matrix<double> vol;
};

#endif
