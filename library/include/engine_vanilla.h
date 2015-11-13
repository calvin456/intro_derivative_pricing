//engine_vanilla.h

#ifndef ENGINE_VANILLA_H
#define ENGINE_VANILLA_H

//#include <wrapper.h>
#include <Parameters.h>
#include <MCStatistics.h>
#include <path_generation.h>
#include <path_generation_gbm.h>
#include <Timer.h>

using namespace std;

//Compute MC pricing of vanilla options
template<typename T>
void mc_pricer_vanilla(const T& TheOption,
					   const Parameters& r,
					   shared_ptr<PathGeneration>&  ThePaths,
					   unsigned long NumberOfPaths,
					   StatisticsMC& gatherer,
					   StatisticsMC& gatherer_time)
{
	timer t;
	t.start();

	double Expiry(TheOption.GetExpiry());
	//double thisSpot;
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(1);
	args[0] = MJArray(ThePaths->GetSteps());

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = ThePaths->GetOnePath(args); //cout << thisSpot << " ";
		double thisPayOff = TheOption.OptionPayOff(thisSpot);
		gatherer.DumpOneResult(thisPayOff*discounting);
		gatherer_time.DumpOneResult(t.elapsedTime());
	}

};

//compute price w/o convergence table
template<typename T>
double mc_pricer_vanilla(const T& TheOption,
						 const Parameters& r,
						 shared_ptr<PathGeneration>&  ThePaths,
						 unsigned long NumberOfPaths)
{
	double Expiry(TheOption.GetExpiry());
	//double thisSpot;
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(1);
	args[0] = MJArray(ThePaths->GetSteps());

	double sum(0.0);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = ThePaths->GetOnePath(args);
		sum += TheOption.OptionPayOff(thisSpot);
	}

	return sum * discounting / NumberOfPaths;
};

//1.finite difference with MC.
//Bump params


//2. Pathwise with MC.
template<typename T>
double pathwise_mc_delta(const T& TheOption,
						 const Parameters& r,
						 shared_ptr<PathGeneration>&  ThePaths,
						 unsigned long NumberOfPaths)
{
	double Expiry(TheOption.GetExpiry());
	//double thisSpot;
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(1);
	args[0] = MJArray(ThePaths->GetSteps());

	double sum(0.0);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = ThePaths->GetOnePath(args);
		double tmp(thisSpot > TheOption.GetStrike() ? 1.0 : 0.0);

		sum += thisSpot / ThePaths->GetSpot() * tmp;
	}

	return sum * discounting / NumberOfPaths;
};



#endif
