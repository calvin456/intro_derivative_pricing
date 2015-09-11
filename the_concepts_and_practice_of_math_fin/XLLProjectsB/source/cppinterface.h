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

using namespace xlw;

//<xlw:libraryname=MyProjectLibrary

double // evaluate BlackScholes call price
_BlackScholesCall( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );


double // evaluate BlackScholes put price	
_BlackScholesPut( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );

double // evaluate BlackScholes digital call price
_BlackScholesDigitalCall(double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );

double // evaluate BlackScholes digital put price
_BlackScholesDigitalPut(double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );



							 
double // evaluate forward price
_Forward( double Spot //spot
							,double Strike //strike
                             ,double r //interest rate
                             ,double d //dividend yield
                             ,double Expiry //expiry
							 );

							 
double // evaluate forward price
_ZeroCoupon( double r //interest rate
								,double Expiry //expiry
								);



double // evaluate final price bsd on Euler stepping
_FinalPrice_EulerStepping(double Spot //spot
                         ,short Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );

double // evaluate BlackScholes call vega derivatives
_BlackScholesCallVega( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );

double // evaluate BlackScholes call delta derivatives
_BlackScholesCallDelta( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );

double // evaluate BlackScholes call gamma derivatives
_BlackScholesGamma( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );

double // evaluate BlackScholes call rho derivatives
_BlackScholesCallRho( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );

double // evaluate BlackScholes call rho derivatives
_BlackScholesCallTheta( double Spot //spot
                         ,double Strike //strike
                         ,double r //interest rate
                         ,double d //dividend yield
                         ,double Vol //volatility
                         ,double Expiry //expiry
						 );

double // evaluate implied volatility using BSM
_ImpliedVolatility( double Price //option price
					,double r //interest rate
					,double d //dividend yield
					,double Expiry //expiry
					,double Spot //spot
					,double Strike //strike
					, double Start //start vol. Set by default 20%
					, double Tolerance //tolerance. Set by default 1e-6
					);



double // evaluate jump diffusion model for vanilla call 
_Analytical_jdm_pricer_call(double Spot //spot
						, double Strike //strike
						, double r //interest rate
						, double d //dividend yield
						, double Vol0 //vol time 0
						, double Expiry //expiry
						, double kappa //kappa
						, double m //m
						, double nu //nu
						);

double // evaluate quanto vanilla call under BSM
_QuantCallOption(double Spot //spot
				,double Strike //strike
				,double rd //interest rate of domestic currency
				,double rf //interest rate of foreign currency
				,double d //dvd yield
				,double VolS //vol stock price 
				,double VolQ //vol foreign currency
				,double correl //correl
				,double Expiry //expiry
				);

double // evaluate quanto vanilla put under BSM
_QuantPutOption(double Spot //spot
				,double Strike //strike
				,double rd //interest rate of domestic currency
				,double rf //interest rate of foreign currency
				,double d //dvd yield
				,double VolS //vol stock price 
				,double VolQ //vol foreign currency
				,double correl //correl
				,double Expiry //expiry
				);

double // evaluate Margrabe option under BSM 
_MargrabeOptions(double Spot1 //spot 1
				,double Spot2 //spot2
				,double Vol1 //vol1
				,double Vol2 //vol2
				,double correl // correl
				,double Expiry //expiry
				);

double // evaluate Heston model for vanilla call 
_Analytical_heston_pricer_call(double mu //nu
						,double Spot //spot
						,double Vol //vol time 0
						,double r //interest rate
						,double kappa //kappa
						,double theta //theta
						,double sigma //sigma
						,double correl //rho correlation coef
						,double Strike //strike
						,double Expiry //expiry
						);

double // evaluate VG model for vanilla call 
_Analytical_vg_call(double Spot //spot
					, double Strike //strike
					, double r //interest rate
					, double Expiry //expiry
					, double Vol //vol time 0
					, double nu //nu
					, double theta //theta
					);
					 
double //The premium for the Up-and-Out call option	
_up_out_call(double Spot //spot
			, double Strike //strike
			, double Barrier //barrier
			, double r //interest rate
			, double d //dividend yield
			, double Vol //vol time 0
			, double Expiry //expiry
			);

double //The premium for the Up-and-Out call option	
_up_out_put(double Spot //spot
			, double Strike //strike
			, double Barrier //barrier
			, double r //interest rate
			, double d //dividend yield
			, double Vol //vol time 0
			, double Expiry //expiry
			);

double //The premium for the down-and-Out call option	
_down_out_call(double Spot //spot
			, double Strike //strike
			, double Barrier //barrier
			, double r //interest rate
			, double d //dividend yield
			, double Vol //vol time 0
			, double Expiry //expiry
			);

double //The premium for the down-and-Out call option	
_down_out_put(double Spot //spot
			, double Strike //strike
			, double Barrier //barrier
			, double r //interest rate
			, double d //dividend yield
			, double Vol //vol time 0
			, double Expiry //expiry
			);

#endif
