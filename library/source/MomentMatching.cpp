//MomentMatching.cpp

/*
use estimator: x_tilda(i) = (x(i)  - sample_mean )* sample_std_dev/pop_std_dev
		+ population_mean
*/

#include <MomentMatching.h>
#include<MyFunctions.h>

#include<iostream>

using namespace std;

MomentMatching::MomentMatching(const Wrapper<RandomBase>& innerGenerator,
								double pop_mean_,
								double pop_std_dev_)
	: RandomBase(*innerGenerator), InnerGenerator(innerGenerator),
	pop_mean(pop_mean_),pop_std_dev(pop_std_dev_)
{
    InnerGenerator->Reset();
    NextVariates.resize(GetDimensionality());
}

RandomBase* MomentMatching::clone() const
{
    return new MomentMatching(*this);
}
    
void MomentMatching::GetUniforms(MJArray& variates)
{
	//match the first and second moments	
	
    InnerGenerator->GetUniforms(variates);
		
	double smpl_avg = mean(variates);
	double smpl_std_dev = std_dev(variates);		
		
	for (unsigned long i = 0; i < GetDimensionality(); i++){
		variates[i] = pop_mean + (variates[i] - smpl_avg) * pop_std_dev / smpl_std_dev;
	}
}

void MomentMatching::GetGaussians(MJArray& variates)
{
	//match the first and second moments	

	InnerGenerator->GetGaussians(variates);

	double smpl_avg = mean(variates);
	double smpl_std_dev = std_dev(variates);

	for (unsigned long i = 0; i < GetDimensionality(); i++){
		variates[i] = pop_mean + (variates[i] - smpl_avg) * pop_std_dev / smpl_std_dev;
	}
}

void MomentMatching::SetSeed(unsigned long Seed)
{
    InnerGenerator->SetSeed(Seed);
}

void MomentMatching::Skip(unsigned long numberOfPaths)
{
    if (numberOfPaths ==0)	return;

    InnerGenerator->Skip(numberOfPaths  / 2);

    if (numberOfPaths % 2){
        MJArray tmp(GetDimensionality());
        GetUniforms(tmp);
    }
}

void MomentMatching::ResetDimensionality(unsigned long NewDimensionality)
{
    RandomBase::ResetDimensionality(NewDimensionality);

    NextVariates.resize(NewDimensionality);

    InnerGenerator->ResetDimensionality(NewDimensionality);
}

void MomentMatching::Reset()
{
    InnerGenerator->Reset();
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