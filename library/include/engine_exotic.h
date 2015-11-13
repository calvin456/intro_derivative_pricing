//engine_exotic.h

#ifndef EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H

//Compute MC pricing of exotic path-dependent options

#include <Parameters.h>
#include <PathDependent.h>
#include <MCStatistics.h>

#include <cmath>
#include <vector>

using namespace std;

template<typename T, typename U>
class engine_mc_exotic
{

public:
	engine_mc_exotic(shared_ptr<T>& TheOption_, //option type - Asian, discrete barrier
					const Parameters& r_,
					shared_ptr<U>& ThePaths_ //path model - jdp, svm, vg model
					)
	:TheOption(TheOption_), r(r_), ThePaths(ThePaths_)
	{

		Discounts = TheOption->PossibleCashFlowTimes();

		for (unsigned long i = 0; i < Discounts.size(); i++)
			Discounts[i] = exp(-r.Integral(0.0, Discounts[i]));

		TheseCashFlows.resize(TheOption->MaxNumberOfCashFlows());

	}

	virtual ~engine_mc_exotic(){}

	void DoSimulation(StatisticsMC& TheGatherer, unsigned long NumberOfPaths)
	{
		std::vector<MJArray> args(3);
		args[0] = MJArray(ThePaths->GetSteps());
		args[1] = MJArray(ThePaths->GetSteps());
		args[2] = MJArray(ThePaths->GetSteps());

		TheseCashFlows.resize(TheOption->MaxNumberOfCashFlows());

		for (unsigned long i = 0; i < NumberOfPaths; ++i)
		{
			MJArray thisSpots = ThePaths->GetWholePath(args);

			//thisSpots.print();

			double thisPayOff = DoOnePath(thisSpots); //cout << thisPayOff << endl;
			TheGatherer.DumpOneResult(thisPayOff);
		}

	}

	double DoOnePath(const MJArray& SpotValues) const
	{
		unsigned long NumberFlows = TheOption->CashFlows(SpotValues, TheseCashFlows,level);
		double Value = 0.0;

		for (unsigned i = 0; i < NumberFlows; ++i)
			Value += TheseCashFlows[i].Amount * Discounts[TheseCashFlows[i].TimeIndex];

		return Value;
	}

private:

	shared_ptr<T> TheOption;
	shared_ptr<U> ThePaths;
	Parameters r;
	MJArray Discounts;
	mutable std::vector<CashFlow> TheseCashFlows;

};

#endif
