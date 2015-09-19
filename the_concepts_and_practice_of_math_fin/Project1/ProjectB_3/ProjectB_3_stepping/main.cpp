#include <iostream>
#include <cmath>

#include <Normals.h>
#include <Parameters.h>
#include <Arrays.h>
#include <MersenneTwister.h>
//#include <ParkMiller.h>
#include <AntiThetic.h>
#include <BlackScholesFormulas.h>
#include <path_generation_gbm.h>
#include <engine_vanilla.h>
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
		unsigned long NumberOfPaths(static_cast<unsigned long>(1e4));

		//Stepping methods

		// (ii) Compare the number of paths required for the 2 mc methods to get a given degree of convergence

		// (iii) Make sure the two methods give the same prices

		// (iv) Compare the times req to set a given level of accuracy

		cout << "analytical solution BSM call : " << BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << "analytical solution BSM put : " << BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << "analytical solution BSM digital call : " << BlackScholesDigitalCall(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << "analytical solution BSM digital put : " << BlackScholesDigitalPut(Spot, Strike, r, d, Vol, Expiry) << endl;

		PayOffCall thePayOff(Strike);

		VanillaOptionTemplate<PayOffCall> theOption(thePayOff, Expiry);

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

		RandomMersenneTwister generator_(6000);
		//RandomParkMiller generator_(6000);

		RandomBase* generator(new AntiThetic(generator_));
		// At 6 000 steps price converges
		shared_ptr<PathGeneration> thePath(new PathEulerStepping(generator, Spot, Expiry,
											driftParam,
											VolParam,
											6000));


		mc_pricer_vanilla(theOption, rParam, thePath, NumberOfPaths, gatherer, gatherer_time);

		vector<vector<double> > results = gatherer.GetResultsSoFar();
		vector<vector<double> > results1 = gatherer_time.GetResultsSoFar();

		cout << "alternative mc pricer" << endl;

		cout << "\nFor the call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++){
				cout << results[i][j] << "\t ";

			}
			cout << results1[i][0] << "\t ";
			cout << "\n";
		}
		
		PayOffPut thePayOff1(Strike);

		VanillaOptionTemplate<PayOffPut> theOption1(thePayOff1, Expiry);

		ConvergenceTable gatherer1(gathererOne);

		ConvergenceTable gatherer_time1(_gatherer_time);

		mc_pricer_vanilla(theOption1, rParam, thePath, NumberOfPaths, gatherer1, gatherer_time1);

		vector<vector<double> > results2 = gatherer1.GetResultsSoFar();
		vector<vector<double> > results3 = gatherer_time1.GetResultsSoFar();

		cout << "\nFor the put price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results2.size(); i++)
		{
			for (unsigned long j = 0; j < results2[i].size(); j++){
				cout << results2[i][j] << "\t ";

			}
			cout << results3[i][0] << "\t ";
			cout << "\n";
		}

		PayOffDigitalCall thePayOff2(Strike);

		VanillaOptionTemplate<PayOffDigitalCall> theOption2(thePayOff2, Expiry);

		ConvergenceTable gatherer2(gathererOne);

		ConvergenceTable gatherer_time2(_gatherer_time);

		mc_pricer_vanilla(theOption2, rParam, thePath, NumberOfPaths, gatherer2, gatherer_time2);

		vector<vector<double> > results4 = gatherer2.GetResultsSoFar();
		vector<vector<double> > results5 = gatherer_time2.GetResultsSoFar();

		cout << "\nFor the digital call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results4.size(); i++)
		{
			for (unsigned long j = 0; j < results4[i].size(); j++){
				cout << results4[i][j] << "\t ";

			}
			cout << results5[i][0] << "\t ";
			cout << "\n";
		}

		PayOffDigitalPut thePayOff3(Strike);

		VanillaOptionTemplate<PayOffDigitalPut> theOption3(thePayOff3, Expiry);

		ConvergenceTable gatherer3(gathererOne);

		ConvergenceTable gatherer_time3(_gatherer_time);

		mc_pricer_vanilla(theOption3, rParam, thePath, NumberOfPaths, gatherer3, gatherer_time3);

		vector<vector<double> > results6 = gatherer3.GetResultsSoFar();
		vector<vector<double> > results7 = gatherer_time3.GetResultsSoFar();

		cout << "\nFor the digital put price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results6.size(); i++)
		{
			for (unsigned long j = 0; j < results6[i].size(); j++){
				cout << results6[i][j] << "\t ";

			}
			cout << results7[i][0] << "\t ";
			cout << "\n";
		}
		
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