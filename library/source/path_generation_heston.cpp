//path_generation_heston.cpp

#include <path_generation_heston.h>
#include <algorithm>

using namespace std;
using namespace QuantLib;

PathGenerationHeston::PathGenerationHeston(shared_ptr<RandomBase> TheGenerator_,
											double Spot0_,
											double T_,
											const Parameters& drift_,
											const Parameters& vol_,
											unsigned long steps_,
											double correl_,
											double kappa_,
											double epsilon_ )
	:PathGeneration(TheGenerator_, Spot0_, T_, steps_), drift(drift_), vol(vol_), correl(correl_),
		kappa(kappa_), epsilon(epsilon_)
{
	vol_path.resize(steps + 1);
	vol_path[0] = vol.IntegralSquare(0.0, 1.0);
	TheGenerator->ResetDimensionality(steps);
}

PathGenerationHeston::PathGenerationHeston(shared_ptr<RandomBase> TheGenerator_,
											double Spot0_,
											double T_,
											const Parameters& drift_,
											const Parameters& vol_,
											unsigned long steps_, //steps stock path
											unsigned long steps1_,  //steps volatility process
											double correl_,
											double kappa_,
											double epsilon_)
:PathGeneration(TheGenerator_, Spot0_, T_, steps_),
drift(drift_), vol(vol_), correl(correl_), kappa(kappa_), epsilon(epsilon_), steps1(steps1_)
{
	vol_path.resize(steps + 1);
	vol_path[0] = vol.IntegralSquare(0.0, 1.0);
	TheGenerator->ResetDimensionality(steps);
}

//ref. Leif Andersen, Efficient simul of heston stoch vol model, 2006
//ref. T. Odelman, Efficient MC sim with stochastic vol, KTH Computer Science and Communication, 2009

double PathGenerationHeston::GetOnePath(args& args_) const {

	double stock_spot(Spot0);

	double deltaT(T / steps);
	double _drift(drift.Integral(0, deltaT));

	TheGenerator->GetGaussians(args_[0]);
	TheGenerator->GetGaussians(args_[1]);

	/*
	//Euler scheme
	for(size_t i(0);i < vol_path.size()-1;++i){

	//Generate correl normal var
	//zv = variate array 1
	double z_x(correl * VariateArray1[i] + sqrt(1.0 - correl*correl) * VariateArray2[i]); //zx


	//truncated distr. Only take positive part of distr.
	vol_t = max(vol_path[i],0); sqrt_vol_t = sqrt(vol_t * deltaT);

	vol_path[i+1] = vol_path[i] + kappa * (_vol - vol_t * deltaT) + epsilon * sqrt_vol_t * VariateArray1[i];

	stock_path[i+1] = stock_path[i] * exp(_drift- .5 * vol_t * deltaT + sqrt_vol_t *  z_x);

	}
	*/

	//stochastic volatility proces - Heston
	double vol_t = vol.IntegralSquare(0.0, 1.0);
	double sqrt_vol_t = sqrt(vol_t);

	double vol_path = vol_t;

	//Milstein scheme
	double a(kappa * vol_t * deltaT);
	double b(kappa * deltaT);
	double c(epsilon * sqrt(deltaT));
	double d(.25*epsilon*epsilon*deltaT);
	double e(.5 * deltaT);

	for (size_t i(0); i < steps; ++i){

		//Generate correl normal var
		//zv = variate array 1
		double z_x(correl * args_[0][i] + sqrt(1.0 - correl*correl) * args_[1][i]); //zx

		double tmp(args_[0][i] * args_[0][i] - 1.0);

		stock_spot *= exp(_drift - e * max(vol_path, 0.0) + sqrt(max(vol_path, 0.0) * deltaT) * args_[0][i]);

		vol_path  +=  a - b * max(vol_path,0.0) + c * sqrt(max(vol_path,0.0)) * z_x + d * tmp;

	}

	return stock_spot;
}

double PathGenerationHeston::GetOnePathLS(args& args_)  {

	double stock_spot = Spot0;
	double deltaT(T / steps);

	double vol(sqrt(GetOnePathVol(args_)));

	double a(drift.Integral(0,deltaT) - .5 * vol * vol * deltaT);
	double b(vol * sqrt(deltaT));

	for (size_t i(0); i < steps; ++i)
		stock_spot *= exp(a + b *args_[0][i]);

	return stock_spot;
}

MJArray PathGenerationHeston::GetWholePath(args& args_){

	MJArray stock_path(steps + 1);
	
	vol_path.resize(steps + 1);
	vol_path[0] = vol.IntegralSquare(0.0, 1.0);

	double deltaT(T / steps);
	double _drift(drift.Integral(0, deltaT));

	TheGenerator->GetGaussians(args_[0]);
	TheGenerator->GetGaussians(args_[1]);

	stock_path[0] = Spot0;

	//stochastic volatility proces - Heston
	double vol_t = vol.IntegralSquare(0.0, 1.0);
	double sqrt_vol_t = sqrt(vol_t);

	//Milstein scheme
	double a(kappa * sqrt_vol_t * deltaT);
	double b(kappa * deltaT);
	double c(epsilon * sqrt(deltaT));
	double d(.25*epsilon*epsilon*deltaT);
	double e(.5 * deltaT);

	for (size_t i(0); i < vol_path.size() - 1; ++i){

		//Generate correl normal var
		//zv = variate array 1
		double z_x(correl * args_[0][i] + sqrt(1.0 - correl*correl) * args_[1][i]); //zx

		double tmp(args_[0][i] * args_[0][i] - 1.0);

		vol_path[i + 1] = vol_path[i] + a - b * max(vol_path[i],0.0)  + c * sqrt(max(vol_path[i],0.0)) * z_x + d * tmp;

		stock_path[i + 1] = stock_path[i] * exp(_drift - e * max(vol_path[i],0.0) +  sqrt(max(vol_path[i],0.0) * deltaT) * args_[0][i]);

	}

	return stock_path;
}

double PathGenerationHeston::rms_sigma(size_t  s, size_t t) const {

	double sum_sq(0.0);

	for (size_t i(s); i <= t; ++i){
		double tmp(vol_path[i] * vol_path[i]);
		sum_sq += tmp;
	}

	return sqrt(1.0 / (t - s) * sum_sq);
}



double PathGenerationHeston::GetOnePathVol(args& args_) {

	double deltaT(T / steps);

	TheGenerator->GetGaussians(args_[0]);
	TheGenerator->GetGaussians(args_[1]);

	//stochastic volatility proces - Heston
	double vol_t = vol.IntegralSquare(0.0, 1.0);
	double sqrt_vol_t = sqrt(vol_t);

	//Milstein scheme

	double a(kappa * sqrt_vol_t * deltaT);
	double b(kappa * deltaT);
	double c(epsilon * sqrt(deltaT));
	double d(.25*epsilon*epsilon*deltaT);

	for (size_t i(0); i < vol_path.size() - 1; ++i){

		//Generate correl normal var
		//zv = variate array 1
		double z_x(correl * args_[0][i] + sqrt(1.0 - correl*correl) * args_[1][i]); //zx

		double tmp(args_[0][i] * args_[0][i] - 1.0);

		vol_path[i + 1] = vol_path[i] + a - max(vol_path[i],0.0) * b + c * sqrt(max(vol_path[i],0.0)) * z_x + d * tmp;

	}

	return rms_sigma(0,vol_path.size()-1);

}

//Taken from Intro to selected classes of the quantlib library 2, Dimitri Reiswich, 2010, p. 139-144
// available at quantlib.org
//Use Quadratic Exponential scheme

MJArray PathGenerationHeston::GetWholePathInstant(args& args_){

	MJArray stock_path(steps + 1);

	vol_path.resize(steps + 1);

	double deltaT(T / steps);

	Date refDate = Date(1, Jan, 2000);
	Rate riskFreeRate = drift.Integral(0, 1);
	Rate dividendRate=0.0;
	Real spot=Spot0;
	Rate _vol = sqrt(vol.IntegralSquare(0.0, 1.0));

	DayCounter dc = ActualActual();

	boost::shared_ptr<YieldTermStructure> rdStruct(new FlatForward(refDate,riskFreeRate,dc));
	boost::shared_ptr<YieldTermStructure> rqStruct(new FlatForward(refDate,dividendRate,dc));
	Handle<YieldTermStructure> rdHandle(rdStruct);
	Handle<YieldTermStructure> rqHandle(rqStruct);

	boost::shared_ptr<SimpleQuote> spotQuote(new SimpleQuote(spot));
	Handle<Quote> spotHandle(spotQuote);

	boost::shared_ptr<HestonProcess> hestonProcess(new HestonProcess(rdHandle, rqHandle, spotHandle, _vol,
		kappa, _vol, epsilon, correl, HestonProcess::QuadraticExponential));

	/*
	PartialTruncation, FullTruncation, Reflection, NonCentralChiSquareVariance,
	QuadraticExponential, QuadraticExponentialMartingale, BroadieKayaExactSchemeLobatto, BroadieKayaExactSchemeLaguerre,
	BroadieKayaExactSchemeTrapezoidal
	*/

	Array x(2), dw(2);
	vol_path[0] = _vol; x[1] = _vol;
	stock_path[0] = Spot0; x[0] = Spot0;

	Time dt=deltaT,t=0.0;

	for (size_t i(0); i < vol_path.size() - 1; ++i){
		TheGenerator->GetGaussians(args_[0]); dw[0] = args_[0][0];
		TheGenerator->GetGaussians(args_[1]); dw[1] = args_[1][0];
		x=hestonProcess->evolve(t,x,dt, dw);
		vol_path[i + 1] = x[1];
		stock_path[i + 1] = x[0];
	}

	return stock_path;
}
