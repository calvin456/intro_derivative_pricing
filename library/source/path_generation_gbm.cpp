//path_generation_gbm.cpp

#include <path_generation_gbm.h>


PathGenerationGBM::PathGenerationGBM(shared_ptr<RandomBase> TheGenerator_,
									 double Spot0_,
									 double T_,
									 const Parameters& drift_,
									 const Parameters& vol_,
									 unsigned long steps_)
	: PathGeneration(TheGenerator_, Spot0_, T_, steps_), drift(drift_), vol(vol_)
{
	TheGenerator->ResetDimensionality(steps);
	deltaT = T / steps;
	_drift = drift.Integral(0, deltaT) - .5 * vol.IntegralSquare(0, deltaT);
	_vol_sqrt = sqrt(vol.IntegralSquare(0, deltaT));
}

void PathGenerationGBM::SetSteps(unsigned long steps_){
	steps = steps_;
	TheGenerator->ResetDimensionality(steps);
	deltaT = T / steps;
	_drift = drift.Integral(0, deltaT) - .5 * vol.IntegralSquare(0, deltaT);
	_vol_sqrt = sqrt(vol.IntegralSquare(0, deltaT));
}

void PathGenerationGBM::SetDrift(const Parameters& drift_){ drift = drift_; }
void PathGenerationGBM::SetVol(const Parameters& vol_){ vol = vol_; }

double PathGenerationGBM::GetOnePath(args& args_) const {

	TheGenerator->GetGaussians(args_[0]);

	double log_stock_spot = log(Spot0);

	for (size_t i(0); i < steps; ++i)
		log_stock_spot += _drift + _vol_sqrt * args_[0][i];

	return exp(log_stock_spot);
}

MJArray PathGenerationGBM::GetWholePath(args& args_)  {

	MJArray stock_path(steps+1);

	TheGenerator->GetGaussians(args_[0]);

	stock_path[0] = Spot0;

	for (size_t i(0); i < stock_path.size() - 1; ++i)
		stock_path[i + 1] = stock_path[i] * exp(_drift + _vol_sqrt * args_[0][i]);
	
	return stock_path;
}

//Stepping methods
//One further thing to implement is an alternative Path bsd on Euler stepping

PathEulerStepping::PathEulerStepping(shared_ptr<RandomBase> TheGenerator_,
									 double Spot0_,
									 double T_,
									 const Parameters& drift_,
									 const Parameters& vol_,
									 unsigned long steps_)
 : PathGeneration(TheGenerator_, Spot0_, T_, steps_), drift(drift_), vol(vol_)
{
	TheGenerator->ResetDimensionality(steps);
	deltaT = T / steps;
	_drift = 1.0 + drift.Integral(0, deltaT);
	_vol_sqrt = sqrt(vol.IntegralSquare(0, deltaT));

}

double PathEulerStepping::GetOnePath(args& args_) const{

	TheGenerator->GetGaussians(args_[0]);

	double stock_spot = Spot0;

	for (size_t i(0); i < steps; ++i)
		stock_spot *= (_drift + _vol_sqrt * args_[0][i]);
	
	return stock_spot;

}

MJArray PathEulerStepping::GetWholePath(args& args_) {

	MJArray stock_path(steps + 1);

	TheGenerator->GetGaussians(args_[0]);

	stock_path[0] = Spot0;

	for (size_t i(0); i < stock_path.size() - 1; ++i)
		stock_path[i + 1] = stock_path[i] * (_drift + _vol_sqrt * args_[0][i]);

	return stock_path;
}
