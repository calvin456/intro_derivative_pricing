#include <Sobol.h>

#include <vector>

using namespace std;

SobolRsg Sobol::sobolGen(1, 0, SobolRsg::Kuo);

Sobol::Sobol(long Seed_ ) : Seed(Seed_)
{
  if(Seed ==0)	Seed=0;
}

void Sobol::SetSeed(long Seed_)
{
  Seed=Seed_;
  if (Seed ==0)	Seed=0;
  sobolGen.skipTo( Seed_) ;
}

double Sobol::GetOneRandomInteger()
{
	typedef vector<Real> QMCPoint ;
	QMCPoint point = sobolGen.nextSequence().value ; // Generate next point
	Seed = static_cast<double>(point[0]);

    return Seed;
}


RandomSobol::RandomSobol(unsigned long Dimensionality, unsigned long Seed)
	:RandomBase(Dimensionality), InnerGenerator(Seed),InitialSeed(Seed)
{
	SetSeed(InitialSeed);
}

RandomBase* RandomSobol::clone() const
{
    return new RandomSobol(*this);
}

void RandomSobol::GetUniforms(MJArray& variates)
{
    for (unsigned long j=0; j < GetDimensionality(); j++)
		variates[j] = InnerGenerator.GetOneRandomInteger();
}

void RandomSobol::GetUniforms(vector<double>& variates, double a, double b)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++)
		variates[j] = InnerGenerator.GetOneRandomInteger();
}

void RandomSobol::Skip(unsigned long numberOfPaths)
{
    MJArray tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        GetUniforms(tmp);
}

void RandomSobol::SetSeed(unsigned long Seed)
{
    InitialSeed = Seed;
    InnerGenerator.SetSeed(Seed);
}

void RandomSobol::Reset()
{
    InnerGenerator.SetSeed(InitialSeed);
}


void RandomSobol::ResetDimensionality(unsigned long NewDimensionality)
{
    RandomBase::ResetDimensionality(NewDimensionality);
    InnerGenerator.SetSeed(InitialSeed);
}

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
