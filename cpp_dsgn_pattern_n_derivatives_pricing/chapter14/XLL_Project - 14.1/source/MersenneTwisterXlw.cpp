//_MersenneTwisterXlw.cpp

#include <string>
#include <Arrays.h>
#include "MersenneTwisterXlw.h"

using namespace std;

base_generator_type MersenneTwister::generator(12411UL);

MersenneTwister::MersenneTwister(unsigned long Seed_) : Seed(Seed_)
{
	MersenneTwister::generator.seed(Seed_);
	if (Seed == 0UL)	Seed = 12411UL;
}

void MersenneTwister::SetSeed(unsigned long Seed_)
{
	Seed = Seed_;
	if (Seed == 0UL)	Seed = 12411UL;
	generator.seed(Seed_);
}

unsigned long MersenneTwister::Max()
{
	return MersenneTwister::generator.max();
}

unsigned long MersenneTwister::Min()
{
	return MersenneTwister::generator.min();
}

double MersenneTwister::GetOneUniform()
{
	uniform_real<> uni_dist(0, 1);
	variate_generator<base_generator_type&, uniform_real<> > rng(generator, uni_dist);

	Seed = rng();

	return Seed;
}

double MersenneTwister::GetOneGaussian()
{
	normal_distribution<> normal(0, 1);
	variate_generator<base_generator_type&, normal_distribution<> > rng(generator, normal);

	Seed = rng();

	return Seed;
}


MersenneTwisterXlw::MersenneTwisterXlw(ArgumentList args)
	:RandomBaseXlw(static_cast<unsigned long>(args.GetDoubleArgumentValue("dim")))
{

	if (args.GetStructureName() != "rng")
		throw("rng structure expected in MersenneTwisterXlw  class");

	if (args.GetStringArgumentValue("name") == "mersenne twister"){
		MersenneTwister _rng; InnerGenerator = _rng;
	}
	else throw("name list not for antithetic passed to MersenneTwisterXlw  : got " + args.GetStringArgumentValue("name"));

	Seed = static_cast<unsigned long>(args.GetDoubleArgumentValue("seed"));

	if (args.GetStructureName() != "seed")	Seed = 12411;

	args.CheckAllUsed("MersenneTwisterXlw");

	ResetDimensionality(static_cast<unsigned long>(args.GetDoubleArgumentValue("dim")));

}


RandomBaseXlw* MersenneTwisterXlw::clone() const
{
	return new MersenneTwisterXlw(*this);
}

void MersenneTwisterXlw::GetUniforms(MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneUniform();
	}
}

void MersenneTwisterXlw::Skip(unsigned long numberOfPaths)
{
	MJArray tmp(GetDimensionality());
	for (unsigned long j = 0; j < numberOfPaths; j++)
		GetUniforms(tmp);
}

void MersenneTwisterXlw::SetSeed(unsigned long Seed)
{
	Seed = Seed;
	InnerGenerator.SetSeed(Seed);
}

void MersenneTwisterXlw::Reset()
{
	InnerGenerator.SetSeed(Seed);
}


void MersenneTwisterXlw::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBaseXlw::ResetDimensionality(NewDimensionality);
	InnerGenerator.SetSeed(Seed);
}

