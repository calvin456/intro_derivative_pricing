
#include "cppinterface.h"
#pragma warning (disable : 4996)

#include "BlackScholesFormulas.h"
#include "SteppingMethods.h"
#include "BSCallTwo.h"
#include "NewtonRaphson.h"
#include "ctime"
#include "analytical_jdm_pricer.h"
#include "options.h"
#include "quanto_margrabe.h"
#include "HestonPricingAnalytical.h"

#include "VGPricingAnalytical.h"
#include "barrier_options_analytical.h"



double // evaluate BlackScholes call price
_BlackScholesCall( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 )
{
							 
	return BlackScholesCall(Spot,Strike, r,d, Vol, Expiry);
                                             
}


double // evaluate BlackScholes put price
_BlackScholesPut( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 )
{
	
	return BlackScholesPut(Spot,Strike, r,d, Vol, Expiry);
}

double // evaluate BlackScholes digital call price
_BlackScholesDigitalCall(double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 )
{
								   
	return BlackScholesDigitalCall(Spot,Strike, r,d, Vol, Expiry);

}

double // evaluate BlackScholes digital put price
_BlackScholesDigitalPut(double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 )
{
								   
	return BlackScholesDigitalPut(Spot,Strike, r,d, Vol, Expiry);

}



							 
double // evaluate forward price
_Forward( double Spot,
							double Strike,
                            double r,
                            double d,
							double Expiry){
	
	return Forward(Spot,Strike, r,d,Expiry);
														
}

							 
double // evaluate forward price
_ZeroCoupon( double r,
							double Expiry){
	
	return ZeroCoupon(r,Expiry);
						
}



double // evaluate final price bsd on Euler stepping
_FinalPrice_EulerStepping( double Spot,
                         short Steps, //Number of steps
                         double r,
                         double d,
                         double Vol,
						 double Expiry){

	return FinalPrice_EulerStepping( Spot,Steps,r,d,Vol, Expiry);
                         						
}

double // evaluate BlackScholes call vega derivatives
_BlackScholesCallVega( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 ){

	return BlackScholesCallVega(Spot,Strike, r,d, Vol, Expiry);
                         						
}

double // evaluate BlackScholes call delta derivatives
_BlackScholesCallDelta( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 ){

	return BlackScholesCallDelta(Spot,Strike, r,d, Vol, Expiry);
                         						
}

double // evaluate BlackScholes call gamma derivatives
_BlackScholesGamma( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 ){

	return BlackScholesGamma(Spot,Strike, r,d, Vol, Expiry);
                         						
}

double // evaluate BlackScholes call rho derivatives
_BlackScholesCallRho( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 ){

	return BlackScholesCallRho(Spot,Strike, r,d, Vol, Expiry);
                         						
}

double // evaluate BlackScholes call rho derivatives
_BlackScholesCallTheta( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 ){

	return BlackScholesCallTheta(Spot,Strike, r,d, Vol, Expiry);
                         						
}


double // evaluate implied volatility using BSM
_ImpliedVolatility(double Price //option price
					, double r //interest rate
					, double d //dividend yield
					, double Expiry //expiry
					, double Spot //spot
					, double Strike //strike
					, double Start //start vol. Set by default 20%
					, double Tolerance //tolerance. Set by default 1e-6
){

	BSCallTwo theCall(r, d, Expiry, Spot, Strike);

	Terminator terminator(5, 100); //5 sec, 100 max iter

	return NewtonRaphson1<BSCallTwo, &BSCallTwo::Price, &BSCallTwo::Vega>(Price,
		Start, Tolerance, theCall, terminator);

}



double // evaluate jump diffusion model for vanilla call 
_Analytical_jdm_pricer_call(double Spot //spot
						,double Strike //strike
						,double r //interest rate
						,double d //dividend yield
						,double Vol0 //vol time 0
						,double Expiry //expiry
						,double kappa //kappa
						,double m //m
						,double nu //nu
){

	CallOption*  call = new CallOption(Spot, Strike, r, d, Vol0, Expiry);

	return analytical_jdm_pricer(Spot, Strike, r, d, Vol0, Expiry, kappa, m, nu, call);
}

double // evaluate quanto vanilla call under BSM
_QuantCallOption(double Spot //spot
				, double Strike //strike
				, double rd //interest rate of domestic currency
				, double rf //interest rate of foreign currency
				, double d //dvd yield
				, double VolS //vol stock price 
				, double VolQ //vol foreign currency
				, double correl //correl
				, double Expiry //expiry
){
	return QuantCallOption(Spot, Strike, rd, rf, d, VolS, VolQ, correl, Expiry);
}

double // evaluate quanto vanilla call under BSM
_QuantPutOption(double Spot //spot
				, double Strike //strike
				, double rd //interest rate of domestic currency
				, double rf //interest rate of foreign currency
				, double d //dvd yield
				, double VolS //vol stock price 
				, double VolQ //vol foreign currency
				, double correl //correl
				, double Expiry //expiry
){
	return QuantPutOption(Spot, Strike, rd, rf, d, VolS, VolQ, correl, Expiry);
}

double // evaluate Margrabe option under BSM 
_MargrabeOptions(double Spot1 //spot 1
				, double Spot2 //spot2
				, double Vol1 //vol1
				, double Vol2 //vol2
				, double correl // correl
				, double Expiry //expiry
){
	return MargrabeOptions(Spot1, Spot2, Vol1, Vol2, correl, Expiry);

}

double // evaluate Heston model for vanilla call 
_Analytical_heston_pricer_call(double mu //nu
							, double Spot //spot
							, double Vol //vol time 0
							, double r //interest rate
							, double kappa //kappa
							, double theta //theta
							, double sigma //sigma
							, double correl //rho correlation coef
							, double Strike //strike
							, double Expiry //expiry
){

	ParametersHeston p(mu, Spot, Vol, r, kappa, theta, sigma, correl, Strike, Expiry);

	return HestonVanillaCalltAnalytical(p);

}

double // evaluate VG model for vanilla call 
_Analytical_vg_call(double Spot //spot
					, double Strike //strike
					, double r //interest rate
					, double Expiry //expiry
					, double Vol //vol time 0
					, double nu //nu
					, double theta //theta
){

	return VGVanillaCallAnalytical(Spot, Strike, r, Expiry, Vol, nu, theta);

}

double //The premium for the down-and-Out put option	
_up_out_call(double Spot //spot
			, double Strike //strike
			, double Barrier //barrier
			, double r //interest rate
			, double d //dividend yield
			, double Vol //vol time 0
			, double Expiry //expiry
){
	return up_out_call(Spot, Strike, Barrier, r, d, Vol, Expiry);
}

double //The premium for the down-and-Out put option	
_up_out_put(double Spot //spot
			, double Strike //strike
			, double Barrier //barrier
			, double r //interest rate
			, double d //dividend yield
			, double Vol //vol time 0
			, double Expiry //expiry
){
	return up_out_put(Spot, Strike, Barrier, r, d, Vol, Expiry);
}

double //The premium for the down-and-Out call option	
_down_out_call(double Spot //spot
			, double Strike //strike
			, double Barrier //barrier
			, double r //interest rate
			, double d //dividend yield
			, double Vol //vol time 0
			, double Expiry //expiry
){
	return down_out_call(Spot, Strike, Barrier, r, d, Vol, Expiry);
}

double //The premium for the down-and-Out call option	
_down_out_put(double Spot //spot
			, double Strike //strike
			, double Barrier //barrier
			, double r //interest rate
			, double d //dividend yield
			, double Vol //vol time 0
			, double Expiry //expiry
){
	return down_out_put(Spot, Strike, Barrier, r, d, Vol, Expiry);
}