//barrier_option_analytical.cpp

/*
barrier option pricing, sulin suo, yong wang
*/

/*
2 put, call
2 in,out
2 down,up

2*2*2 = 8 - 8 options type
*/


#include <cmath>
#include <algorithm>
#include <iostream>

#include <Normals.h>
#include <BlackScholesFormulas.h>
#include <barrier_options_analytical.h>


using namespace std;
using namespace BSFunction;

//knock-in options

//the premium for up-and-in call option

double up_in_call(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	return BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) - up_out_call(Spot, Strike, Barrier, r, d, Vol, Expiry);

}


//the premium for the Down-and-In call option

double down_in_call(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	return BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) - down_out_call(Spot,Strike,Barrier,r,d,Vol,Expiry);

}

//	The premium for Up-and-In put option					 

double up_in_put(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	return BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) - up_out_put(Spot, Strike, Barrier, r, d, Vol, Expiry);

}


//The premium for the Down-and-In put option						 

double down_in_put(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	return BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) - down_out_put(Spot, Strike, Barrier, r, d, Vol, Expiry);

}

//knock-out type						 

//The premium for the Up-and-Out call option						 

double up_out_call(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	if (Spot >= Barrier){
		cout << "barrier touched" << endl;
		return 0.0;
	}

	double ratio(Spot / Barrier);
	double k_prime(2.0*(r - d) / (Vol * Vol));
	double a((1.0 - k_prime));

	double px = BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) - BlackScholesCall(Spot, Barrier, r, d, Vol, Expiry)
		- (Barrier - Strike) * BlackScholesDigitalCall(Spot, Barrier, r, d, Vol, Expiry)
			- pow(ratio, a) * (BlackScholesCall(Barrier / ratio, Strike, r, d, Vol, Expiry) 
				- BlackScholesCall(Barrier / ratio, Barrier, r, d, Vol, Expiry)
					- (Barrier - Strike) * BlackScholesDigitalCall(Barrier / ratio, Barrier, r, d, Vol, Expiry));
	
	if (px < 0.0) px = 0.0;

	return px;
}

//The premium for the down-and-Out call option						 

double down_out_call(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	if (Spot <= Barrier){
		cout << "barrier touched" << endl;
		return 0.0;
	}

	double ratio(Spot / Barrier);
	double k_prime(2.0*(r - d) / (Vol * Vol));
	double a((1.0 - k_prime));

	double px(0.0);
	
	if (Barrier < Strike){

	//case barrier below strike
	
		px = BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) 
			- pow(ratio, a) * BlackScholesCall(Barrier / ratio, Strike, r, d, Vol, Expiry);

		if (px < 0.0) px = 0.0;
	
	}else{

	//case barrier above the strike

		px = BlackScholesCall(Spot, Barrier, r, d, Vol, Expiry) 
			+ (Barrier - Strike) * BlackScholesDigitalCall(Spot, Barrier, r, d, Vol, Expiry)
				- pow(ratio, a) * (BlackScholesCall(Barrier / ratio, Barrier, r, d, Vol, Expiry) 
					+ (Barrier - Strike) * BlackScholesDigitalCall(Barrier / ratio, Barrier, r, d, Vol, Expiry));
	
		if (px < 0.0) px = 0.0;

	}
	
	return px;
}
	

//The premium for the up-and-Out put option						 

double up_out_put(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	if (Spot >= Barrier){
		cout << "barrier touched" << endl;
		return 0.0;
	}


	double ratio(Spot / Barrier);
	double k_prime(2.0*(r - d) / (Vol * Vol));
	double a((1.0 - k_prime));

	double px(0.0);

	if (Barrier > Strike){

	//case barrier above strike

		px = BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) 
			- pow(ratio, a) * BlackScholesPut(Barrier / ratio, Strike, r, d, Vol, Expiry);

		if (px < 0.0) px = 0.0;
	}
	else{
	
		//case barrier below the strike
	
		px = BlackScholesPut(Spot, Barrier, r, d, Vol, Expiry) 
			+ (Strike - Barrier) * BlackScholesDigitalPut(Spot, Barrier, r, d, Vol, Expiry)
				- pow(ratio, a) * (BlackScholesPut(Barrier / ratio, Barrier, r, d, Vol, Expiry) 
					+ (Strike - Barrier) * BlackScholesDigitalPut(Barrier / ratio, Barrier, r, d, Vol, Expiry));

		if (px < 0.0) px = 0.0;
	}

	return px;
}

//The premium for the down-and-Out put option						 

double down_out_put(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	if (Spot <= Barrier){
		cout << "barrier touched" << endl;
		return 0.0;
	}

	double ratio(Spot / Barrier);
	double k_prime(2.0*(r - d) / (Vol * Vol));
	double a((1.0 - k_prime));

	double px =  BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) - BlackScholesPut(Spot, Barrier, r, d, Vol, Expiry) 
		-(Strike - Barrier) * BlackScholesDigitalPut(Spot, Barrier, r, d, Vol, Expiry)
			- pow(ratio, a) * (BlackScholesPut(Barrier / ratio, Strike, r, d, Vol, Expiry) -
				BlackScholesPut(Barrier / ratio, Barrier, r, d, Vol, Expiry)
					- (Strike - Barrier) * BlackScholesDigitalPut(Barrier / ratio, Barrier, r, d, Vol, Expiry));
	
	if (px < 0.0)	px = 0.0;

	return px;

}
