//_ParkMillerXlw.h

#ifndef PARK_MILLER_XLW_H
#define PARK_MILLER_XLW_H

#include <Random2.h>
#include <xlw/ArgList.h>
#include "Wrapper.h" //Wrapper class in xlw package is improved version of wrapper class of the book
#include "ArgListFactory.h"
#include "Random2Xlw.h"

using namespace xlw;

class ParkMiller
{
public:

	ParkMiller(long Seed = 1);

	long GetOneRandomInteger();
	void SetSeed(long Seed);

	static unsigned long Max();
	static unsigned long Min();
	

private:

	long Seed;

};


class ParkMillerXlw : public RandomBaseXlw {

public:
	ParkMillerXlw(ArgumentList args);
	virtual ~ParkMillerXlw(){}
	virtual RandomBaseXlw* clone() const;

	virtual void GetUniforms(MJArray& variates);
	
	virtual void SetSeed(unsigned long Seed_);

	virtual void Skip(unsigned long numberOfPaths);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
	ParkMiller InnerGenerator;
	unsigned long Seed; 
	double Reciprocal;
};




#endif