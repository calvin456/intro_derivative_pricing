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

#include"barrier_options_analytical.h"
#include<cmath>
#include<minmax.h>
#include<Normals.h>

#include<BlackScholesFormulas.h>

using namespace std;


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

	double ratio(Spot / Barrier);
	double k_prime((r - d) / (.5 * Vol * Vol));
	double a(.5 *(1.0 - k_prime));
	//double a((r - d) / (.5 * Vol * Vol));

	return BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) - BlackScholesCall(Spot, Barrier, r, d, Vol, Expiry)
		- (Barrier - Strike) * BlackScholesDigitalCall(Spot, Barrier, r, d, Vol, Expiry)
			- pow(ratio, 2.0 * a) * 
			(BlackScholesCall(Barrier / ratio, Strike, r, d, Vol, Expiry) - BlackScholesCall(Barrier / ratio, Barrier, r, d, Vol, Expiry)
					- (Barrier - Strike) * BlackScholesDigitalCall(Barrier / ratio, Barrier, r, d, Vol, Expiry));

}

//The premium for the down-and-Out call option						 

double down_out_call(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){



	double ratio(Spot / Barrier);
	double k_prime((r - d) / (.5 * Vol * Vol));
	//double a(.5 *(1.0 - k_prime));
	double a((r - d) / (.5 * Vol * Vol));

	if (Barrier < Strike){

		//case barrier below strike

		return BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) - 
			pow(1/ratio, (2.0 * a)) * BlackScholesCall(Barrier / ratio, Strike, r, d, Vol, Expiry);

	}else{

		//case barrier above the strike

		return BlackScholesCall(Spot, Barrier, r, d, Vol, Expiry) + (Barrier - Strike) * BlackScholesDigitalCall(Spot, Barrier, r, d, Vol, Expiry)
			- pow(ratio, (2.0 * a)) * (BlackScholesCall(Barrier / ratio, Barrier, r, d, Vol, Expiry) +
			(Barrier - Strike) * BlackScholesDigitalCall(Barrier / ratio, Barrier, r, d, Vol, Expiry));
	}
}

//The premium for the up-and-Out put option						 

double up_out_put(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	double ratio(Spot / Barrier);
	double k_prime((r - d) / (.5 * Vol * Vol));
	double a(.5 *(1.0 - k_prime));
	//double a((r - d) / (.5 * Vol * Vol));

	if (Barrier > Strike){

	//case barrier above strike

		return BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) - pow(ratio, 2.0 * a) * BlackScholesPut(Barrier / ratio, Strike, r, d, Vol, Expiry);

	}
	else{

		//case barrier below the strike

		return BlackScholesPut(Spot, Barrier, r, d, Vol, Expiry) + (Strike - Barrier) * BlackScholesDigitalPut(Spot, Barrier, r, d, Vol, Expiry)
			- pow(ratio, (2.0 * a)) * 
			(BlackScholesPut(Barrier / ratio, Barrier, r, d, Vol, Expiry) +
			(Strike - Barrier) * BlackScholesDigitalPut(Barrier / ratio, Barrier, r, d, Vol, Expiry));

	}
}

//The premium for the down-and-Out put option						 

double down_out_put(double Spot,
	double Strike,
	double Barrier,
	double r,
	double d,
	double Vol,
	double Expiry){

	double ratio(Spot / Barrier);
	double k_prime((r - d) / (.5 * Vol * Vol));
	double a(.5 *(1.0 - k_prime));
	//double a((r - d) / (.5 * Vol * Vol));

	return BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) - BlackScholesPut(Spot, Barrier, r, d, Vol, Expiry) 
		-(Strike - Barrier) * BlackScholesDigitalPut(Spot, Barrier, r, d, Vol, Expiry)
			- pow(ratio, (2.0 * a)) * (BlackScholesPut(Barrier / ratio, Strike, r, d, Vol, Expiry) -
				BlackScholesPut(Barrier / ratio, Barrier, r, d, Vol, Expiry)
				- (Strike - Barrier) * BlackScholesDigitalPut(Barrier / ratio, Barrier, r, d, Vol, Expiry));

}
