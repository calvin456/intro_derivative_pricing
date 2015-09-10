// tgamma only implemented in std library since C++11
//ref. http://rosettacode.org/wiki/Gamma_function#C

#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES // for C++
#include <cmath>

using namespace std;

/* very simple approximation */
double st_gamma(double x) //Striling's approximation
{
  return std::sqrt(2.0*M_PI/x)*std::pow(x/M_E, x);
}

#define A 12
double sp_gamma(double z) //Spouge's approximation
{
  const int a = A;
  static double c_space[A];
  static double *c = NULL;
  int k;
  double accm;

  if ( c == NULL ) {
    double k1_factrl = 1.0; /* (k - 1)!*(-1)^k with 0!==1*/
    c = c_space;
    c[0] = std::sqrt(2.0*M_PI);
    for(k=1; k < a; k++) {
      c[k] = std::exp(a-(double)(k)) * std::pow(a-k, k-0.5) / k1_factrl;
	  k1_factrl *= -k;
    }
  }
  accm = c[0];
  for(k=1; k < a; k++) {
    accm += c[k] / ( z + k );
  }
  accm *= std::exp(-(z+a)) * std::pow(z+a, z+0.5); /* Gamma(z+1) */
  return accm/z;
}
