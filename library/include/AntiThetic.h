//
//
//                  AntiThetic.h
//
//

//Edit file to reflect base class change.
// Add antithetic Gaussian variable

#ifndef ANTITHETIC_H
#define ANTITHETIC_H

#include <Random2.h>
#include <wrapper.h>

class AntiThetic : public RandomBase
{

public:
    AntiThetic(const Wrapper<RandomBase>& innerGenerator );

    virtual RandomBase* clone() const;

    virtual void GetUniforms(MJArray& variates);
	virtual void GetUniforms(std::vector<double>& variates, double a = 0.0, double b = 1.0);
	virtual void GetGaussians(MJArray& variates);
	virtual void GetGaussians(std::vector<double>& variates, double m = 0.0, double s = 1.0);

	virtual void GetLogNormals(double m, double s, MJArray& variates);
	virtual void GetExponentials(double lambda, MJArray& variates);
	virtual void GetPoissons(double lambda, MJArray& variates);
	virtual void GetGammas(double alpha, double beta, MJArray& variates);
	virtual void GetBetas(double alpha, double beta, MJArray& variates);

    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);

    virtual void ResetDimensionality(unsigned long NewDimensionality);
    virtual void Reset();
private:
    Wrapper<RandomBase> InnerGenerator;

    bool OddEven;

    MJArray NextVariates;
	std::vector<double> _NextVariates;
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
