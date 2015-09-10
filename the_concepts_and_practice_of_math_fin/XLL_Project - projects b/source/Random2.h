//
//
//                        Random2.h
//
//

//Modified version of random2.h to accommodate vector container
//Since C++11, Boost rngs part of std library, #include<random>

#ifndef RANDOM2_H
#define RANDOM2_H

#include <Arrays.h>
#include<vector>

using namespace std;

class RandomBase
{
public:

    RandomBase(unsigned long Dimensionality);
	RandomBase(){}

	virtual ~RandomBase(){}

    inline unsigned long GetDimensionality() const;

    virtual RandomBase* clone() const=0;

    virtual void Skip(unsigned long numberOfPaths)=0;
    virtual void SetSeed(unsigned long Seed) =0;
    virtual void Reset()=0;

    virtual void ResetDimensionality(unsigned long NewDimensionality);

    virtual void GetUniforms(MJArray& variates)=0;
	virtual void GetUniforms(vector<double>& variates, double a = 0.0, double b = 1.0) = 0;

    virtual void GetGaussians(MJArray& variates);
	virtual void GetGaussians(vector<double>& variates, double m = 0.0, double s = 1.0);
	
	virtual void GetLogNormals(double m, double s, vector<double>& variates){}
	virtual void GetExponentials(double lambda, vector<double>& variates){}
	virtual void GetPoissons(double lambda, vector<double>& variates){}
	virtual void GetGammas(double alpha, double beta, vector<double>& variates){}
	virtual void GetBetas(double alpha, double beta, vector<double>& variates){}

private:
    unsigned long Dimensionality;

};

unsigned long RandomBase::GetDimensionality() const
{
    return Dimensionality;
}

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
