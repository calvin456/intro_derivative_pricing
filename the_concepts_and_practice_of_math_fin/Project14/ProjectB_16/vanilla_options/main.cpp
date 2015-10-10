//main.cpp

//Implement analytical vg pricer for vanilla option and various mc pricer for vanillas

#include <iostream>
#include <VGPricingAnalytical.h>
#include <path_generation_vg.h>
#include <PayOff3.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <MCStatistics.h>
#include <ConvergenceTable.h>
#include <MersenneTwister.h>
#include <Random2.h>
#include <AntiThetic.h>
#include <Engine_vg.h>
#include <Terminator.h>

using namespace std;

int main(){
	try {

		//ATM 3-mth vanilla call
		double Spot(100.0);
		double Strike(100.0);
		double r(.05);
		double d(0.0);
		double Expiry(.25);
		double Vol(.1);
		double nu(.2);
		double theta(0);

		cout << "vg vanilla call price : " << endl;
		cout << VGVanillaCallAnalytical(Spot, Strike, r, Expiry, Vol, nu, theta) << endl;

		cout << "vg vanilla put price : " << endl;
		cout << VGVanillaPutAnalytical(Spot, Strike, r, Expiry, Vol, nu, theta) << endl;

		//-----------------------------------------------------------------------------------
		//use of mc pricer with template class

		PayOffCall thePayOff(Strike);

		//create template vanilla option class
		VanillaOptionTemplate<PayOffCall> theOption(thePayOff, Expiry);

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant driftParam(r - d);
		//---------------------------------------------------------------------------
		//mc pricing

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

		RandomMersenneTwister generator_(1);
		//RandomParkMiller generator_(1);

		shared_ptr<RandomBase> generator(new AntiThetic(generator_));

		unsigned long steps(static_cast<unsigned long> (1e01));

		unique_ptr<PathGenerationVG> ThePath(new PathGenerationVG(generator, Spot, Expiry, driftParam, VolParam, nu, theta, steps));

		unsigned long NumberOfPaths(static_cast<unsigned long> (1e6));

		mc_pricer_vg(theOption, rParam, ThePath, NumberOfPaths, gatherer, gatherer_time);

		vector<vector<double> > results = gatherer.GetResultsSoFar();
		vector<vector<double> > results1 = gatherer_time.GetResultsSoFar();

		cout << "vg mc pricing : " << endl;
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