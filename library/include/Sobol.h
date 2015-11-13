/*
Exercice 6.3 Code up a low-discrepancy number generator and integrate it into the classes here

Sobol low-discrepancy sequence generator. ref. Dimitri Reiswich, QuantLib into 2

Sobol sequence implemented in QuantLib. ref. www.mathematik.uni-ulm.de/numerik/teaching/s09/NumFin/Exercises/QuantLib.pdf

*/

#ifndef SOBOL_H
#define SOBOL_H
#include <Random2.h>

#include <ql/quantlib.hpp>
//#include <ql/math/randomnumbers/sobolrsg.hpp>

using namespace QuantLib;

class Sobol
{
public:
    Sobol(long Seed = 0);
    double GetOneRandomInteger();
    void SetSeed(long Seed);
private:
    double Seed;
	static SobolRsg sobolGen;
};

class RandomSobol : public RandomBase
{
public:

	RandomSobol(unsigned long Dimensionality, unsigned long Seed = 123456); //4096 123456 0

    virtual RandomBase* clone() const;

    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    virtual void ResetDimensionality(unsigned long NewDimensionality);

    virtual void GetUniforms(MJArray& variates);
	virtual void GetUniforms(std::vector<double>& variates, double a = 0.0, double b = 1.0) ;
private:

    Sobol InnerGenerator;
    unsigned long InitialSeed;

};
#endif
