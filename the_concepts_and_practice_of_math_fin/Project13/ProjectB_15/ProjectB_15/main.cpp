//main.cpp

//Implement analytical heston pricer for vanilla option and various mc pricer for vanillas

#include <iostream>
#include <HestonPricingAnalytical.h>
#include <BlackScholesFormulas.h>
#include <path_generation.h>
#include <path_generation_heston.h>
#include <PayOff3.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <MCStatistics.h>
#include <ConvergenceTable.h>
#include <MersenneTwister.h>
#include <AntiThetic.h>
#include <engine_heston.h>

using namespace std;

int main(){
	try {

		//ATM 3-mth option

		/*double mu, .05
		double Spot, 100
		double Vol, .1
		double r, .05
		double kappa, 0
		double theta, .1
		double sigma, .05
		double correl, 0
		double Strike, 100
		double Expiry .25
		*/

		ParametersHeston p(0.05, 100.0, .1, 0.05, 0, 0.1, .05, 0, 100.0, .25);

		double Spot(p.GetSpot());
		double Strike(p.GetStrike());
		double r(p.GetRate());
		double d(0.0);
		double Vol(p.GetVol());
		double kappa(p.GetKappa());
		double Expiry(p.GetExpiry());
		double correl(p.GetCorrel());

		cout << "Heston vanilla call : " << HestonVanillaCalltAnalytical(p) << endl;

		cout << "Heston vanilla put : " << HestonVanillaPutAnalytical(p) << endl;

		cout << "BSM vanilla call : " << BlackScholesCall(p.GetSpot(),
			p.GetStrike(), p.GetRate(), 0.0, p.GetVol(), p.GetExpiry()) << endl;

		cout << "BSM vanilla put : " << BlackScholesPut(p.GetSpot(),
			p.GetStrike(), p.GetRate(), 0.0, p.GetVol(), p.GetExpiry()) << endl;

		cout << endl;
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

		RandomMersenneTwister generator_(1);
		//RandomParkMiller generator_(1);

		shared_ptr<RandomBase> generator(new AntiThetic(generator_));

		unsigned long steps(static_cast<unsigned long> (1e1));

		unique_ptr<PathGenerationHeston> ThePath(new PathGenerationHeston(generator, Spot, Expiry, driftParam, VolParam, steps, correl, kappa, 0.05));

		unsigned long NumberOfPaths(static_cast<unsigned long> (1e6));

		mc_pricer_heston(theOption, rParam, ThePath, NumberOfPaths, gatherer, gatherer_time);

		vector<vector<double> > results = gatherer.GetResultsSoFar();
		vector<vector<double> > results1 = gatherer_time.GetResultsSoFar();

		cout << "heston mc pricing : " << endl;
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

		// (ii) short-step the vol, compute rms vol for the path and long-step the spot

		steps = static_cast<unsigned long> (1e0);

		unsigned long steps1(static_cast<unsigned long> (1e1));

		unique_ptr<PathGenerationHeston> ThePath1(new PathGenerationHeston(generator, Spot, Expiry, driftParam, VolParam, steps, steps1, correl, kappa, 0.05));

		ConvergenceTable gatherer1(gathererOne);

		StatisticsKeepTrack _gatherer_time1;

		ConvergenceTable gatherer_time1(_gatherer_time1);

		mc_pricer_heston_ls(theOption, rParam, ThePath1, NumberOfPaths, gatherer1, gatherer_time1);

		vector<vector<double> > results2 = gatherer1.GetResultsSoFar();
		vector<vector<double> > results3 = gatherer_time1.GetResultsSoFar();

		cout << "heston mc pricing : " << endl;
		cout << "short-step the vol and long-step the spot" << endl;
		cout << "\nFor the vanilla call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results2.size(); i++)
		{
			for (unsigned long j = 0; j < results2[i].size(); j++)
				cout << results2[i][j] << "\t ";

			cout << results3[i][0] << "\t ";
			cout << "\n";
		}
		cout << endl;

		//---------------------------------------------------------------------------

		// (iii) short-step the vol, compute rms vol for the path and plug it into BSM formula

		unique_ptr<PathGenerationHeston> ThePath2(new PathGenerationHeston(generator, Spot, Expiry, driftParam, VolParam, steps, steps1, correl, kappa, 0.05));

		ConvergenceTable gatherer2(gathererOne);

		vector<MJArray> args(2);
		args[0] = MJArray(steps1);
		args[1] = MJArray(steps1);

		for (unsigned long i = 0; i < NumberOfPaths; i++)
		{
			double thisVol = sqrt(ThePath2->GetOnePathVol(args)); //cout << thisVol << endl;
			double thisPayOff = BlackScholesCall(Spot, Strike, r, 0.0, thisVol, Expiry);
			gatherer2.DumpOneResult(thisPayOff);
		}

		vector<vector<double> > results4 = gatherer2.GetResultsSoFar();

		cout << "heston mc pricing : " << endl;
		cout << "short-step the vol and plug it into BSM formula" << endl;
		cout << "\nFor the vanilla call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results4.size(); i++)
		{
			for (unsigned long j = 0; j < results4[i].size(); j++)
				cout << results4[i][j] << "\t ";

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