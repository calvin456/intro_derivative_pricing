/*
Exercise 7.4 Implement an engine for pricing when the spot price 
is normal instead of log-normal.


Re: Chapter 7, problem 4

Postby mj » Sun Jan 23, 2011 10:29 pm
in the Black-Scholes stock price increments are lognormal in any measure.

However, there are many other models.

The Bachelier model has normal increments.

*/

#ifndef EXOTIC_NORMAL_ENGINE_H
#define EXOTIC_NORMAL_ENGINE_H
#include <ExoticEngine.h>
#include <Random2.h>

class ExoticNormalEngine : public ExoticEngine
{
public:

      ExoticNormalEngine(const Wrapper<PathDependent>& TheProduct_,
                     const Parameters& R_,
                     const Parameters& D_,
                     const Parameters& Vol_,
                     const Wrapper<RandomBase>& TheGenerator_,
                     double Spot_);

      virtual void GetOnePath(MJArray& SpotValues);
      virtual ~ExoticNormalEngine(){}
 

private:

    Wrapper<RandomBase> TheGenerator;
    MJArray Drifts;
    MJArray StandardDeviations;
    double Spot;
    unsigned long NumberOfTimes;
    MJArray Variates;
};

#endif

