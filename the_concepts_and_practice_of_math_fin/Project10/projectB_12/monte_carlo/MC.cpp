#include <cmath>
#include <Arrays.h>
#include <Vanilla3.h>
#include <Parameters.h>
#include <MCStatistics.h>
#include <Random2.h>
#include "MC.h"

//Numéraire t1

void SimpleMonteCarloP1(const VanillaOption& TheOption,
	double Fwd,
	double t0,
	double t1,
	const Parameters& Vol,
	unsigned long NumberOfPaths,
	StatisticsMC& gatherer,
	RandomBase& generator)
{
	generator.ResetDimensionality(1);

	double Expiry = TheOption.GetExpiry();
	double variance = Vol.IntegralSquare(0, Expiry);
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double movedFwd = Fwd*exp(itoCorrection);

	double tau = t1 - t0;

	MJArray VariateArray(1);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		generator.GetGaussians(VariateArray);
		double thisFwd = movedFwd*exp(rootVariance*VariateArray[0]);
		double p1 = 1.0 / (1.0 + thisFwd*tau);
		double thisPayOff = TheOption.OptionPayOff(thisFwd);
		gatherer.DumpOneResult(10.0 * thisPayOff / p1);
	}


}

//Numéraire t0

void SimpleMonteCarloP2(const VanillaOption& TheOption,
	method m,
	double Fwd,
	double t0,
	double t1,
	const Parameters& Vol,
	unsigned long NumberOfPaths,
	StatisticsMC& gatherer,
	RandomBase& generator)
{
	generator.ResetDimensionality(1);

	double Expiry = TheOption.GetExpiry();
	double variance = Vol.IntegralSquare(0, Expiry);
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double tau = t1 - t0;
	double drift = (tau * Fwd) / (1.0 + tau*Fwd)*variance;

	MJArray VariateArray(1); MJArray VariateArray1(1);

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		generator.GetGaussians(VariateArray);

		double thisFwd = Fwd * exp(drift + itoCorrection + rootVariance*VariateArray[0]);

		if (m == PC){

			double drift1 = (tau * thisFwd) / (1.0 + tau*thisFwd)*variance;

			generator.GetGaussians(VariateArray1);

			thisFwd = Fwd * exp(.5 * drift + .5 * drift1 + itoCorrection + rootVariance*VariateArray1[0]);

		}

		double p1 = (1.0 + thisFwd * tau);
		double thisPayOff = TheOption.OptionPayOff(thisFwd);
		gatherer.DumpOneResult(10.0 * thisPayOff / p1);
	}


}