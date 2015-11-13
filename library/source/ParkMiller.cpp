//
//
//                       ParkMiller.cpp
//
//

#include <ParkMiller.h>

minstd_rand ParkMiller::generator; //actual definition

ParkMiller::ParkMiller(unsigned long Seed_) : Seed(Seed_)
{
	if (Seed == 0)	Seed = 1;
	generator.seed(Seed);
}

void ParkMiller::SetSeed(unsigned long Seed_)
{
	Seed = Seed_;
	if (Seed == 0)	Seed = 1;
	generator.seed(Seed_);
}

void ParkMiller::Skip(unsigned long numberOfPaths)
{
	for (unsigned long i(0); i < numberOfPaths;++i)
		generator();
}

unsigned long ParkMiller::Max()
{
	return  generator.max();
}

unsigned long ParkMiller::Min()
{
	return generator.min();
}

double ParkMiller::GetOneUniform(double a, double b){

	uniform_real_distribution<> uni(a, b);

	return uni(generator);

}

double  ParkMiller::GetOneGaussian(double m, double s){

	normal_distribution<> normal(m, s);

	return normal(generator);
}

double ParkMiller::GetOneLogNormal(double m, double s){

	lognormal_distribution<> log_normal(m, s);

	return log_normal(generator);
}

double  ParkMiller::GetOneExponential(double lambda){

	exponential_distribution<> exponential(lambda);

	return exponential(generator);
}


double  ParkMiller::GetOnePoisson(double lambda){

	poisson_distribution<> poisson(lambda);

	return poisson(generator);
}


double  ParkMiller::GetOneGamma(double alpha, double beta){

	gamma_distribution<> gamma(alpha, beta);

	return gamma(generator);
}


double  ParkMiller::GetOneBeta(double alpha, double beta){

	gamma_distribution<> a_gamma(alpha, 2.0);
	gamma_distribution<> b_gamma(beta, 2.0);

	double x = a_gamma(generator);
	return x / (x + b_gamma(generator));

}


RandomParkMiller::RandomParkMiller(unsigned long Dimensionality, unsigned long Seed)
:    RandomBase(Dimensionality),InnerGenerator(Seed), InitialSeed(Seed)
{}

RandomBase* RandomParkMiller::clone() const
{
    return new RandomParkMiller(*this);
}

void RandomParkMiller::Skip(unsigned long numberOfPaths)
{
	InnerGenerator.Skip(numberOfPaths);
}

void RandomParkMiller::SetSeed(unsigned long Seed)
{
	InitialSeed = Seed;
	InnerGenerator.SetSeed(Seed);
}

void RandomParkMiller::Reset()
{
	InnerGenerator.SetSeed(InitialSeed);
}

void RandomParkMiller::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBase::ResetDimensionality(NewDimensionality);
	InnerGenerator.SetSeed(InitialSeed);
}

void RandomParkMiller::GetUniforms(MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneUniform(0.0,1.0);
	}
}

void RandomParkMiller::GetUniforms(vector<double>& variates, double a, double b)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++)
		variates[j] = InnerGenerator.GetOneUniform(a, b);
}

void RandomParkMiller::GetGaussians(MJArray& variates) { RandomBase::GetGaussians(variates); }

void RandomParkMiller::GetGaussians(vector<double>& variates, double m, double s)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++)
		variates[j] = InnerGenerator.GetOneGaussian(m,s);
}

void RandomParkMiller::GetLogNormals(double m, double s, MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneLogNormal(m, s);
	}
}

void RandomParkMiller::GetExponentials(double lambda, MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneExponential(lambda);
	}
}

void RandomParkMiller::GetPoissons(double lambda, MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOnePoisson(lambda);
	}
}

void RandomParkMiller::GetGammas(double alpha, double beta, MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneGamma(alpha,beta);
	}
}

void RandomParkMiller::GetBetas(double alpha, double beta, MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneBeta(alpha, beta);
	}
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
