//path_generation_jdp.h
//Jump diffussion process

//the stock price follows a jump-diffusion SDE

//dSt = a(S,t) * dt + b(S,t) * dWt  + c(S,t) * dJt , 0<= t <= T_

//J = compound Poisson process sum from 1 to N(t) over [Yi -1]

//ref. Multilevel MC method for jump-diffusion SDEs, Yuan Xiam, 2011,
//Oxford-Man Institute of Quantitative Finance and Mathematical Institute

#ifndef PATH_GEN_JDP_H
#define PATH_GEN_JDP_H

#include"path_generation.h"
#include <Parameters.h>

class PathGenerationJDP : public PathGeneration
{
	//Merton. GBM + compound process with log Y ~ N(0,nu)
	//J ~ m * exp(-.5 * nu * nu + nu * Z), m acts as a scaling factor
public:
		PathGenerationJDP(shared_ptr<RandomBase> TheGenerator_,
												double Spot0_,
												double T_,
												const Parameters& drift_,
												const Parameters& vol_,
												double kappa_,
												double m_,
												double nu_,
												unsigned long steps_);
		 virtual ~PathGenerationJDP(){}
		 virtual double GetOnePath(args& args_) const;
		 virtual MJArray GetWholePath(args& args_);

private:
		Parameters drift;
		Parameters vol;
		double kappa;
		double m;
		double nu;
};

#endif
