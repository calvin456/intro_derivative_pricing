//  BlackSwaption.h

#ifndef BLACK_SWAPTION_H
#define BLACK_SWAPTION_H


//project 11. Add class for Black model

class BlackSwaption
{

public:

	BlackSwaption(double annuity_, double swap_rate_, double strike_, double expiry_);

	double Price(double vol) const;
	double Vega(double vol) const;

private:

	double annuity;
	double swap_rate;
	double strike;
	double expiry;

};


#endif