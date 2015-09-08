//
//
//
//                      MCStatistics.h
//
//

#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <wrapper.h>

class StatisticsMC
{
public:

    StatisticsMC(){}

    virtual void DumpOneResult(double result)=0;
    virtual std::vector<std::vector<double> > GetResultsSoFar() const=0;
    virtual StatisticsMC* clone() const=0;
    virtual ~StatisticsMC(){}

private:

};


class StatisticsMean : public StatisticsMC
{

public:

    StatisticsMean();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

    double RunningSum;
    unsigned long PathsDone;

};

//Exercice 5.1
class StatisticsMoments4 : public StatisticsMC
{

public:

    StatisticsMoments4();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

    double RunningSum;
	double RunningSum2;
	double RunningSum3;
	double RunningSum4;
    unsigned long PathsDone;

};


//Exercice 5.2
class ValueAtRisk : public StatisticsMC
{

public:

    ValueAtRisk(double alpha_);
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

    std::vector<double> PathData;
	double alpha;
    unsigned long PathsDone;

};

//Exercice 5.3
class StatsGatherer : public StatisticsMC
{
public:

   StatsGatherer(const std::vector<Wrapper<StatisticsMC> >& GathererVector_);
   virtual void DumpOneResult(double result);
   virtual std::vector<std::vector<double> > GetResultsSoFar() const;
   virtual StatisticsMC* clone() const;

private:
   std::vector<Wrapper<StatisticsMC> > GathererVector;
   unsigned long PathsDone;
};

//Exercice 6.1
class StatisticsSE : public StatisticsMC
{

public:

    StatisticsSE();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

    double RunningSum;
	double RunningSum2;
    unsigned long PathsDone;

};

class StatisticsVariance : public StatisticsMC
{

public:

    StatisticsVariance();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

    double RunningSum;
	double RunningSum2;
    unsigned long PathsDone;

};

class StatisticsStdDev : public StatisticsMC
{

public:

    StatisticsStdDev();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

    double RunningSum;
	double RunningSum2;
    unsigned long PathsDone;

};

class StatisticsRMS : public StatisticsMC
{

public:

    StatisticsRMS();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;

private:

	double RunningSum2;
    unsigned long PathsDone;

};

class StatisticsKeepTrack : public StatisticsMC
{

public:

	StatisticsKeepTrack();
	virtual void DumpOneResult(double result);
	virtual std::vector<std::vector<double> > GetResultsSoFar() const;
	virtual StatisticsMC* clone() const;

private:

	double LastNumber;
	unsigned long PathsDone;

};

#endif

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

