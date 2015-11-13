//path_generation_gbm_svm.cpp


#include <cmath>

#include <path_generation_gbm_svm.h>

using namespace std;

PathGenerationGBM_SV::PathGenerationGBM_SV(shared_ptr<RandomBase>& TheGenerator_,
																						double Spot0_,
																						double T_,
																						const Parameters& drift_,
																						matrix<double> vol_,
																						unsigned long steps_)
	: PathGeneration(TheGenerator_, Spot0_, T_, steps_), drift(drift_), vol(vol_)
{}

	double PathGenerationGBM_SV::GetOnePath(args& args_) const
	{
		double stock_spot = Spot0;
		double deltaT(T / steps);
		unsigned long i(0);

		for (size_t j(1); j < steps; ++j){
			TheGenerator->GetGaussians(args_[0]); //VariateArray  simul Gaussian variates

			while ((deltaT * i) <= vol(i,0)){
				stock_spot *= exp(drift.Integral(0, deltaT) - .5 * vol(i, 1) * vol(i, 1) * deltaT + vol(i, 1) * sqrt(deltaT) * args_[0][0]);
			}
			++i;
		}
		return stock_spot;
	}

MJArray PathGenerationGBM_SV::GetWholePath(args& args_)
{
	MJArray stock_path;
	stock_path.resize(steps + 1);
	stock_path[0] = Spot0;

	double deltaT(T / steps);
	//unsigned long i(0);

	TheGenerator->GetGaussians(args_[0]); 	//VariateArray  simul Gaussian variates

	for (size_t j(0); j < stock_path.size() - 1; ++j){

		//std::cout << args_[0][j] << "; ";

		//while ((deltaT * i) <= vol(j - 1, 0)){
			stock_path[j + 1] = stock_path[j] * exp(drift.Integral(0, deltaT) - .5 * vol(j, 1) * vol(j, 1) * deltaT
												+ vol(j, 1) * sqrt(deltaT) * args_[0][j]);
		//	++i;
		//}
		
	}
	return stock_path;
}
