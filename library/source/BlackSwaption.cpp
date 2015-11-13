//   BlackSwaption.cpp


#include "BlackSwaption.h"
#include <interest_derivatives_analytical.h>

BlackSwaption::BlackSwaption(double annuity_, double swap_rate_, double strike_, double expiry_)
	:annuity(annuity_), swap_rate(swap_rate_), strike(strike_), expiry(expiry_)

{}

double BlackSwaption::Price(double vol) const
{
	return black_formula_payer_swaption(annuity, swap_rate, strike, vol, expiry);
}


double BlackSwaption::Vega(double vol) const
{
	return black_swaption_vega(annuity, swap_rate, strike, vol, expiry);
}