//barrier_options_analytical.h

#ifndef BARRIER_ANALYTICAL_H
#define BARRIER_ANALYTICAL_H



//knock-in options

//the premium for up-and-in call option
double up_in_call(double Spot, double Strike, double Barrier, double r, double d, double Vol, double Expiry);

//the premium for the Down-and-In call option
double down_in_call(double Spot,double Strike,double Barrier,double r,double d,double Vol,double Expiry);

//	The premium for up-and-in put option					 
double up_in_put(double Spot,double Strike,double Barrier,double r,double d,double Vol,double Expiry);

//The premium for the Down-and-In put option						 
double down_in_put(double Spot,double Strike,double Barrier,double r,double d,double Vol,double Expiry);

//knock-out type						 

//The premium for the Up-and-Out call option						 
double up_out_call(double Spot,double Strike,double Barrier,double r,double d,double Vol,double Expiry);

//The premium for the down-and-Out call option						 
double down_out_call(double Spot,double Strike,double Barrier,double r,double d,double Vol,double Expiry);

//The premium for the up-and-Out put option						 
double up_out_put(double Spot,double Strike,double Barrier,double r, double d,double Vol,double Expiry);

//The premium for the down-and-Out put option						 
double down_out_put(double Spot,double Strike,double Barrier,double r,double d,double Vol,double Expiry);

#endif