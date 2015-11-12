//mc pricer with p1 as numeraire

#ifndef MC_H
#define MC_H

#include <Vanilla3.h>
#include <Parameters.h>
#include <Random2.h>
#include <MCStatistics.h>

using namespace Vanilla;


enum method { EULER, PC };

void SimpleMonteCarloP1(const VanillaOption& TheOption,
	double Fwd,
	double t1,
	double t2,
	const Parameters& Vol,
	unsigned long NumberOfPaths,
	StatisticsMC& gatherer,
	RandomBase& generator);

void SimpleMonteCarloP2(const VanillaOption& TheOption,
	method m,
	double Fwd,
	double t1,
	double t2,
	const Parameters& Vol,
	unsigned long NumberOfPaths,
	StatisticsMC& gatherer,
	RandomBase& generator);


#endif