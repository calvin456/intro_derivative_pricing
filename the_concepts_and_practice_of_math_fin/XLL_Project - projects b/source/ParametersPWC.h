//
//
//
//                      Parameters.h
//
//
#include<Parameters.h>

#include <Arrays.h>
using namespace std;


#ifndef PARAMETERS_PWC_H
#define PARAMETERS_PWC_H



//Exercice 4.3 
class ParametersPWC : public ParametersInner
{
public:
	ParametersPWC(const MJArray& _times, const MJArray& _constant);
	virtual ParametersInner* clone() const;
	virtual double Integral(double time1, double time2) const;
	virtual double IntegralSquare(double time1, double time2) const;
private:
	MJArray Times;
	MJArray Constant;
	MJArray K1;
	MJArray K2;
};	

#endif


