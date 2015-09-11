//	RNGRegistration.cpp

#include "ArgListFactoryHelper.h"
#include "AntiTheticXlw.h"
#include "MomentMatchingXlw.h"
#include "ParkMillerXlw.h"
#include "MersenneTwisterXlw.h"

namespace
{
	FactoryHelper<RandomBaseXlw, AntiTheticXlw > AntitheticHelper("antithetic");
	FactoryHelper<RandomBaseXlw, MomentMatchingXlw> MomentmatchingHelper("moment matching");
	FactoryHelper<RandomBaseXlw, ParkMillerXlw> ParkMillerHelper("park miller");
	FactoryHelper<RandomBaseXlw, MersenneTwisterXlw> MersenneTwisterHelper("mersenne twister");

}
