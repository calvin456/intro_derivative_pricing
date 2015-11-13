//engine_simul.h

//Compute mean and variance of final p&l
//Investigate sensitivity to rebalancing interval and volatility

#ifndef ENGINE_H
#define ENGINE_H
#include <MCStatistics.h>
#include <hedging_strategy.h>
#include <hedging_strategy_sv.h>

//typedef vector<vector<double>> matrix;

template<typename T>
class EngineSimul {

public:
	EngineSimul(shared_ptr<HedgingStrategy<T>> TheHedgingStrategy_,
				unsigned long NumberOfPaths_);
	~EngineSimul(){}
	double DoSimulation() const;
private:
	shared_ptr<HedgingStrategy<T>> TheHedgingStrategy;
	unsigned long NumberOfPaths;
};

template<typename T>
class EngineSimulSV {

public:
	EngineSimulSV(shared_ptr<HedgingStrategySV<T>> TheHedgingStrategy_,
		unsigned long NumberOfPaths_);
	~EngineSimulSV(){}
	double DoSimulation() const;
private:
	shared_ptr<HedgingStrategySV<T>> TheHedgingStrategy;
	unsigned long NumberOfPaths;
};

#endif
