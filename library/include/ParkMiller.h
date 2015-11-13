//
//
//                      ParkMiller.h
//
//


//Edit file to reflect base class change.
//Add Park-Miller as implemented in std random library

#ifndef PARK_MILLER_H
#define PARK_MILLER_H

#include <Random2.h>
#include <random>
#include <vector>

using namespace std;

class ParkMiller
{
public:
	ParkMiller(unsigned long Seed = 1);

    static unsigned long Max();
    static unsigned long Min();

	void SetSeed(unsigned long Seed);
	void Skip(unsigned long numberOfPaths);

	double GetOneUniform(double a = 0.0, double b = 1.0);
	double GetOneGaussian(double m = 0.0, double s = 1.0);
	double GetOneLogNormal(double m, double s);
	double GetOneExponential(double lambda);
	double GetOnePoisson(double lambda);
	double GetOneGamma(double alpha, double beta);
	double GetOneBeta(double alpha, double beta);

private:
	unsigned long Seed;
	static minstd_rand generator; //external declaration
};

class RandomParkMiller : public RandomBase
{
public:

    RandomParkMiller(unsigned long Dimensionality, unsigned long Seed=1);
    virtual RandomBase* clone() const;
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    virtual void ResetDimensionality(unsigned long NewDimensionality);

    virtual void GetUniforms(MJArray& variates);
	virtual void GetUniforms(vector<double>& variates, double a = 0.0, double b = 1.0);

	virtual void GetGaussians(MJArray& variates);
	virtual void GetGaussians(vector<double>& variates, double m = 0.0, double s = 1.0);

	virtual void GetLogNormals(double m, double s, MJArray& variates);
	virtual void GetExponentials(double lambda, MJArray& variates);
	virtual void GetPoissons(double lambda, MJArray& variates);
	virtual void GetGammas(double alpha, double beta, MJArray& variates);
	virtual void GetBetas(double alpha, double beta, MJArray& variates);

private:

    ParkMiller InnerGenerator;
    unsigned long InitialSeed;


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
