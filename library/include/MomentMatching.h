//MomentMatching.h

/*
ex.1 Modify the random number classes to work w/ArgumentList factory (ArgListFactory)

Include anti-thetic sampling and moment matching w/arbitrary
 underlying classes amongst the classes to register.
*/

#ifndef MOMENT_MATCHING_H
#define MOMENT_MATCHING_H

#include <Random2.h>
#include <wrapper.h>

class MomentMatching:public RandomBase
{

public:
	MomentMatching(const Wrapper<RandomBase>& innerGenerator,
								double pop_mean_,
								double pop_std_dev_);

    virtual RandomBase* clone() const;
    virtual void GetUniforms(MJArray& variates);
	virtual void GetGaussians(MJArray& variates);

    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
	
    virtual void ResetDimensionality(unsigned long NewDimensionality);
    virtual void Reset();
private:
	Wrapper<RandomBase> InnerGenerator;

    MJArray NextVariates;
	
	double pop_mean;
	double pop_std_dev;
};

#endif


/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

