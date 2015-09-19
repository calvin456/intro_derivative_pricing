#include <iostream>
#include <cmath>

#include <Normals.h>
#include <Parameters.h>
#include <Arrays.h>
#include <MersenneTwister.h>
#include <ParkMiller.h>
#include <Sobol.h>
#include <AntiThetic.h>
#include <BlackScholesFormulas.h>
#include <path_generation_gbm.h>
#include <engine_vanilla.h>
#include <engine_vanilla_lr.h>
#include <Vanilla3Template.cpp>
#include <MCStatistics.h>
#include <ConvergenceTable.h>
#include <Digital.h>

using namespace std;

int main(){

	try{

		double Spot(100);
		double Strike(100);
		double r(.01);
		double d(.03);
		double Vol(.30);
		double Expiry(.33);

		cout << "call atm" << endl;

		double delta = BlackScholesCallDelta(Spot, Strike, r, d, Vol, Expiry);

		double gamma = BlackScholesGamma(Spot, Strike, r, d, Vol, Expiry);

		cout << "analytical formula delta: " << delta << endl;

		double epsilon(1e-4);

		//finite difference approx
		double delta_fd = (1 / epsilon) * (BlackScholesCall(Spot + epsilon, Strike, r, d, Vol, Expiry) -
			BlackScholesCall(Spot, Strike, r, d, Vol, Expiry));

		cout << "finite difference formula delta: " << delta_fd << endl;

		cout << "perc diff : " << fabs(1 - delta / delta_fd) * 100 << endl;

		cout << endl;

		cout << "analytical formula gamma: " << gamma << endl;

		epsilon = 1e-2;

		//finite difference approx
		double gamma_fd = (1 / (epsilon* epsilon)) * (BlackScholesCall(Spot + epsilon, Strike, r, d, Vol, Expiry) -
			2.0 *BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) +
			BlackScholesCall(Spot - epsilon, Strike, r, d, Vol, Expiry));

		cout << "finite difference formula delta: " << gamma_fd << endl;

		cout << "perc diff : " << fabs(1 - delta / delta_fd) * 100 << endl;

		//-------------------------------------------------------------------
		//MC Greeks
		PayOffCall thePayOff(Strike);

		VanillaOptionTemplate<PayOffCall> theOption(thePayOff, Expiry);

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant driftParam(r - d);

		unsigned long NumberOfPaths(static_cast<unsigned long>(1e5));

		RandomParkMiller rng_pm(1);

		RandomBase* anti_pm_gen(new AntiThetic(rng_pm));

		shared_ptr<PathGeneration> thePath(new PathGenerationGBM(anti_pm_gen, Spot, Expiry,
			driftParam, VolParam, 1));

		cout << " Monte Carlo Greeks" << endl;
		cout << "Delta" << endl;

		cout << "Finite difference method : " << endl;

		double mc_pm1 = mc_pricer_vanilla(theOption, rParam, thePath, NumberOfPaths);

		// (i) Finite difference method. Use 2 separate RNGs
		cout << "2 RNGs - Park Miller & Mersenne Twister" << endl;

		RandomMersenneTwister rng_mt(1);

		RandomBase* anti_mt_gen(new AntiThetic(rng_pm));

		shared_ptr<PathGeneration> thePath1(new PathGenerationGBM(anti_mt_gen, Spot, Expiry,
			driftParam, VolParam, 1));

		double mc_mt = mc_pricer_vanilla(theOption, rParam, thePath1, NumberOfPaths);

		cout << (1 / epsilon) * (mc_mt - mc_pm1) << endl;

		cout << "2 RNGs - Park Miller & Sobol" << endl;

		RandomBase* rng_sobol(new RandomSobol(1));

		shared_ptr<PathGeneration> thePath2(new PathGenerationGBM(rng_sobol, Spot + epsilon, Expiry,
			driftParam, VolParam, 1));

		double mc_sobol = mc_pricer_vanilla(theOption, rParam, thePath2, NumberOfPaths);

		cout << (1 / epsilon) * (mc_sobol - mc_pm1) << endl;

		// (ii)  Finite difference method. Sme RNG - ParkMiller
		cout << "sme RNG - Park Miller" << endl;

		shared_ptr<PathGeneration> thePath3(new PathGenerationGBM(anti_pm_gen, Spot + epsilon, Expiry,
			driftParam, VolParam, 1));

		double mc_pm2 = mc_pricer_vanilla(theOption, rParam, thePath3, NumberOfPaths);

		cout << (1 / epsilon) * (mc_pm2 - mc_pm1) << endl;

		
		// (iii) Implement the pathwise method for the delta
		cout << "pathwise method : ";
		cout << pathwise_mc_delta(theOption, rParam, thePath, NumberOfPaths) << endl;
		
		// (iv) Implement the likelihood ratio method for the delta
		cout << "likelihood ratio method :";

		shared_ptr<PathGenerationGBM> thePath4(new PathGenerationGBM(anti_pm_gen, Spot + epsilon, Expiry,
			driftParam, VolParam, 1));

		cout << l_ratio_mc_delta(theOption, rParam, thePath4, NumberOfPaths) << endl;
		
		double tmp;
		cin >> tmp;

		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "unknown error" << std::endl;
		return 1;
	}



}