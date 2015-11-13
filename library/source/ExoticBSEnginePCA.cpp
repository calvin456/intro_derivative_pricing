//  ExoticBSEnginePCA.cpp

//ref. p.226-231, the concepts and practice of math fin

#include <ExoticBSEnginePCA.h>
#include <cmath>
#include <algorithm>
#include <stochastic_term.h>

using namespace std;
using namespace QuantLib;

void ExoticBSEnginePCA::GetOnePath(MJArray& LogSpotValues)
{
    TheGenerator->GetGaussians(Variates);
    MJArray tmp = StochasticTerm(A, Variates);

    double CurrentLogSpot = LogSpot;

    for (unsigned long j=0; j < NumberOfTimes; j++){
        CurrentLogSpot += Drifts[j];
        CurrentLogSpot += StandardDeviations[j] * tmp[j];
		LogSpotValues[j] = CurrentLogSpot;
    }
}

ExoticBSEnginePCA::ExoticBSEnginePCA(const Wrapper<PathDependent>& TheProduct_,
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
    A.resize(NumberOfTimes, NumberOfTimes);

    //double Variance = Vol_.IntegralSquare(0,1);

    Drifts[0] = R_.Integral(0.0,Times[0]) - D_.Integral(0.0,Times[0]) - 0.5 * Vol_.IntegralSquare(0.0,Times[0]);
	StandardDeviations[0] = sqrt(Vol_.IntegralSquare(0.0, 1.0));

    for (unsigned long j=1; j < NumberOfTimes; ++j)
    {
        //double thisVariance = Vol_.IntegralSquare(0,1);
        Drifts[j] = R_.Integral(Times[j-1],Times[j]) - D_.Integral(Times[j-1],Times[j])
                    - 0.5 * Vol_.IntegralSquare(Times[j-1],Times[j]);
		StandardDeviations[j] = sqrt(Vol_.IntegralSquare(0.0, 1.0));
    }

    LogSpot = std::log(Spot_);
    Variates.resize(NumberOfTimes);
    method_ = logscale;

    //--------------------------------------------------------------------------------
	//PCA. Use Schur decomposition implemented as in QL C =UDU'
	//Eigen values and eigen vector are already sorted
	//To get principal component ui * di

	Matrix C(NumberOfTimes, NumberOfTimes);
	
	/*
	for (size_t i(0); i < NumberOfTimes; ++i)
		for (size_t j(0); j < NumberOfTimes; ++j)
			C[i][j] =  min(Times[i],Times[j]);
	*/

	for (size_t i(0); i < NumberOfTimes; ++i){
		for (size_t j(0); j < NumberOfTimes; ++j)
			C[i][j] = TheProduct_->GetLookAtTimes()[j];
	}
	

	for (size_t j(1); j <NumberOfTimes; ++j){
		for (size_t i(0); i < j; ++i)
			C[i][j] = TheProduct_->GetLookAtTimes()[i];
	}



	SymmetricSchurDecomposition SymDec(C);

	Matrix D(NumberOfTimes, NumberOfTimes);

	for (size_t i(0); i < NumberOfTimes; ++i)
		for (size_t j(0); j < NumberOfTimes; ++j)
			D[i][j] = SymDec.eigenvectors()[i][j] * sqrt(SymDec.eigenvalues()[j]);

	std::copy(D.begin(),D.end(),A.begin2());

}
