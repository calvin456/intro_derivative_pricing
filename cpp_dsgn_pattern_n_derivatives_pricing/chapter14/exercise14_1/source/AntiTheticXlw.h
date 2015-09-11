//AntiTheticXlw.h

#ifndef ANTITHETIC_XLW_H
#define ANTITHETIC_XLW_H

//#include <Random2.h>
//#include <AntiThetic.h>
#include <xlw\ArgList.h>
#include "Random2Xlw.h"
#include <wrapper.h> //Wrapper class in xlw package is improved version of wrapper class of the book
#include <ArgListFactory.h>

using namespace xlw;

class AntiTheticXlw : public RandomBaseXlw {

public:
	AntiTheticXlw(ArgumentList args);
	virtual ~AntiTheticXlw(){}
	virtual RandomBaseXlw* clone() const;

	//virtual unsigned long __thiscall GetDimensionality() const;

	virtual void GetUniforms(MJArray& variates);
	
	virtual void SetSeed(unsigned long Seed_);

	virtual void Skip(unsigned long numberOfPaths);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

	Wrapper<RandomBaseXlw> InnerGenerator;

	bool OddEven;

	MJArray NextVariates;
};



#endif