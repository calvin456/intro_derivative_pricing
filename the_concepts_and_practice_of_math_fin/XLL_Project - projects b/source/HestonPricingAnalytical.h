//HestonPricingAnalytical.h

//price vanilla options using analytical for Heston model

#ifndef HESTON_PRICING_ANALYTICAL_H
#define HESTON_PRICING_ANALYTICAL_H

#include "HestonIntegrand.h"

double HestonVanillaCalltAnalytical(const ParametersHeston& p);

double HestonVanillaPutAnalytical(const ParametersHeston& p);




#endif
