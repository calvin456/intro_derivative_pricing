//_ParkMillerXlw.cpp

#include <string>
#include <Arrays.h> 
#include "ParkMillerXlw.h"

using namespace std;

const long a = 16807;
const long m = 2147483647;
const long q = 127773;
const long r = 2836;

ParkMiller::ParkMiller(long Seed_) : Seed(Seed_)
{
	if (Seed == 0)
		Seed = 1;
}


void ParkMiller::SetSeed(long Seed_)
{
	Seed = Seed_;
	if (Seed == 0)
		Seed = 1;
}

unsigned long ParkMiller::Max()
{
	return m - 1;
}

unsigned long ParkMiller::Min()
{
	return 1;
}

long ParkMiller::GetOneRandomInteger()
{
	long k;

	k = Seed / q;

	Seed = a*(Seed - k*q) - r*k;

	if (Seed < 0)
		Seed += m;

	return Seed;
}

ParkMillerXlw::ParkMillerXlw(ArgumentList args)
	:RandomBaseXlw(static_cast<unsigned long>(args.GetDoubleArgumentValue("dim")))
{
	if (args.GetStructureName() != "rng")
		throw("rng structure expected in ParkMillerXlw  class");

	if (args.GetStringArgumentValue("name") == "park miller"){
		ParkMiller _rng; InnerGenerator = _rng;
		Reciprocal = 1 / (1.0 + InnerGenerator.Max());
	}

	else throw("name list not for antithetic passed to ParkMillerXlw  : got " + args.GetStringArgumentValue("name"));
	
	Seed = static_cast<unsigned long>(args.GetDoubleArgumentValue("seed"));

	if (args.GetStructureName() != "seed") 	Seed = 1;

	args.CheckAllUsed("ParkMillerXlw");

	ResetDimensionality(static_cast<unsigned long>(args.GetDoubleArgumentValue("dim")));

}

RandomBaseXlw* ParkMillerXlw::clone() const
{
	return new ParkMillerXlw(*this);
}

void ParkMillerXlw::GetUniforms(MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++)
		variates[j] = InnerGenerator.GetOneRandomInteger()*Reciprocal;

}

void ParkMillerXlw::Skip(unsigned long numberOfPaths)
{
	MJArray tmp(GetDimensionality());
	for (unsigned long j = 0; j < numberOfPaths; j++)
		GetUniforms(tmp);
}

void ParkMillerXlw::SetSeed(unsigned long Seed)
{
	Seed = Seed;
	InnerGenerator.SetSeed(Seed);
}

void ParkMillerXlw::Reset()
{
	InnerGenerator.SetSeed(Seed);
}

void ParkMillerXlw::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBaseXlw::ResetDimensionality(NewDimensionality);
	InnerGenerator.SetSeed(Seed);
}
