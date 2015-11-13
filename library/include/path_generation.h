//path_generation.h

//Simulator needs to have whole memory of stock path

#ifndef PATH_GEN_H
#define PATH_GEN_H

#include<vector>
#include<Arrays.h>
#include<memory>
#include<Random2.h>

using namespace std;

typedef std::vector<MJArray> args;

class PathGeneration{
	//abstract class

public:
	PathGeneration(std::shared_ptr<RandomBase> TheGenerator_,
				   double Spot0_,
				   double T_,
				   unsigned long steps_=1);
	virtual ~PathGeneration(){}
	virtual double GetOnePath(args& args_) const=0;
	virtual MJArray GetWholePath(args& args_) = 0;

	virtual double GetSpot() const { return Spot0; }
	virtual void SetSpot(double Spot0_);

	virtual unsigned long GetSteps() const { return steps; }
	virtual void SetSteps(unsigned long steps_);
protected:
	std::shared_ptr<RandomBase> TheGenerator;
	double Spot0;
	double T;
	unsigned long steps;
};



#endif
