//
//
//
//                      MCStatistics.cpp
//
//

#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>

#include<MCStatistics.h>
#include <wrapper.h>

using namespace std;

StatisticsMean::StatisticsMean()
    :
    RunningSum(0.0), PathsDone(0UL)
{
}
    
void StatisticsMean::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum += result;
}

vector<vector<double> > StatisticsMean::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);

    Results[0].resize(1);
    Results[0][0] = RunningSum / PathsDone;

    return Results;
}

StatisticsMC* StatisticsMean::clone() const
{
    return new StatisticsMean(*this);
}

//Exercice 5.1
StatisticsMoments4::StatisticsMoments4()
:RunningSum(0.0), RunningSum2(0.0),RunningSum3(0.0),RunningSum4(0.0),PathsDone(0UL)
{}

void StatisticsMoments4::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum +=  result;
	RunningSum2 +=  result* result;
	RunningSum3 += result * result * result;
	RunningSum4 += result * result * result * result;
	
}

vector<vector<double> > StatisticsMoments4::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);

    Results[0].resize(4);
    Results[0][0] = RunningSum / PathsDone;
	Results[0][1] = RunningSum2 / PathsDone;
	Results[0][2] = RunningSum3 / PathsDone;
	Results[0][3] = RunningSum4 / PathsDone;

    return Results;
}

StatisticsMC* StatisticsMoments4::clone() const
{
    return new StatisticsMoments4(*this);
}

/*
Compute historical VaR method
Taken from quant finance books forum at www.markjoshi.com 
Re: Exercises - Chapter 5
Post by emza0114 Mon Jan 28, 2013 12:23 pm 
*/

ValueAtRisk::ValueAtRisk(double alpha_) : alpha(alpha_)
{
   PathsDone=0;
}

StatisticsMC* ValueAtRisk::clone() const
{
    return new ValueAtRisk(*this);
}

void ValueAtRisk::DumpOneResult(double result)
{
   PathData.push_back(result);
    ++PathsDone;
}

vector<vector<double> >  ValueAtRisk::GetResultsSoFar() const
{
   vector<vector<double> > Results(1);
   Results[0].resize(1);

   vector<double> tmp(PathData);
   
   sort(tmp.begin(), tmp.end());
   int n(tmp.size());
   int var_slot((int)(ceil(n*alpha)));
   
   Results[0][0] = tmp[var_slot];
   return Results;
}

/*
Taken from quant finance books forum at www.markjoshi.com 
Re: Exercise 5.3
Postby rer » Fri Apr 27, 2012 11:52 am 
*/
StatsGatherer::StatsGatherer(const vector<Wrapper<StatisticsMC>>& GathererVector_)
: GathererVector(GathererVector_),PathsDone(0UL)
{}

void StatsGatherer::DumpOneResult(double result)
{
	for(unsigned long i=0;i <GathererVector.size();++i){
		GathererVector[i]->DumpOneResult(result);
	}
}

vector<vector<double>> StatsGatherer::GetResultsSoFar() const
{
	vector<vector<double> > Results(1);
	Results[0].resize(GathererVector.size());

	for(unsigned long i = 0; i < GathererVector.size(); i++){			
		Results[0][i] = GathererVector[i]->GetResultsSoFar()[0][0];				 		
	}
	return  Results;
}

StatisticsMC* StatsGatherer::clone() const
{
return new StatsGatherer(*this);
}

//Exercice 6.1
StatisticsSE::StatisticsSE()
:RunningSum(0.0), RunningSum2(0.0),PathsDone(0UL)
{}

void StatisticsSE::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum +=  result;
	RunningSum2 +=  result* result;
	
}

vector<vector<double> > StatisticsSE::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);

    Results[0].resize(1);
    Results[0][0] = std::sqrt((double)((RunningSum2 - (RunningSum *RunningSum)/PathsDone)/(PathsDone - 1))/PathsDone);
	
    return Results;
}

StatisticsMC* StatisticsSE::clone() const
{
    return new StatisticsSE(*this);
}


StatisticsVariance::StatisticsVariance()
:RunningSum(0.0), RunningSum2(0.0),PathsDone(0UL)
{}

void StatisticsVariance::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum +=  result;
	RunningSum2 +=  result* result;
	
}

vector<vector<double> > StatisticsVariance::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);

    Results[0].resize(1);
	Results[0][0] = (RunningSum2 - (RunningSum *RunningSum) / PathsDone) / (PathsDone - 1);
	
    return Results;
}

StatisticsMC* StatisticsVariance::clone() const
{
    return new StatisticsVariance(*this);
}


StatisticsStdDev::StatisticsStdDev()
:RunningSum(0.0), RunningSum2(0.0),PathsDone(0UL)
{}

void StatisticsStdDev::DumpOneResult(double result)
{
    PathsDone++;
    RunningSum +=  result;
	RunningSum2 +=  result* result;
	
}

vector<vector<double> > StatisticsStdDev::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);

    Results[0].resize(1);
	Results[0][0] = std::sqrt((double)((RunningSum2 - (RunningSum *RunningSum) / PathsDone) / (PathsDone - 1)));
	
    return Results;
}

StatisticsMC* StatisticsStdDev::clone() const
{
    return new StatisticsStdDev(*this);
}

StatisticsRMS::StatisticsRMS()
:RunningSum2(0.0),PathsDone(0UL)
{}

void StatisticsRMS::DumpOneResult(double result)
{
    PathsDone++;
	RunningSum2 +=  result* result;
	
}

vector<vector<double> > StatisticsRMS::GetResultsSoFar() const
{
    vector<vector<double> > Results(1);

    Results[0].resize(1);
    Results[0][0] = sqrt(RunningSum2/PathsDone);
	
    return Results;
}

StatisticsMC* StatisticsRMS::clone() const
{
    return new StatisticsRMS(*this);
}

StatisticsKeepTrack::StatisticsKeepTrack()
	:LastNumber(0.0), PathsDone(0UL)
{}

void StatisticsKeepTrack::DumpOneResult(double result)
{
	PathsDone++;
	LastNumber = result;

}

vector<vector<double> > StatisticsKeepTrack::GetResultsSoFar() const
{
	vector<vector<double> > Results(1);

	Results[0].resize(1);
	Results[0][0] = LastNumber;

	return Results;
}

StatisticsMC* StatisticsKeepTrack::clone() const
{
	return new StatisticsKeepTrack(*this);
}

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

