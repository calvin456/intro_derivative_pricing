//_MomentMatchingXlw.cpp


#include "MomentMatchingXlw.h"

#include <Arrays.h>
#include <ParkMiller.h>
#include <MersenneTwister.h>
#include <MyFunctions.h>
#include <string>

using namespace std;

MomentMatchingXlw::MomentMatchingXlw(ArgumentList args)
	:RandomBaseXlw()
{

	if (args.GetStructureName() != "rng")
		throw("rng structure expected in MomentMatchingXlw  class");

	if (args.GetStringArgumentValue("name") != "moment matching")
		throw("name list not for moment matching passed to MomentMatchingXlw  : got " + args.GetStringArgumentValue("name"));

	InnerGenerator = Wrapper<RandomBaseXlw>(GetFromFactory<RandomBaseXlw>(args.GetArgumentListArgumentValue("innergenerator")));
	
	pop_mean = args.GetDoubleArgumentValue("pop mean");

	pop_std_dev = args.GetDoubleArgumentValue("pop std dev");

	ResetDimensionality(InnerGenerator->GetDimensionality());

	args.CheckAllUsed("MomentMatchingXlw ");

}


RandomBaseXlw* MomentMatchingXlw::clone() const
{
	return new MomentMatchingXlw(*this);
}

//unsigned long __thiscall MomentMatchingXlw::GetDimensionality() const { return RandomBaseXlw::GetDimensionality(); }

void MomentMatchingXlw::GetUniforms(MJArray& variates)
{
	
	//match the first and second moments	

	InnerGenerator->GetUniforms(variates);

	double smpl_avg = mean(variates);
	double smpl_std_dev = std_dev(variates);

	for (unsigned long i = 0; i < GetDimensionality(); i++){
			variates[i] = pop_mean + (variates[i] - smpl_avg) * pop_std_dev / smpl_std_dev;
	}
	
}

void MomentMatchingXlw::Skip(unsigned long numberOfPaths)
{
	MJArray tmp(GetDimensionality());
	for (unsigned long j = 0; j < numberOfPaths; j++)
		GetUniforms(tmp);
}

void MomentMatchingXlw::SetSeed(unsigned long Seed)
{
	Seed = Seed;
	InnerGenerator->SetSeed(Seed);
}

void MomentMatchingXlw::Reset()
{
	InnerGenerator->Reset();
	
}


void MomentMatchingXlw::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBaseXlw::ResetDimensionality(NewDimensionality);
	InnerGenerator->ResetDimensionality(NewDimensionality);
}
