//engine_simul.cpp

//#include <iostream>

#include <engine_simul.h>

using namespace std;

template<typename T>
EngineSimul<T>::EngineSimul(shared_ptr<HedgingStrategy<T>> TheHedgingStrategy_, unsigned long NumberOfPaths_)
	:TheHedgingStrategy(TheHedgingStrategy_), NumberOfPaths(NumberOfPaths_)
{}

template<typename T>
double EngineSimul<T>::DoSimulation() const {

	StatisticsVariance variance;
	vector<MJArray> args(1);
	args[0] = MJArray(TheHedgingStrategy->GetSteps());

	for (size_t i(0); i < NumberOfPaths; ++i){
		double result = TheHedgingStrategy->DoOnePath(args);
	
		variance.DumpOneResult(result);
	}

	return variance.GetResultsSoFar()[0][0];
}

template<typename T>
EngineSimulSV<T>::EngineSimulSV(shared_ptr<HedgingStrategySV<T>> TheHedgingStrategy_, unsigned long NumberOfPaths_)
	:TheHedgingStrategy(TheHedgingStrategy_), NumberOfPaths(NumberOfPaths_)
{}

template<typename T>
double EngineSimulSV<T>::DoSimulation() const {

	StatisticsVariance variance;
	vector<MJArray> args(2);
	args[0] = MJArray(TheHedgingStrategy->GetSteps());
	args[1] = MJArray(TheHedgingStrategy->GetSteps());

	for (size_t i(0); i < NumberOfPaths; ++i){
		double result = TheHedgingStrategy->DoOnePath(args);
	
		variance.DumpOneResult(result);
	}

	return variance.GetResultsSoFar()[0][0];
}
