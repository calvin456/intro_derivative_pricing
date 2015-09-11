//Random2Xl.cpp

#include <cstdlib>
#include "Random2Xlw.h"
#include <Normals.h>

using namespace std;


unsigned long RandomBaseXlw::GetDimensionality() const
{
	return Dimensionality;
}

void RandomBaseXlw::GetGaussians(MJArray& variates)
{
	GetUniforms(variates);

	for (unsigned long i = 0; i < Dimensionality; i++)
	{
		double x = variates[i];
		variates[i] = InverseCumulativeNormal(x);
	}
}

void RandomBaseXlw::ResetDimensionality(unsigned long NewDimensionality)
{
	Dimensionality = NewDimensionality;
}

RandomBaseXlw::RandomBaseXlw(unsigned long Dimensionality_)
	: Dimensionality(Dimensionality_)
{
}