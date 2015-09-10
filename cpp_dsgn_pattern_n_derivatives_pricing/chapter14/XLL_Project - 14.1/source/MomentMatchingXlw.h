//MomentMatchingXlw.h

#ifndef MOMENT_MATCHING_XLW_H
#define MOMENT_MATCHING_XLW_H

#include <Random2.h>
#include <MomentMatching.h>
#include <xlw/ArgList.h>
#include "Random2Xlw.h"
#include "Wrapper.h"
#include "ArgListFactory.h"

using namespace xlw;

class MomentMatchingXlw : public RandomBaseXlw {

public:
	MomentMatchingXlw(ArgumentList args);
	virtual RandomBaseXlw* clone() const;

	//virtual unsigned long __thiscall GetDimensionality() const;

	virtual void GetUniforms(MJArray& variates);
	
	virtual void SetSeed(unsigned long Seed_);

	virtual void Skip(unsigned long numberOfPaths);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
	Wrapper<RandomBaseXlw> InnerGenerator;
	double pop_mean;
	double pop_std_dev;
};



#endif