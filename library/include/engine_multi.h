//engine_multi.h

#ifndef ENGINE_MULTI_H
#define ENGINE_MULTI_H

#include <Parameters.h>
#include <MCStatistics.h>
#include <path_generation_multi.h>
#include <Timer.h>

using namespace std;

//Compute MC pricing of vanilla options
template<typename T>
void mc_pricer_multi(const T& TheOption,
								const Parameters& r,
								shared_ptr<PathGenerationMulti>&  ThePaths,
								unsigned long NumberOfPaths,
								StatisticsMC& gatherer,
								StatisticsMC& gatherer_time)
{
	timer t;
	t.start();

	double Expiry(TheOption.GetExpiry());
	double discounting = exp(-r.Integral(0, Expiry));

	std::vector<MJArray> args(ThePaths->GetSteps()); 

	for (size_t i(0); i < ThePaths->GetSteps(); ++i)
		args[i] = MJArray(ThePaths->GetSize());
	
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		MJArray thisSpots = ThePaths->GetOnePathMulti(args);
		double thisPayOff = TheOption.OptionPayOff(thisSpots);
		gatherer.DumpOneResult(thisPayOff*discounting);
		gatherer_time.DumpOneResult(t.elapsedTime());
	}

}

//compute price w/o convergence table
template<typename T>
double mc_pricer_multi(const T& TheOption,
								const Parameters& r,
								shared_ptr<PathGenerationMulti>&  ThePaths,
								unsigned long NumberOfPaths){

	double Expiry(TheOption.GetExpiry());
	double discounting = exp(-r.Integral(0, Expiry));

	std::vector<MJArray> args(ThePaths->GetSteps());

	for (size_t i(0); i < ThePaths->GetSteps(); ++i)
		args[i] = MJArray(ThePaths->GetSize());

	double sum(0.0);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		MJArray thisSpots = ThePaths->GetOnePathMulti(args);
		sum += TheOption.OptionPayOff(thisSpots);
	}

	return sum * discounting / NumberOfPaths;
}


#endif
