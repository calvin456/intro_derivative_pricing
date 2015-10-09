//main.cpp

//Implement analytical heston pricer for vanilla option and various mc pricer for vanillas

#include <iostream>
#include <analytical_jdm_pricer.h>
#include <BlackScholesFormulas.h>
#include <path_generation.h>
#include <path_generation_jdp.h>
#include <options.h>
#include <PayOff3.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <MCStatistics.h>
#include <ConvergenceTable.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>
#include <engine_jdp.h>

using namespace std;
using namespace MyOption;

int main(){
	try {

		double Spot(100.0);
		double Strike(100.0);
		double r(0.05);
		double d(0.0);
		double Vol(.1);
		double kappa(0.2);
		double m(.9);
		double nu(.1);
		double Expiry(.25);

		CallOption*  call = new CallOption(Spot, Strike, r, d, Vol, Expiry);

		double result;

		result = analytical_jdm_pricer(Spot, Strike, r, d, Vol, Expiry, kappa, m, nu, call);

		cout << "BSM value : " << endl;
		cout << call->GetValue(Spot, Vol, Expiry) << endl;

		cout << "jump diffusion model : " << endl;
		cout << result << endl;
		//---------------------------------------------------------------------------
		//use of mc pricer with template class

		PayOffCall thePayOff(Strike);

		//create template vanilla option class
		VanillaOptionTemplate<PayOffCall> theOption(thePayOff, Expiry);

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant driftParam(r - d);
		//---------------------------------------------------------------------------
		//mc pricing

		// (i) short-step the vol and the spot

		StatisticsMean gatherer_mean;
		StatisticsSE gatherer_se;

		vector<Wrapper<StatisticsMC>> stat_vec;
		stat_vec.resize(2);
		stat_vec[0] = gatherer_mean;
		stat_vec[1] = gatherer_se;
		StatsGatherer gathererOne(stat_vec);

		ConvergenceTable gatherer(gathererOne);

		StatisticsKeepTrack _gatherer_time;

		ConvergenceTable gatherer_time(_gatherer_time);

		//shared_ptr<RandomBase> generator(new RandomMersenneTwister(1));
		
		RandomMersenneTwister generator_(1);
		//RandomParkMiller generator_(1);

		shared_ptr<RandomBase> generator(new AntiThetic(generator_));

		unique_ptr<PathGenerationJDP> ThePath(new PathGenerationJDP(generator, Spot, Expiry, driftParam, VolParam, kappa, m, nu, 1));

		unsigned long NumberOfPaths(static_cast<unsigned long> (1e06)); //1e04

		mc_pricer_jdp(theOption, rParam, ThePath, NumberOfPaths, gatherer, gatherer_time);

		vector<vector<double> > results = gatherer.GetResultsSoFar();
		vector<vector<double> > results1 = gatherer_time.GetResultsSoFar();

		cout << "jdp mc pricing : " << endl;
		cout << "short-step the vol and the spot" << endl;
		cout << "\nFor the vanilla call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << "\t ";

			cout << results1[i][0] << "\t ";
			cout << "\n";


		}
		cout << endl;
		//---------------------------------------------------------------------------

		
		double tmp;
		cin >> tmp;

		return 0;

	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error" << endl;
		return 1;
	}

}