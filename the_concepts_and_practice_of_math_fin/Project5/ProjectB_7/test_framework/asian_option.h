//asian_options.h

//discrete Asian call option - Geometric average
double asian_geo_call(double Spot,
	unsigned long m, // # of observation dates
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);


//discrete Asian put option - Geometric average
double asian_geo_put(double Spot,
	unsigned long m, // # of observation dates
	double Strike,
	double r,
	double d,
	double Vol,
	double Expiry);
