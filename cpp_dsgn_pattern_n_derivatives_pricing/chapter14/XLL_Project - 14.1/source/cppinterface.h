//
//
//                                                                    Test.h
//

#ifndef TEST_H
#define TEST_H

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>

#include "reftest.h"
#include "wrapper.h"
#include "ArgListFactory.h"

#include "Random2Xlw.h"

using namespace xlw;

//<xlw:libraryname=MyRNGLibrary
//<xlw:typeregister(Wrapper<RandomBaseXlw> ArgumentList GetFromFactory<RandomBaseXlw>)

CellMatrix // generate pseudo random numbers using spec generator
//<xlw:time
//<xlw:volatile
GetUniforms(Wrapper<RandomBaseXlw>& RandomTable, // table for RNG
			double seed
);

CellMatrix // generate pseudo random number using spec generator
//<xlw:time
//<xlw:volatile
GetGaussians(Wrapper<RandomBaseXlw>& RandomTable, // table for RNG
			double seed
);


#endif
