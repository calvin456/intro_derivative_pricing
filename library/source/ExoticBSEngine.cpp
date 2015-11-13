//
//
//
//                      ExoticBSEngine.cpp
//
//

//Edit to account for change log vs level value

#include <ExoticBSEngine.h>
#include <cmath>


using namespace std;

void ExoticBSEngine::GetOnePath(MJArray& LogSpotValues)
{

    TheGenerator->GetGaussians(Variates);

    double CurrentLogSpot = LogSpot;

    for (unsigned long j=0; j < NumberOfTimes; j++)
    {
        CurrentLogSpot += Drifts[j];
        CurrentLogSpot += StandardDeviations[j]*Variates[j];
		LogSpotValues[j] = CurrentLogSpot;
    }

    return;
}

ExoticBSEngine::ExoticBSEngine(const Wrapper<PathDependent>& TheProduct_,
                                    const Parameters& R_,
                                    const Parameters& D_,
                                    const Parameters& Vol_,
                                    const Wrapper<RandomBase>& TheGenerator_,
                                    double Spot_,
									bool speed_up_)
                                    :
                                    ExoticEngine(TheProduct_,R_,speed_up_),
                                    TheGenerator(TheGenerator_)
{
    MJArray Times(TheProduct_->GetLookAtTimes());
    NumberOfTimes = Times.size();
	if (speed_up == true)	
		NumberOfTimes -= 1;

    TheGenerator->ResetDimensionality(NumberOfTimes);

    Drifts.resize(NumberOfTimes);
    StandardDeviations.resize(NumberOfTimes);

    double Variance = Vol_.IntegralSquare(0,Times[0]);

    Drifts[0] = R_.Integral(0.0,Times[0]) - D_.Integral(0.0,Times[0]) - 0.5 * Variance;
    StandardDeviations[0] = sqrt(Variance);

    for (unsigned long j=1; j < NumberOfTimes; ++j)
    {
        double thisVariance = Vol_.IntegralSquare(Times[j-1],Times[j]);
        Drifts[j] = R_.Integral(Times[j-1],Times[j]) - D_.Integral(Times[j-1],Times[j])
                    - 0.5 * thisVariance;
        StandardDeviations[j] = sqrt(thisVariance);
    }

    LogSpot = std::log(Spot_);
    Variates.resize(NumberOfTimes);
    method_ = logscale;
}


/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/
