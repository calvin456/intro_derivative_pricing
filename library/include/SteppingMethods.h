/*
b3 project 1 :vanilla options in a bs world
*/

#ifndef STEPPING_METHODS_H
#define STEPPING_METHODS_H
//S(j+1)deltaT = S(j)deltaT + r * S(j)deltaT * deltaT + S(j)deltaT * sigma * sqrt(delta) * Wj

double FinalPrice_EulerStepping( double Spot,
                         unsigned long Steps,
                         double r,
                         double d,
                         double Vol,
                         double Expiry);

#endif
