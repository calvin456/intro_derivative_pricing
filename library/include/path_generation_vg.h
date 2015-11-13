//path_generation_vg.h

#ifndef PATH_GEN_VG_H
#define PATH_GEN_VG_H

#include <path_generation.h>
#include <Parameters.h>

//VG process
class PathGenerationVG : public PathGeneration
{
	//Merton. GBM + compound process with log Y ~ N(a,b)
	//J ~ m * exp(-.5 * nu * nu + nu * Z)
public:
		PathGenerationVG(shared_ptr<RandomBase>& TheGenerator_,
											double Spot0_,
											double T_,
											const Parameters& drift_,
											const Parameters& vol_,
											double nu_,
											double theta_,
											unsigned long steps_);

		virtual ~PathGenerationVG(){}

		virtual double GetOnePath(args& args_) const;
		virtual MJArray GetWholePath(args& args_) ;

		MJArray GetOnePathBB(args& args_) ;

private:
		Parameters drift;
		Parameters vol;
		double nu;
		double theta;
		double omega;

};

#endif
