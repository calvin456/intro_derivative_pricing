#include<iostream>
#include <Normals.h>
#include <cmath>

#include<Arrays.h>
#include<ParkMiller.h>
#include<AntiThetic.h>
#include<BlackScholesFormulas.h>
#include"path_generation.h"
#include"engine.h"
#include<Vanilla3.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
#include<Digital.h>

using namespace std;

int main(){

	try{

		double Spot(100);
		double Strike(100);
		double r(.01);
		double d(.03);
		double Vol(.30);
		double Expiry(.33);
		unsigned long NumberOfPaths(1e6);

		//Validation via MC



		// (ii) Use the engine to write MC pricers for all the products mentionned above

		cout << "analytical solution BSM call : " << BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << "analytical solution BSM put : " << BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << "analytical solution BSM digital call : " << BlackScholesDigitalCall(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << "analytical solution BSM digital put : " << BlackScholesDigitalPut(Spot, Strike, r, d, Vol, Expiry) << endl;

		PayOffCall thePayOff(Strike);

		unique_ptr<VanillaOption> theOption(new VanillaOption(thePayOff, Expiry));

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant driftParam(r - d);

		StatisticsMean gatherer_mean;

		StatisticsSE gatherer_se;

		vector<Wrapper<StatisticsMC>> stat_vec;
		stat_vec.resize(2);
		stat_vec[0] = gatherer_mean;
		stat_vec[1] = gatherer_se;
		StatsGatherer gathererOne(stat_vec);

		//Generate convergence table
		ConvergenceTable gatherer(gathererOne);

		StatisticsKeepTrack _gatherer_time;

		ConvergenceTable gatherer_time(_gatherer_time);

		RandomParkMiller generator_(1);

		unique_ptr<RandomBase> generator(new AntiThetic(generator_));

		//unique_ptr<RandomBase> generator(new RandomParkMiller(1));

		unique_ptr<Path> thePath(new PathBS(generator, driftParam, VolParam, Spot, Expiry));

		mc_pricer(theOption, rParam, NumberOfPaths, gatherer, gatherer_time, thePath);

		vector<vector<double> > results = gatherer.GetResultsSoFar();
		vector<vector<double> > results1 = gatherer_time.GetResultsSoFar();

		cout << "1st mc pricer" << endl;

		cout << "\nFor the call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++){
				cout << results[i][j] << "\t";

			}
			cout << results1[i][0] << "\t";
			cout << "\n";
		}
		/*
		PayOffPut thePayOff1(Strike);

		unique_ptr<VanillaOption> theOption1(new VanillaOption(thePayOff1, Expiry));

		ConvergenceTable gatherer1(gathererOne);

		mc_pricer(theOption1, rParam, NumberOfPaths, gatherer1, theEngine);


		vector<vector<double> > results1 = gatherer1.GetResultsSoFar();

		cout << "\nFor the put price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results1.size(); i++)
		{
		for (unsigned long j = 0; j < results1[i].size(); j++)
		cout << results1[i][j] << " ";

		cout << "\n";
		}

		PayOffDigitalCall thePayOff2(Strike);

		unique_ptr<VanillaOption> theOption2(new VanillaOption(thePayOff2, Expiry));

		ConvergenceTable gatherer2(gathererOne);

		mc_pricer(theOption2, rParam, NumberOfPaths, gatherer2, theEngine);


		vector<vector<double> > results2 = gatherer2.GetResultsSoFar();

		cout << "\nFor the digital call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results2.size(); i++)
		{
		for (unsigned long j = 0; j < results2[i].size(); j++)
		cout << results2[i][j] << " ";

		cout << "\n";
		}

		PayOffDigitalPut thePayOff3(Strike);

		unique_ptr<VanillaOption> theOption3(new VanillaOption(thePayOff3, Expiry));

		ConvergenceTable gatherer3(gathererOne);

		mc_pricer(theOption3, rParam, NumberOfPaths, gatherer3, theEngine);


		vector<vector<double> > results3 = gatherer3.GetResultsSoFar();

		cout << "\nFor the digital put price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results3.size(); i++)
		{
		for (unsigned long j = 0; j < results3[i].size(); j++)
		cout << results3[i][j] << " ";

		cout << "\n";
		}

		*/

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