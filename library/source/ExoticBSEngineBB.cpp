//  ExoticBSEngineBB.cpp

//On the tractability of the Brownian Bridge algorithm, 2003, Leobacher, Scheicher
//p.8 - 11

#include <ExoticBSEngineBB.h>
#include <cmath>
#include <algorithm>
#include <cholesky.hpp>
//#include <invert_matrix.hpp>
#include <stochastic_term.h>

using namespace std;

void ExoticBSEngineBB::GetOnePath(MJArray& LogSpotValues)
{
	TheGenerator->GetGaussians(Variates);

	BrownianBridge bridge(times);

	bridge.transform(Variates.begin(),Variates.end(),out.begin());

	double CurrentLogSpot = LogSpot;

	for (unsigned long j=0; j < NumberOfTimes; j++){
		CurrentLogSpot += Drifts[j];
		CurrentLogSpot += StandardDeviations[j] * out[j];
		LogSpotValues[j] = CurrentLogSpot;
	}
}

ExoticBSEngineBB::ExoticBSEngineBB(const Wrapper<PathDependent>& TheProduct_,
									const Parameters& R_,
									const Parameters& D_,
									const Parameters& Vol_,
									const Wrapper<RandomBase>& TheGenerator_,
									double Spot_,
									bool speed_up_)
									:
									ExoticEngine(TheProduct_, R_, speed_up_),
									TheGenerator(TheGenerator_)
{
	NumberOfTimes = TheProduct_->GetLookAtTimes().size();

	if (speed_up == true)
		NumberOfTimes -= 1;

    times.resize(NumberOfTimes);
    out.resize(NumberOfTimes);

    for (unsigned long i(0); i < NumberOfTimes;++i)
		times[i] = TheProduct_->GetLookAtTimes()[i];

    TheGenerator->ResetDimensionality(NumberOfTimes);

    Drifts.resize(NumberOfTimes);
    StandardDeviations.resize(NumberOfTimes);

    Drifts[0] = R_.Integral(0.0,times[0]) - D_.Integral(0.0,times[0]) - 0.5 * Vol_.IntegralSquare(0.0,times[0]);
	StandardDeviations[0] = sqrt(Vol_.IntegralSquare(0.0, times[0]));

    for (unsigned long j=1; j < NumberOfTimes; ++j)
    {
        Drifts[j] = R_.Integral(times[j-1],times[j]) - D_.Integral(times[j-1],times[j])
			- 0.5 * Vol_.IntegralSquare(times[j-1],times[j]);
		StandardDeviations[j] = sqrt(Vol_.IntegralSquare(times[j - 1], times[j]));
    }

    LogSpot = std::log(Spot_);
    Variates.resize(NumberOfTimes);
    method_ = logscale;
}
