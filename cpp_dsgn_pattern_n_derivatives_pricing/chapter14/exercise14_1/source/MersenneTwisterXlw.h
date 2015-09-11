//_MersenneTwisterXlw.h

#ifndef MERSNNE_TWISTER_XLW_H
#define MERSNNE_TWISTER_XLW_H

#include<random>
#include <xlw/ArgList.h>
#include "Random2Xlw.h"
#include "Wrapper.h" //Wrapper class in xlw package is improved version of wrapper class of the book
#include "ArgListFactory.h"

using namespace xlw;

typedef std::mt19937 base_generator_type;

class MersenneTwister
{
public:
	MersenneTwister(unsigned long Seed = 12411);

	double GetOneUniform();
	double GetOneGaussian();

	void SetSeed(unsigned long Seed);

	static unsigned long Max();
	static unsigned long Min();

private:
	double Seed;
	static base_generator_type generator;
};


class MersenneTwisterXlw : public RandomBaseXlw {

public:
	MersenneTwisterXlw(ArgumentList args);
	virtual ~MersenneTwisterXlw(){}
	virtual RandomBaseXlw* clone() const;

	virtual void GetUniforms(MJArray& variates);
	
	virtual void SetSeed(unsigned long Seed_);

	virtual void Skip(unsigned long numberOfPaths);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);


private:
	MersenneTwister InnerGenerator;
	unsigned long Seed; 
};



#endif