#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <Arrays.h>

double mean(MJArray& variates);

double std_dev(MJArray& variates);

double rmse(MJArray& variates, double theta);

double factorial(unsigned long n);

double binomialCoeff(unsigned long n, unsigned long k);

#endif