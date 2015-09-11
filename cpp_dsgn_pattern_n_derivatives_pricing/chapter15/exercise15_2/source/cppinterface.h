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

#include "BlackScholesFormulas.h"

using namespace xlw;

//<xlw:libraryname=152Library


double _BlackScholesCall(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double _BlackScholesPut(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double _BlackScholesDigitalCall(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double _BlackScholesDigitalPut(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);

double _BlackScholesCallVega(double Spot,
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);



#endif
