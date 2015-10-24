// main.cpp

//test Asian and discrete barrier option  + QMC (Sobol sequence)

#include <iostream>
#include <memory>

#include <BlackScholesFormulas.h>
#include <barrier_options_analytical.h>
#include <options.h>

#include<Parameters.h>
#include<ParametersPWC.h>
#include<MCStatistics.h>
#include<ConvergenceTable.h>
//#include<AntiThetic.h>
#include <Sobol.h>

#include <PathDependentAsian.h>
#include <PathDependentDiscreteDO.h>
#include <PathDependentDiscreteDI.h>

#include <PathDependentAsianSU.h>
#include <PathDependentDiscreteDOSU.h>
#include <PathDependentDiscreteDISU.h>

#include<ExoticBSEngine.h>

using namespace std;
using namespace MyOption;
using namespace BSFunction;


int main(){

	try{

		double Spot(100.0);
		double Vol(0.1);
		double r(.05);
		double d(.03);
		double Strike(103.0);
		double Expiry(1.0);

		unsigned long NumberOfPaths(static_cast<unsigned long>(1e05)); //1e06
		//----------------------------------------------------------
		//pricing BSM call and put

		cout << "BSM call " << Spot << ", " << Vol << ", " << Expiry << ": ";
		cout << BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << endl;
		//----------------------------------------------------------
		//pricing Asian options

		PayOffCall thePayOff(Strike);

		unsigned long NumberOfDates(12);

		ParametersConstant VolParam(Vol);
		ParametersConstant rParam(r);
		ParametersConstant dParam(d);

		//Assume flat struture for Vol,r, and d
		MJArray times(NumberOfDates);

		for (unsigned long i = 0; i < NumberOfDates; i++)
			times[i] = (i + 1.0)*Expiry / NumberOfDates;

		MJArray _Vol(NumberOfDates);
		MJArray _r(NumberOfDates);
		MJArray _d(NumberOfDates);

		for (unsigned long i(0); i < NumberOfDates; ++i){
			_Vol[i] = Vol;
			_r[i] = r;
			_d[i] = d;
		}

		ParametersPWC _VolParam(times, _Vol);
		ParametersPWC _rParam(times, _r);
		ParametersPWC _dParam(times, _d);

		StatisticsMean gatherer_mean;

		StatisticsSE gatherer_se;

		std::vector<Wrapper<StatisticsMC>> stat_vec;
		stat_vec.resize(2);
		stat_vec[0] = gatherer_mean;
		stat_vec[1] = gatherer_se;
		StatsGatherer gathererOne(stat_vec);

		//Generate convergence table
		ConvergenceTable gathererTwo(gathererOne);

		RandomSobol GenTwo(NumberOfDates);

		//(i) maturity 1 year and monthly setting dates

		double _time(times[times.size() - 1] - times[times.size() - 2]);

		std::shared_ptr<MyOption::Option> call(new CallOption(Spot, Strike, _r[_r.size() - 2], _d[_d.size() - 2], _Vol[_Vol.size() - 2], _time));

		PathDependentAsianSU theOption(times, Expiry, call);

		//PathDependentAsian theOption(times, Expiry, thePayOff);

		ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, GenTwo, Spot);

		//ExoticBSEngine theEngine(theOption, _rParam, _dParam, _VolParam, GenTwo, Spot);

		theEngine.DoSimulation(gathererTwo, NumberOfPaths);

		vector<vector<double> > results = gathererTwo.GetResultsSoFar();

		cout << "Asian call option - (i) maturity 1 year and monthly setting dates : " << endl;
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results.size(); i++){
			for (unsigned long j = 0; j < results[i].size(); j++)	cout << results[i][j] << "\t ";
			cout << endl;
		}

		cout << endl;

		//(ii) maturity 1 year and three-monthly setting dates
		NumberOfDates = 3;

		MJArray times1(NumberOfDates);

		for (unsigned long i = 0; i < NumberOfDates; i++)
			times1[i] = (i + 1.0)*Expiry / NumberOfDates;

		MJArray _Vol1(NumberOfDates);
		MJArray _r1(NumberOfDates);
		MJArray _d1(NumberOfDates);

		for (unsigned long i(0); i < NumberOfDates; ++i){
			_Vol1[i] = Vol;
			_r1[i] = r;
			_d1[i] = d;
		}

		ParametersPWC _VolParam1(times1, _Vol1);
		ParametersPWC _rParam1(times1, _r1);
		ParametersPWC _dParam1(times1, _d1);

		double _time1(times1[times1.size() - 1] - times1[times1.size() - 2]);

		std::shared_ptr<MyOption::Option> call1(new CallOption(Spot, Strike, _r1[_r1.size() - 2], _d1[_d1.size() - 2], _Vol1[_Vol1.size() - 2], _time1));

		PathDependentAsianSU theOption1(times1, Expiry, call1);

		//PathDependentAsian theOption1(times1, Expiry, thePayOff);

		GenTwo.Reset();

		ExoticBSEngine theEngine1(theOption1, rParam, dParam, VolParam, GenTwo, Spot);

		//ExoticBSEngine theEngine1(theOption1, _rParam1, _dParam1, _VolParam1, GenTwo, Spot);

		ConvergenceTable gathererTwo1(gathererOne);

		theEngine1.DoSimulation(gathererTwo1, NumberOfPaths);

		vector<vector<double> > results1 = gathererTwo1.GetResultsSoFar();

		cout << "Asian call option - (i) maturity 1 year and three-monthly setting dates : " << endl;
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results1.size(); i++){
			for (unsigned long j = 0; j < results1[i].size(); j++)	cout << results1[i][j] << "\t ";
			cout << endl;
		}

		cout << endl;

		//(iii) maturity 1 year and weekly setting dates
		NumberOfDates = 52;

		MJArray times2(NumberOfDates);

		for (unsigned long i = 0; i < NumberOfDates; i++)
			times2[i] = (i + 1.0)*Expiry / NumberOfDates;

		MJArray _Vol2(NumberOfDates);
		MJArray _r2(NumberOfDates);
		MJArray _d2(NumberOfDates);

		for (unsigned long i(0); i < NumberOfDates; ++i){
			_Vol2[i] = Vol;
			_r2[i] = r;
			_d2[i] = d;
		}

		ParametersPWC _VolParam2(times2, _Vol2);
		ParametersPWC _rParam2(times2, _r2);
		ParametersPWC _dParam2(times2, _d2);

		double _time2(times2[times2.size() - 1] - times2[times2.size() - 2]);

		std::shared_ptr<MyOption::Option> call2(new CallOption(Spot, Strike, _r2[_r2.size() - 1], _d2[_d2.size() - 1], _Vol2[_Vol2.size() - 1], _time2));

		PathDependentAsianSU theOption2(times2, Expiry, call2);

		//PathDependentAsian theOption2(times2, Expiry, thePayOff);

		GenTwo.Reset();

		ExoticBSEngine theEngine2(theOption2, rParam, dParam, VolParam, GenTwo, Spot);

		//ExoticBSEngine theEngine2(theOption2, _rParam2, _dParam2, _VolParam2, GenTwo, Spot);

		ConvergenceTable gathererTwo2(gathererOne);

		theEngine2.DoSimulation(gathererTwo2, NumberOfPaths);

		vector<vector<double> > results2 = gathererTwo2.GetResultsSoFar();

		cout << "Asian call option - (i) maturity 1 year and weekly setting dates : " << endl;
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results2.size(); i++){
			for (unsigned long j = 0; j < results2[i].size(); j++)	cout << results2[i][j] << "\t ";
			cout << endl;
		}

		cout << endl;


		//-----------------------------------------------------------
		//Pricing discrete barrier options

		double BarrierDown(80.0);
		NumberOfDates = 12;
		Spot = 90.0;

		//(i) DOC w/ barrier 80 and monthly barrier dates

		std::shared_ptr<MyOption::Option> _call(new CallOption(Spot, Strike, _r[_r.size() - 1], _d[_d.size() - 1], _Vol[_Vol.size() - 1], _time));

		PathDependentDiscreteDOSU theOption3(times, Expiry, BarrierDown, _call);

		//PathDependentDiscreteDO theOption3(times, Expiry, BarrierDown, thePayOff);

		GenTwo.Reset();

		cout << "BSM call " << Spot << ", " << Vol << ", " << Expiry << ": ";
		cout << BlackScholesCall(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << "Down-and-out call - " << Strike << ", " << BarrierDown << ": ";
		cout << down_out_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry) << endl;
		cout << endl;

		ExoticBSEngine theEngine3(theOption3, rParam, dParam, VolParam, GenTwo, Spot);

		//ExoticBSEngine theEngine3(theOption3, _rParam, _dParam, _VolParam, GenTwo, Spot);

		ConvergenceTable gathererTwo3(gathererOne);

		theEngine3.DoSimulation(gathererTwo3, NumberOfPaths);

		vector<vector<double> > results3 = gathererTwo3.GetResultsSoFar();

		cout << "(i) DOC w/ barrier 80 -  maturity 1 year and monthly setting dates : " << endl;
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results3.size(); i++){
			for (unsigned long j = 0; j < results3[i].size(); j++)	cout << results3[i][j] << "\t ";
			cout << endl;
		}

		cout << endl;

		//(ii) DIC w/ barrier 80 and monthly barrier dates

		cout << "Down-and-in call - " << Strike << ", " << BarrierDown << ": ";
		cout << down_in_call(Spot, Strike, BarrierDown, r, d, Vol, Expiry) << endl;
		cout << endl;

		PathDependentDiscreteDISU theOption4(times, Expiry, BarrierDown, _call);

		//PathDependentDiscreteDI theOption4(times, Expiry, BarrierDown, thePayOff);

		GenTwo.Reset();

		ExoticBSEngine theEngine4(theOption4, rParam, dParam, VolParam, GenTwo, Spot);

		//ExoticBSEngine theEngine4(theOption4, _rParam, _dParam, _VolParam, GenTwo, Spot);

		ConvergenceTable gathererTwo4(gathererOne);

		theEngine4.DoSimulation(gathererTwo4, NumberOfPaths);

		vector<vector<double> > results4 = gathererTwo4.GetResultsSoFar();

		cout << "(ii) DIC w/ barrier 80 -  maturity 1 year and monthly setting dates : " << endl;
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results4.size(); i++){
			for (unsigned long j = 0; j < results4[i].size(); j++)	cout << results4[i][j] << "\t ";
			cout << endl;
		}

		cout << endl;

		//(iii) DOP w/ barrier 80 and monthly barrier dates

		cout << "BSM put " << Spot << ", " << Vol << ", " << Expiry << ": ";
		cout << BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) << endl;

		cout << "Down-and-out put - " << Strike << ", " << BarrierDown << ": ";
		cout << down_out_put(Spot, Strike, BarrierDown, r, d, Vol, Expiry) << endl;
		cout << endl;

		std::shared_ptr<MyOption::Option> put(new PutOption(Spot, Strike, _r[_r.size() - 1], _d[_d.size() - 1], _Vol[_Vol.size() - 1], _time));

		PathDependentDiscreteDOSU theOption5(times, Expiry, BarrierDown, put);

		//PayOffPut thePayOff1(Strike);

		//PathDependentDiscreteDO theOption5(times, Expiry, BarrierDown, thePayOff1);


		GenTwo.Reset();

		ExoticBSEngine theEngine5(theOption5, rParam, dParam, VolParam, GenTwo, Spot);

		//ExoticBSEngine theEngine5(theOption5, _rParam, _dParam, _VolParam, GenTwo, Spot);

		ConvergenceTable gathererTwo5(gathererOne);

		theEngine5.DoSimulation(gathererTwo5, NumberOfPaths);

		vector<vector<double> > results5 = gathererTwo5.GetResultsSoFar();

		cout << "(iii) DOP w/ barrier 80 -  maturity 1 year and monthly setting dates : " << endl;
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results5.size(); i++){
			for (unsigned long j = 0; j < results5[i].size(); j++)	cout << results5[i][j] << "\t ";
			cout << endl;
		}

		cout << endl;

		//(iv) DOP w/ barrier 120 and barrier dates 0.05, 0.15 , ... , .95

		GenTwo.Reset();

		double BarrierUp(120.0);
		Spot = 140.0;
		Vol = .3;
		Expiry = .95;
		NumberOfDates = 19;

		MJArray times3(NumberOfDates);

		for (unsigned long i = 0; i < NumberOfDates; i++)
			times3[i] = (i + 1.0) * .05;

		MJArray _Vol3(NumberOfDates);
		MJArray _r3(NumberOfDates);
		MJArray _d3(NumberOfDates);

		for (unsigned long i(0); i < NumberOfDates; ++i){
			_Vol3[i] = Vol;
			_r3[i] = r;
			_d3[i] = d;
		}

		ParametersPWC _VolParam3(times3, _Vol3);
		ParametersPWC _rParam3(times3, _r3);
		ParametersPWC _dParam3(times3, _d3);

		double _time3(times3[times3.size() - 1] - times3[times3.size() - 2]);

		std::shared_ptr<MyOption::Option> put1(new PutOption(Spot, Strike, _r3[_r3.size() - 1], _d3[_d3.size() - 1], _Vol3[_Vol3.size() - 1], _time3));

		PathDependentDiscreteDOSU theOption6(times3, Expiry, BarrierUp, put1);

		//PathDependentDiscreteDO theOption6(times3, Expiry, BarrierUp, thePayOff1);

		cout << "BSM put " << Spot << ", " << Vol << ", " << Expiry << ": ";
		cout << BlackScholesPut(Spot, Strike, r, d, Vol, Expiry) << endl;
		cout << endl;


		cout << "Down-and-out put - " << Strike << ", " << BarrierUp << ": ";
		cout << down_out_put(Spot, Strike, BarrierUp, r, d, Vol, Expiry) << endl;
		cout << endl;

		GenTwo.Reset();

		ExoticBSEngine theEngine6(theOption6, rParam, dParam, VolParam, GenTwo, Spot);

		//ExoticBSEngine theEngine6(theOption6, _rParam3, _dParam3, _VolParam3, GenTwo, Spot);

		ConvergenceTable gathererTwo6(gathererOne);

		theEngine6.DoSimulation(gathererTwo6, NumberOfPaths);

		vector<vector<double> > results6 = gathererTwo6.GetResultsSoFar();

		cout << "(iii) DOP w/ barrier 120 -  maturity 1 year and barrier dates ";
		cout << " 0.05, 0.15, ..., .95 : " << endl;
		cout << "mean\t se\t path\t timer\n";
		for (unsigned long i = 0; i < results6.size(); i++){
			for (unsigned long j = 0; j < results6[i].size(); j++)	cout << results6[i][j] << "\t ";
			cout << endl;
		}

		cout << endl;

		//--------------------------------------------------------------------------------------------------------

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