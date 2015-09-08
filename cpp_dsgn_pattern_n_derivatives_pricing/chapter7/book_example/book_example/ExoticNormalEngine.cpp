/*
The Bachelier model

dSt = nu * dt + sigma * dWt, Wt Weiner process : sqrt(t)*norm(0,1)

nu = r - d

Price can become negative. Not suitable for stocks  -> GBM.

*/

#include <ExoticNormalEngine.h>
#include <cmath>


using namespace std;

void ExoticNormalEngine::GetOnePath(MJArray& SpotValues) 
{

    TheGenerator->GetGaussians(Variates);

    double CurrentSpot = Spot;

    for (unsigned long j=0; j < NumberOfTimes; j++)
    {
        CurrentSpot += Drifts[j];
        CurrentSpot += StandardDeviations[j]*Variates[j];
        SpotValues[j] = CurrentSpot;
    }

    return;
}

ExoticNormalEngine::ExoticNormalEngine(const Wrapper<PathDependent>& TheProduct_,
                                    const Parameters& R_,
                                    const Parameters& D_,
                                    const Parameters& Vol_,
                                    const Wrapper<RandomBase>& TheGenerator_,
                                    double Spot_)
                                    :
                                    ExoticEngine(TheProduct_,R_),
                                    TheGenerator(TheGenerator_)
{
    MJArray Times(TheProduct_->GetLookAtTimes());
    NumberOfTimes = Times.size();

    TheGenerator->ResetDimensionality(NumberOfTimes);

    Drifts.resize(NumberOfTimes);
    StandardDeviations.resize(NumberOfTimes);

    double Variance = Vol_.IntegralSquare(0,Times[0]);

    Drifts[0] = R_.Integral(0.0,Times[0]) - D_.Integral(0.0,Times[0]);
    StandardDeviations[0] = sqrt(Variance);

    for (unsigned long j=1; j < NumberOfTimes; ++j)
    {   
        double thisVariance = Vol_.IntegralSquare(Times[j-1],Times[j]);
        Drifts[j] = R_.Integral(Times[j-1],Times[j]) - D_.Integral(Times[j-1],Times[j]);
        StandardDeviations[j] = sqrt(thisVariance);
    }

    Spot = Spot_;                                   
    Variates.resize(NumberOfTimes);
}




