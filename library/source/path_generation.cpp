//path_generation.cpp

#include "path_generation.h"

#include <cmath>
#include <algorithm>

using namespace std;

PathGeneration::PathGeneration(shared_ptr<RandomBase> TheGenerator_,
							   double Spot0_,
							   double T_,
							   unsigned long steps_)
	:TheGenerator(TheGenerator_), Spot0(Spot0_), T(T_), steps(steps_)
{}

void PathGeneration::SetSteps(unsigned long steps_) { 
	steps = steps_; 
	TheGenerator->ResetDimensionality(steps); 
}

void PathGeneration::SetSpot(double Spot0_) {
	double Spot0 = Spot0_;	
}


