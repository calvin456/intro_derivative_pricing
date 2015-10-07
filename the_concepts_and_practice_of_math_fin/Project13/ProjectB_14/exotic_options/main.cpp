//main.cpp

//Implement exotic pricer for Asian option and discrete ko barrier option

#include <vector>
#include <iostream>
#include <memory>

#include <path_generation_heston.h>
#include <path_generation_gbm_svm.h>
#include <PayOff3.h>
#include <Vanilla3Template.cpp>
#include <Parameters.h>
#include <MCStatistics.h>
#include <ConvergenceTable.h>
#include <MersenneTwister.h>
#include <Random2.h>
#include <AntiThetic.h>
#include <PathDependentAsian.h>
#include <PathDependentDiscreteKnockOut.h>
#include <engine_exotic.h>

using namespace std;

int main(){

	try {

		double Spot(100.0);
		double Strike(100.0);

		double r(0.05);
		double d(0.0);

		double Vol(.1);

		double kappa(0.0);
		//double theta(.1);
		double sigma(.2);
		double correl(0.0);

		double Expiry(1.0);


		//Price one-year Asian call option w/ monthly resets

		//use of mc pricer with template class

		PayOffCall thePayOff(Strike);

		//create template vanilla option class

		unsigned long NumberOfDates(12);

		MJArray times(NumberOfDates);
		for (unsigned long i = 0; i < NumberOfDates; i++)
			times[i] = (i + 1.0)*Expiry / NumberOfDates;

		shared_ptr<PathDependent> theOption(new PathDependentAsian(times, Expiry, thePayOff));

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant driftParam(r - d);
		//----------------------------------------------------------
		//mc pricing

		StatisticsMean gatherer_mean;
		StatisticsSE gatherer_se;

		std::vector<Wrapper<StatisticsMC>> stat_vec;
		stat_vec.resize(2);
		stat_vec[0] = gatherer_mean;
		stat_vec[1] = gatherer_se;
		StatsGatherer gathererOne(stat_vec);

		ConvergenceTable gatherer(gathererOne);

		RandomMersenneTwister generator_(1);

		shared_ptr<RandomBase> _generator(new AntiThetic(generator_));

		unsigned long steps(NumberOfDates - 1);

		shared_ptr<PathGenerationHeston> thePath(new PathGenerationHeston(_generator, Spot, Expiry, driftParam, VolParam, steps, correl, kappa, sigma));

		unsigned long NumberOfPaths(static_cast<unsigned long> (1e04));

		engine_mc_exotic<PathDependent, PathGenerationHeston> theEngine(theOption, rParam, thePath);
		theEngine.DoSimulation(gatherer, NumberOfPaths);

		std::vector<std::vector<double>> results = gatherer.GetResultsSoFar();

		cout << "heston mc pricing : " << endl;
		cout << "\nFor the Asian call price the results are \n";
		cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results.size(); i++)
		{
			for (unsigned long j = 0; j < results[i].size(); j++)
				cout << results[i][j] << "\t ";

			cout << "\n";
		}
		cout << endl;
		//-----------------------------------------------------------------

		//implied vol. jdp model

		matrix<double> vol_matrix_atm(12, 2);

		//atm implied vol.

		vol_matrix_atm(11, 0) = 1.0; // 1-yr
		vol_matrix_atm(11, 1) = .231406;

		vol_matrix_atm(10, 0) = .916667; // 11-mth
		vol_matrix_atm(10, 1) = .225215;

		vol_matrix_atm(9, 0) = .833333; // 10-mth
		vol_matrix_atm(9, 1) = .218995;

		vol_matrix_atm(8, 0) = .75; // 9-mth
		vol_matrix_atm(8, 1) = .212295;

		vol_matrix_atm(7, 0) = .666667; // 8-mth
		vol_matrix_atm(7, 1) = .205498;

		vol_matrix_atm(6, 0) = .583333; // 7-mth
		vol_matrix_atm(6, 1) = .198084;

		vol_matrix_atm(5, 0) = .5; // 6-mth
		vol_matrix_atm(5, 1) = .19018;

		vol_matrix_atm(4, 0) = .416667; // 5-mth
		vol_matrix_atm(4, 1) = .181934;

		vol_matrix_atm(3, 0) = .333333; // 4-mth
		vol_matrix_atm(3, 1) = .172586;

		vol_matrix_atm(2, 0) = .25; // 3-mth
		vol_matrix_atm(2, 1) = .162396;

		vol_matrix_atm(1, 0) = .166667; // 2-mth
		vol_matrix_atm(1, 1) = .149514;

		vol_matrix_atm(0, 0) = .083333; // 1-mth
		vol_matrix_atm(0, 1) = .134838;

		//------------------------------------------------------------------

		// Reprice one-year Asian call option w/ monthly resets 
		// using BSM model w/ time-dependent vol

		//_generator->ResetDimensionality(11);
		_generator->Reset();

		shared_ptr<PathGeneration> thePath1(new PathGenerationGBM_SV(_generator, Spot, Expiry, driftParam, vol_matrix_atm, steps));

		engine_mc_exotic<PathDependent, PathGeneration> theEngine1(theOption, rParam, thePath1);

		ConvergenceTable gatherer1(gathererOne);
		theEngine1.DoSimulation(gatherer1, NumberOfPaths);

		std::vector<std::vector<double>> results1 = gatherer1.GetResultsSoFar();

		cout << "gbm with stochastic vol mc pricing - atm : " << endl;
		cout << "\nFor the Asian call price the results are \n";
		//cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results1.size(); i++)
		{
			for (unsigned long j = 0; j < results1[i].size(); j++)
				cout << results1[i][j] << "\t ";

			cout << "\n";
		}
		cout << endl;
		//------------------------------------------------------------------

		//Price discrete barrier call option calibrating w/ ATM vol

		_generator->Reset();

		shared_ptr<PathDependent> theOption1(new PathDependentDiscreteKnockOut(times, Expiry, 105, thePayOff));

		engine_mc_exotic<PathDependent, PathGeneration> theEngine2(theOption1, rParam, thePath1);

		ConvergenceTable gatherer2(gathererOne);
		theEngine2.DoSimulation(gatherer2, NumberOfPaths);

		std::vector<std::vector<double> > results2 = gatherer2.GetResultsSoFar();

		cout << "gbm with stochastic vol mc pricing - atm : " << endl;
		cout << "\nFor the discrete barrier call price the results are \n";
		//cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results2.size(); i++)
		{
			for (unsigned long j = 0; j < results2[i].size(); j++)
				cout << results2[i][j] << "\t ";

			cout << "\n";
		}
		cout << endl;

		matrix<double> vol_matrix_atb(12, 2);

		//atb at-the-barrier implied vol.

		vol_matrix_atb(11, 0) = 1.0; // 1-yr
		vol_matrix_atb(11, 1) = .200092;

		vol_matrix_atb(10, 0) = .916667; // 11-mth
		vol_matrix_atb(10, 1) = .194004;

		vol_matrix_atb(9, 0) = .833333; // 10-mth
		vol_matrix_atb(9, 1) = .187912;

		vol_matrix_atb(8, 0) = .75; // 9-mth
		vol_matrix_atb(8, 1) = .18138;

		vol_matrix_atb(7, 0) = .666667; // 8-mth
		vol_matrix_atb(7, 1) = .174785;

		vol_matrix_atb(6, 0) = .583333; // 7-mth
		vol_matrix_atb(6, 1) = .167692;

		vol_matrix_atb(5, 0) = .5; // 6-mth
		vol_matrix_atb(5, 1) = .160189;

		vol_matrix_atb(4, 0) = .416667; // 5-mth
		vol_matrix_atb(4, 1) = .152507;

		vol_matrix_atb(3, 0) = .333333; // 4-mth
		vol_matrix_atb(3, 1) = .143945;

		vol_matrix_atb(2, 0) = .25; // 3-mth
		vol_matrix_atb(2, 1) = .13494;

		vol_matrix_atb(1, 0) = .166667; // 2-mth
		vol_matrix_atb(1, 1) = .124267;

		vol_matrix_atb(0, 0) = .083333; // 1-mth
		vol_matrix_atb(0, 1) = .113508;

		//Price discrete barrier call option calibrating w/ ATB vol
		_generator->Reset();

		shared_ptr<PathGeneration> ThePath2(new PathGenerationGBM_SV(_generator, Spot, Expiry, driftParam, vol_matrix_atb, NumberOfDates));

		engine_mc_exotic<PathDependent, PathGeneration> theEngine3(theOption1, rParam, ThePath2);

		ConvergenceTable gatherer3(gathererOne);
		theEngine3.DoSimulation(gatherer3, NumberOfPaths);

		std::vector<std::vector<double> > results3 = gatherer3.GetResultsSoFar();

		cout << "gbm with stochastic vol mc pricing - atb : " << endl;
		cout << "\nFor the discrete barrier call price the results are \n";
		//cout << "with antithetic variables \n";
		cout << "mean\t se\t path\n";
		for (unsigned long i = 0; i < results3.size(); i++)
		{
			for (unsigned long j = 0; j < results3[i].size(); j++)
				cout << results3[i][j] << "\t ";

			cout << "\n";
		}
		cout << endl;

		//--------------------------------------------------------

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