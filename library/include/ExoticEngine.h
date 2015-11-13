//
//
//                      ExoticEngine.h
//
//

// add method part of exercise 7.3

#ifndef EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H
#include <wrapper.h>
#include <Parameters.h>
#include <PathDependent.h>
#include <MCStatistics.h>
#include <vector>

//Edit to account for change lov vs level value
//Edit to include boolean - speed up. cf. project 5

class ExoticEngine
{
public:

    ExoticEngine(const Wrapper<PathDependent>& TheProduct_,
                 const Parameters& r_,
				 bool speed_up_ = false);

    virtual void GetOnePath(MJArray& LogSpotValues)=0;

    void DoSimulation(StatisticsMC& TheGatherer, unsigned long NumberOfPaths);
    virtual ~ExoticEngine(){}
    double DoOnePath(const MJArray& SpotValues) const;

protected:
    method method_;
	bool speed_up;
    Wrapper<PathDependent> TheProduct;
    Parameters r;
    MJArray Discounts;
	mutable std::vector<MyCashFlow::CashFlow> TheseCashFlows;
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
