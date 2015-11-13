//path_generation_gbm.h

#ifndef PATH_GEN_GBM_H
#define PATH_GEN_GBM_H

#include <path_generation.h>
#include <Parameters.h>

//Geometric Brownian motion
class PathGenerationGBM : public PathGeneration
{
public:
		PathGenerationGBM(shared_ptr<RandomBase> TheGenerator_,
						  double Spot0_,
						  double T_,
						  const Parameters& drift_,
						  const Parameters& vol_,
						  unsigned long steps_ = 1);
		
		virtual ~PathGenerationGBM(){}
		double GetOnePath(args& args_) const;
		MJArray GetWholePath(args& args_);

		virtual Parameters GetDrift() const { return drift; }
		virtual Parameters GetVol() const { return vol; }

		void SetSteps(unsigned long steps_);
		void SetDrift(const Parameters& drift_);
		void SetVol(const Parameters& vol_);
private:
		mutable Parameters drift;
		mutable Parameters vol;
		double deltaT;
		double _drift;
		double _vol_sqrt;
};

class PathEulerStepping : public PathGeneration
{
public:
	PathEulerStepping(shared_ptr<RandomBase> TheGenerator_,
					  double Spot0_,
					  double T_,
					  const Parameters& drift_,
					  const Parameters& vol_,
					  unsigned long steps_);
		virtual ~PathEulerStepping(){}
		double GetOnePath(args& args_) const;
		MJArray GetWholePath(args& args_);
private:
		Parameters drift;
		Parameters vol;
		double deltaT;
		double _drift;
		double _vol_sqrt;
};

#endif
