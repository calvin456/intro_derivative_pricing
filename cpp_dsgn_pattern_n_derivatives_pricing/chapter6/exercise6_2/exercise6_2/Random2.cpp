//
//
//                      Random2.cpp
//
//

#include <Random2.h>
#include <Normals.h>
#include <cstdlib>


void RandomBase::GetUniforms(vector<double>& variates)
{
	MJArray _variates(variates.size());

	for (unsigned long i(0); i < _variates.size(); ++i)
		_variates[i] = variates[i];

    GetUniforms(_variates);
	
	for (unsigned long i(0); i < _variates.size(); ++i)
		variates[i] = _variates[i];
}

void RandomBase::GetGaussians(MJArray& variates)
{
    GetUniforms(variates);

    for (unsigned long i=0; i < Dimensionality; i++)
    {
		double x = variates[i];
		variates[i] = InverseCumulativeNormal(x);
    }
}

void RandomBase::GetGaussians(vector<double>& variates)
{
	MJArray _variates(variates.size());

	for (unsigned long i(0); i < _variates.size(); ++i)
		_variates[i] = variates[i];

	GetGaussians(_variates);

	for (unsigned long i(0); i < _variates.size(); ++i)
		variates[i] = _variates[i];
}

void RandomBase::ResetDimensionality(unsigned long NewDimensionality)
{
    Dimensionality = NewDimensionality;
}

RandomBase::RandomBase(unsigned long Dimensionality_)
: Dimensionality(Dimensionality_)
{
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
