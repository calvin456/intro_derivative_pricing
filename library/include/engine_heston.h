//engine_heston.h

#ifndef ENGINE_HESTON_H
#define ENGINE_HESTON_H

#include <wrapper.h>
#include <Parameters.h>
#include <MCStatistics.h>
#include <path_generation_heston.h>
#include <timer.h>
#include <memory>

using namespace std;

//Compute MC pricing of vanilla options
template<typename T>
void mc_pricer_heston(const T& TheOption,
								const Parameters& r,
								unique_ptr<PathGenerationHeston>&  ThePaths,
								unsigned long NumberOfPaths,
								StatisticsMC& gatherer,
								StatisticsMC& gatherer_time)
{
	
	
	timer t;
	t.start();

	double Expiry(TheOption.GetExpiry());
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(2);
	args[0] = MJArray(ThePaths->GetSteps());
	args[1] = MJArray(ThePaths->GetSteps());

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = ThePaths->GetOnePath(args); 
		double thisPayOff = TheOption.OptionPayOff(thisSpot); 
		gatherer.DumpOneResult(thisPayOff*discounting);
		gatherer_time.DumpOneResult(t.elapsedTime());
	}

}

//Compute MC pricing of vanilla options - ls stands for long and short stepping respectively
template<typename T>
void mc_pricer_heston_ls(const T& TheOption,
	const Parameters& r,
	unique_ptr<PathGenerationHeston>&  ThePaths,
	unsigned long NumberOfPaths,
	StatisticsMC& gatherer,
	StatisticsMC& gatherer_time)
{


	timer t;
	t.start();

	double Expiry(TheOption.GetExpiry());
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(2);
	args[0] = MJArray(ThePaths->GetSteps());
	args[1] = MJArray(ThePaths->GetSteps());

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = ThePaths->GetOnePathLS(args); 
		double thisPayOff = TheOption.OptionPayOff(thisSpot); 
		gatherer.DumpOneResult(thisPayOff*discounting);
		gatherer_time.DumpOneResult(t.elapsedTime());
	}
	//cout << endl;
}

//compute price w/o convergence table
template<typename T>
double mc_pricer_heston(const T& TheOption,
								const Parameters& r,
								unique_ptr<PathGenerationHeston>&  ThePaths,
								unsigned long NumberOfPaths)
{
	double Expiry(TheOption.GetExpiry());
	double discounting = exp(-r.Integral(0, Expiry));

	vector<MJArray> args(2);
	args[0] = MJArray(ThePaths->GetSteps());
	args[1] = MJArray(ThePaths->GetSteps());

	double sum(0.0);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisSpot = ThePaths->GetOnePath(args);
		sum += TheOption.OptionPayOff(thisSpot);
	}

	return sum * discounting / NumberOfPaths;
}


#endif
