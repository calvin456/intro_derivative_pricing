
#include"cppinterface.h"
#pragma warning (disable : 4996)
#include <ctime>
//#include <Arrays.h>

//Excel : Array function
//1. Enter function =function()
//2. Select array
//3. ctrl + shift + enter

CellMatrix // generate pseudo random numbers using spec generator
GetUniforms(Wrapper<RandomBaseXlw>& RandomTable, // table for RNG
			double seed
			)
{
	if (seed != 0) RandomTable->SetSeed(static_cast<unsigned long>(seed));

	unsigned long dim(RandomTable->GetDimensionality());

	MJArray variates(dim);

	CellMatrix values(dim, 1);

	RandomTable->GetUniforms(variates);

	for (unsigned long i(0); i < dim; ++i)
		values(i, 0) = variates[i];

	return values;
};

CellMatrix // generate pseudo random number using spec generator
GetGaussians(Wrapper<RandomBaseXlw>& RandomTable, // table for RNG
			double seed
			)
{
	if (seed != 0) RandomTable->SetSeed(static_cast<unsigned long>(seed));
	
	unsigned long dim(RandomTable->GetDimensionality());
	
	MJArray variates(dim);
	
	CellMatrix values(dim,1);

	RandomTable->GetGaussians(variates);
	
	for (unsigned long i(0); i < dim; ++i)
		values(i,0) = variates[i];

	return values;
};
	 