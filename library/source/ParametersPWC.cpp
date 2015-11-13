//
//
//
//                  Parameters.cpp
//
//
#include <Arrays.h>
#include <ParametersPWC.h>

#include<iostream>

using namespace std;



//Exercice 4.3
ParametersPWC::ParametersPWC(const MJArray& _times, const MJArray& _constant)
	:Times(_times),Constant(_constant)
{
	K1.resize(Constant.size()+1);
	K2.resize(Constant.size()+1);

	K1[0] = 0.0;
	K1[1] = Constant[0] * Times[0];

	for (unsigned long i(2); i < K1.size(); ++i)
		K1[i] = Constant[i-1] * (Times[i-1] - Times[i - 2]);

	K2[0] = 0.0;
	K2[1] = Constant[0] * Constant[0] * Times[0];

	for (unsigned long i(2); i < K2.size(); ++i)
		K2[i] = Constant[i-1] * Constant[i-1] * (Times[i-1] - Times[i - 2]);

}

ParametersInner* ParametersPWC::clone() const{
    return new ParametersPWC(*this);
}

double ParametersPWC::Integral(double time1, double time2) const{
	double integral(0.0);

	unsigned long _time1(1);
	for (unsigned long i(0);i < Times.size();++i)
		if (Times[i] < time1)	_time1++;

	unsigned long _time2(1);
	if(time1 == 0.0) _time2+=1;

	for (unsigned long i(0);i < Times.size();++i)
		if (Times[i] < time2)	_time2++;

	for (unsigned long i(_time1); i < _time2; ++i)	integral += K1[i];

	return integral;
}

double ParametersPWC::IntegralSquare(double time1, double time2) const{
	double integral_square(0.0);

	unsigned long _time1(1);
	for (unsigned long i(0);i < Times.size();++i)
		if (Times[i] < time1)	_time1++;

	unsigned long _time2(1);
	if(time1 == 0.0) _time2+=1;

	for (unsigned long i(0);i < Times.size();++i)
		if (Times[i] < time2)	_time2++;

	for (unsigned long i(_time1); i < _time2; ++i)	integral_square += K2[i];

	return integral_square;
}
