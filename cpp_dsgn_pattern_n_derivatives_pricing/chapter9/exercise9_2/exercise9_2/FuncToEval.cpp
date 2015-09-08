#include"FuncToEval.h"
#include<cmath>

using namespace std;

FuncToEval::FuncToEval(){}

//example of numerical integration, Dan Stefanica

double Func1::operator()(double x) const
{
    return 1.0/((x + 1.0) * (x + 1.0));	
}

double Func2::operator()(double x) const
{
	return exp(-(x *x));	
}

double Func3::operator()(double x) const
{
	return sqrt(x) * exp(-x);	
}

double Func4::operator()(double x) const
{
	return pow(x,2.5)/((x + 1.0) * (x + 1.0));
}