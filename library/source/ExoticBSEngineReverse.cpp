//  ExoticBSEngineReverse.cpp

//On the tractability of the Brownian Bridge algorithm, 2003, Leobacher, Scheicher
//p.8 - 11


#include <cmath>
#include <algorithm>

#include <boost\numeric\ublas\matrix.hpp>
//#include <boost\numeric\ublas\lu.hpp>
//#include <boost\numeric\ublas\io.hpp>

#include <ExoticBSEngineReverse.h>
#include <stochastic_term.h>

using namespace std;
using namespace boost::numeric::ublas;

void ExoticBSEngineReverse::GetOnePath(MJArray& LogSpotValues)
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

ExoticBSEngineReverse::ExoticBSEngineReverse(const Wrapper<PathDependent>& TheProduct_,
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

    Matrix C(NumberOfTimes, NumberOfTimes);

	/*
    for (size_t i(0); i < NumberOfTimes; ++i)
      for (size_t j(0); j < NumberOfTimes; ++j)
        C[i][j] = max(Times[i],Times[j]);
	*/

	for (size_t i(0); i < NumberOfTimes; ++i){
		for (size_t j(0); j < NumberOfTimes; ++j)
			C[i][j] = TheProduct_->GetLookAtTimes()[j];
	}

	for (size_t j(1); j <NumberOfTimes; ++j){
		for (size_t i(0); i < j; ++i)
			C[i][j] = TheProduct_->GetLookAtTimes()[i];
	}


	//std::cout << C << endl;

    //Permutation matrix - reverse row order last row becoming the first one
    Matrix P(NumberOfTimes, NumberOfTimes);

	for (size_t i(0); i < NumberOfTimes; ++i)
		for (size_t j(0); j < NumberOfTimes; ++j)
			P[i][j] = 0.0;

	for (size_t i(0);i < NumberOfTimes;++i)
		P[NumberOfTimes - 1 - i][i] = 1.0;

	//std::cout << P << endl;

	//Matrix Pinv = inverse(P);

	//Inverse of permutation matrix Pinv = P

	//std::cout << Pinv << endl;

    Matrix D = P * C * P;

	//std::cout << D << endl;

	Matrix E = CholeskyDecomposition(D);

	Matrix F = P * E;

	/*
	//Implement via LU decomposition. Resulting matrix not symmetric

	std::copy(D.begin(), D.end(), A.begin2());

	permutation_matrix<Size> pert(A.size1());

	const Size singular = lu_factorize(A, pert); //overwrite A. Final A contains both L and U triangle
	QL_REQUIRE(singular == 0, "singular matrix given");

	for (size_t i(0); i < NumberOfTimes; ++i)
		for (size_t j(0); j < NumberOfTimes; ++j)
			A(i, j) = P[i][j] * A(i, j);
	*/
    
	std::copy(F.begin(), F.end(), A.begin2());

	//std::cout << A << endl;

}
