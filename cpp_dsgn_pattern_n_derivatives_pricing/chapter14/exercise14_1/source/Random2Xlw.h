//Random2Xlw.h

#ifndef RANDOM_XLW_H
#define RANDOM_XLW_H

#include <cstdlib>
#include<Arrays.h>
#include <Normals.h>

using namespace std;

class RandomBaseXlw{

public:
	RandomBaseXlw(unsigned long Dimensionality = 1);
	//RandomBaseXlw(){}
	virtual ~RandomBaseXlw(){}
	virtual RandomBaseXlw* clone() const = 0;

	virtual void GetUniforms(MJArray& variates) = 0;
	virtual void GetGaussians(MJArray& variates);

	virtual unsigned long   GetDimensionality() const;
	virtual void SetSeed(unsigned long Seed_) = 0;

	virtual void Skip(unsigned long numberOfPaths) = 0;
	virtual void Reset() = 0;
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
	unsigned long Dimensionality;
};

#endif 