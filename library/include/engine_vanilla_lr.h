//engine_vanilla_lr.h

#ifndef ENGINE_VANILLA_LR_H
#define ENGINE_VANILLA_LR_H

//#include <wrapper.h>
#include <Parameters.h>
#include <MCStatistics.h>

#include <path_generation_gbm.h>
#include <Timer.h>

using namespace std;

//ref. module 2, mc methods, prof, Mike Giles, Oxford University

//3. Likelihood ratio with MC
template<typename T>
double l_ratio_mc_delta(const T& TheOption,
	const Parameters& r,
	shared_ptr<PathGenerationGBM>&  ThePaths,
	unsigned long NumberOfPaths)
{
	double Expiry(TheOption.GetExpiry());
	//double thisSpot;
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(1);
	args[0] = MJArray(ThePaths->GetSteps());


	double num(1.0 / (ThePaths->GetSpot() * sqrt(ThePaths->GetVol().IntegralSquare(0, Expiry))));

	double sum(0.0);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = ThePaths->GetOnePath(args);
		sum += args[0][0] * num *TheOption.OptionPayOff(thisSpot);
	}

	return sum * discounting / NumberOfPaths;

};

//to do add lr for vega

#endif
