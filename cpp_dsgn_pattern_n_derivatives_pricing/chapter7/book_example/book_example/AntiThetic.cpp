//
//
//                  AntiThetic.cpp
//
//

#include <AntiThetic.h>

AntiThetic::AntiThetic(const Wrapper<RandomBase>& innerGenerator )
            : RandomBase(*innerGenerator),
              InnerGenerator(innerGenerator)
{
    InnerGenerator->Reset();
    OddEven =true;
    NextVariates.resize(GetDimensionality());
}

RandomBase* AntiThetic::clone() const
{
    return new AntiThetic(*this);
}

void AntiThetic::GetUniforms(MJArray& variates)
{
    if (OddEven){
        InnerGenerator->GetUniforms(variates);

        for (unsigned long i =0; i < GetDimensionality(); i++)
            NextVariates[i] = 1.0 - variates[i];

        OddEven = false;
    }else{
        variates = NextVariates;
        OddEven = true;
    }
}

void AntiThetic::GetUniforms(vector<double>& variates, double a, double b)
{
	if (OddEven){
		InnerGenerator->GetUniforms(variates,a,b);

		for (unsigned long i = 0; i < GetDimensionality(); i++)
			NextVariates[i] = b - variates[i];

		OddEven = false;
	}
	else{
		variates = _NextVariates;
		OddEven = true;
	}
}

//void AntiThetic::GetGaussians(MJArray& variates) { RandomBase::GetGaussians(variates); }

//void AntiThetic::GetGaussians(vector<double>& variates, double m, double s) { RandomBase::GetGaussians(variates,m,s); }

void AntiThetic::SetSeed(unsigned long Seed)
{
    InnerGenerator->SetSeed(Seed);
    OddEven = true;
}

void AntiThetic::Skip(unsigned long numberOfPaths)
{
    if (numberOfPaths ==0)  return;

    if (OddEven){
        OddEven = false;
        numberOfPaths--;
    }

    InnerGenerator->Skip(numberOfPaths  / 2);

    if (numberOfPaths % 2){
        MJArray tmp(GetDimensionality());
        GetUniforms(tmp);
    }
}

void AntiThetic::ResetDimensionality(unsigned long NewDimensionality)
{
    RandomBase::ResetDimensionality(NewDimensionality);
    NextVariates.resize(NewDimensionality);
    InnerGenerator->ResetDimensionality(NewDimensionality);
}

void AntiThetic::Reset()
{
    InnerGenerator->Reset();
    OddEven =true;
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
