//MersenneTwister.cpp

#include <MersenneTwister.h>

mt19937 MersenneTwister::generator; //actual definition

MersenneTwister::MersenneTwister(unsigned long Seed_) : Seed(Seed_)
{
	if (Seed == 0)	Seed = 12411;
	generator.seed(Seed);
}

void MersenneTwister::SetSeed(unsigned long Seed_)
{
	Seed = Seed_;
	if (Seed == 0)	Seed = 12411;
	generator.seed(Seed_);
}

void MersenneTwister::Skip(unsigned long numberOfPaths)
{
	for (unsigned long i(0); i < numberOfPaths;++i)
		generator();
}

unsigned long MersenneTwister::Max()
{
	return  generator.max();
}

unsigned long MersenneTwister::Min()
{
	return generator.min();
}

double MersenneTwister::GetOneUniform(double a, double b){

	uniform_real_distribution<> uni(a, b);

	return uni(generator);

}

double  MersenneTwister::GetOneGaussian(double m, double s){

	normal_distribution<> normal(m, s);

	return normal(generator);
}

double MersenneTwister::GetOneLogNormal(double m, double s){

	lognormal_distribution<> log_normal(m, s);

	return log_normal(generator);
}

double  MersenneTwister::GetOneExponential(double lambda){

	exponential_distribution<> exponential(lambda);

	return exponential(generator);
}


double  MersenneTwister::GetOnePoisson(double lambda){

	poisson_distribution<> poisson(lambda);

	return poisson(generator);
}


double  MersenneTwister::GetOneGamma(double alpha, double beta){

	gamma_distribution<> gamma(alpha, beta);

	return gamma(generator);
}


double  MersenneTwister::GetOneBeta(double alpha, double beta){

	gamma_distribution<> a_gamma(alpha, 2.0);
	gamma_distribution<> b_gamma(beta, 2.0);

	double x = a_gamma(generator);
	return x / (x + b_gamma(generator));

}

RandomMersenneTwister::RandomMersenneTwister(unsigned long Dimensionality, unsigned long Seed)
:    RandomBase(Dimensionality),InnerGenerator(Seed), InitialSeed(Seed)
{}

RandomBase* RandomMersenneTwister::clone() const
{
    return new RandomMersenneTwister(*this);
}

void RandomMersenneTwister::Skip(unsigned long numberOfPaths)
{
	InnerGenerator.Skip(numberOfPaths);
}

void RandomMersenneTwister::SetSeed(unsigned long Seed)
{
	InitialSeed = Seed;
	InnerGenerator.SetSeed(Seed);
}

void RandomMersenneTwister::Reset()
{
	InnerGenerator.SetSeed(InitialSeed);
}

void RandomMersenneTwister::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBase::ResetDimensionality(NewDimensionality);
	InnerGenerator.SetSeed(InitialSeed);
}

void RandomMersenneTwister::GetUniforms(MJArray& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneUniform(0.0,1.0);
	}
}

void RandomMersenneTwister::GetUniforms(vector<double>& variates, double a, double b)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++)
		variates[j] = InnerGenerator.GetOneUniform(a, b);
}

void RandomMersenneTwister::GetGaussians(MJArray& variates) { RandomBase::GetGaussians(variates); }

void RandomMersenneTwister::GetGaussians(vector<double>& variates, double m, double s)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++)
		variates[j] = InnerGenerator.GetOneGaussian(m,s);
}

void RandomMersenneTwister::GetLogNormals(double m, double s, vector<double>& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneLogNormal(m, s);
	}
}

void RandomMersenneTwister::GetExponentials(double lambda, vector<double>& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneExponential(lambda);
	}
}

void RandomMersenneTwister::GetPoissons(double lambda, vector<double>& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOnePoisson(lambda);
	}
}

void RandomMersenneTwister::GetGammas(double alpha, double beta, vector<double>& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneGamma(alpha,beta);
	}
}

void RandomMersenneTwister::GetBetas(double alpha, double beta, vector<double>& variates)
{
	for (unsigned long j = 0; j < GetDimensionality(); j++){
		variates[j] = InnerGenerator.GetOneBeta(alpha, beta);
	}
}


