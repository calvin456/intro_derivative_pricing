//_AntiTheticXlw.cpp

#include <string>
#include <Arrays.h>
#include <ParkMiller.h>
#include <MersenneTwister.h>
#include "AntiTheticXlw.h"

using namespace std;

AntiTheticXlw::AntiTheticXlw(ArgumentList args)
	:RandomBaseXlw()
{

	if (args.GetStructureName() != "rng")
		throw("rng structure expected in AntiTheticXlw  class");

	if (args.GetStringArgumentValue("name") != "antithetic")
		throw("rng list not for antithetic passed to AntiTheticXlw  : got " + args.GetStringArgumentValue("name"));

	InnerGenerator = Wrapper<RandomBaseXlw>(GetFromFactory<RandomBaseXlw>(args.GetArgumentListArgumentValue("innergenerator")));
	
	
	OddEven = true;
	NextVariates.resize(GetDimensionality());

	ResetDimensionality(InnerGenerator->GetDimensionality());

	args.CheckAllUsed("AntiTheticXlw ");
}


RandomBaseXlw* AntiTheticXlw::clone() const
{
	return new AntiTheticXlw(*this);
}

//unsigned long __thiscall AntiTheticXlw::GetDimensionality() const { return RandomBaseXlw::GetDimensionality(); }

void AntiTheticXlw::GetUniforms(MJArray& variates)
{
	

	if (OddEven)
	{
		InnerGenerator->GetUniforms(variates);

		for (unsigned long i = 0; i < GetDimensionality(); i++)
			NextVariates[i] = 1.0 - variates[i];

		OddEven = false;
	}
	else
	{
		variates = NextVariates;
		OddEven = true;
	}
	
}

void AntiTheticXlw::SetSeed(unsigned long Seed)
{
	InnerGenerator->SetSeed(Seed);
	OddEven = true;
}

void AntiTheticXlw::Skip(unsigned long numberOfPaths)
{
	if (numberOfPaths == 0)
		return;

	if (OddEven)
	{
		OddEven = false;
		numberOfPaths--;
	}

	InnerGenerator->Skip(numberOfPaths / 2);

	if (numberOfPaths % 2)
	{
		MJArray tmp(GetDimensionality());
		GetUniforms(tmp);
	}
	
}

void AntiTheticXlw::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBaseXlw::ResetDimensionality(NewDimensionality);
	InnerGenerator->ResetDimensionality(NewDimensionality);
	NextVariates.resize(NewDimensionality);
}

void AntiTheticXlw::Reset()
{
	InnerGenerator->Reset();
	OddEven = true;
}