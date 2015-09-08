//main.cpp

#include<iostream>
#include<ParametersPWC.h>
#include<Arrays.h>
using namespace std;

int main()
{
	MJArray times(3);

	times[0] = 1.0;
	times[1] = 1.1;
	times[2] = 2.0;

	MJArray rates(3);

	rates[0] = 1.5;
	rates[1] = 2.1235;
	rates[2] = 3.15687;

	cout << "rates :" << endl;

	cout << "0, " << times[0] << ": " << rates[0] << endl;
	for (unsigned long i = 1; i < rates.size(); ++i)	cout << times[i - 1] << ", " << times[i] << ": " << rates[i] << endl;

	ParametersPWC my_param(times, rates);

	double _time1 = 0.0;
	double _time2 = 2.0;

	cout << "integral " << _time1 << "," << _time2 << " : " <<
		my_param.Integral(_time1, _time2) << endl;

	cout << "integral2 " << _time1 << "," << _time2 << " : " <<
		my_param.IntegralSquare(_time1, _time2) << endl;

	double tmp;
	cin >> tmp;

	return 0;
}