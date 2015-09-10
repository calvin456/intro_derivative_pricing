//quanto_margrabe.h

#ifndef QUANTO_MARGRABE_H
#define QUANTO_MARGRABE_H

double QuantCallOption(double Spot,
						double Strike,
						double rd, //interest rate of domestic currency
						double rf, //interest rate of foreign currency
						double d, //dvd yield
						double VolS, //vol stock price 
						double VolQ, //vol foreign currency
						double correl, // correl
						double Expiry);

double QuantPutOption(double Spot,
						double Strike,
						double rd, //interest rate of domestic currency
						double rf, //interest rate of foreign currency
						double d, //dvd yield
						double VolS, //vol stock price 
						double VolQ, //vol foreign currency
						double correl, // correl
						double Expiry);

double MargrabeOptions(double Spot1,
						double Spot2,
						double Vol1,
						double Vol2,
						double correl, // correl
						double Expiry);

#endif