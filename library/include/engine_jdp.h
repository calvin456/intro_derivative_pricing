//engine_jdp.h

#ifndef ENGINE_JDP_H
#define ENGINE_JDP_H

#include <wrapper.h>
#include <Parameters.h>
#include <MCStatistics.h>
#include <path_generation_jdp.h>
#include <timer.h>
#include <memory>

using namespace std;

//Compute MC pricing of vanilla options
template<typename T>
void mc_pricer_jdp(const T& TheOption,
								const Parameters& r,
								unique_ptr<PathGenerationJDP>&  ThePaths,
								unsigned long NumberOfPaths,
								StatisticsMC& gatherer,
								StatisticsMC& gatherer_time)
{
	timer t;
	t.start();

	double Expiry(TheOption.GetExpiry());
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(3);
	args[0] = MJArray(ThePaths->GetSteps());
	args[1] = MJArray(1);
	args[2] = MJArray(ThePaths->GetSteps());

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		//cout << i << " ";
		double thisSpot = ThePaths->GetOnePath(args); //cout << thisSpot << endl;
		double thisPayOff = TheOption.OptionPayOff(thisSpot);
		gatherer.DumpOneResult(thisPayOff * discounting);
		gatherer_time.DumpOneResult(t.elapsedTime());
	}

}

//compute price w/o convergence table
template<typename T>
double mc_pricer_jdp(const T& TheOption,
								const Parameters& r,
								unique_ptr<PathGenerationJDP>&  ThePaths,
								unsigned long NumberOfPaths){

	double Expiry(TheOption.GetExpiry());
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(3);
	args[0] = MJArray(ThePaths->GetSteps());
	args[1] = MJArray(1);
	args[2] = MJArray(ThePaths->GetSteps());

	double sum(0.0);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = ThePaths->GetOnePath(args);
		sum += TheOption.OptionPayOff(thisSpot);
	}

	return sum * discounting / NumberOfPaths;
}


#endif
