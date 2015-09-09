//FPMain.cpp

/* Reproduced from 13.8 Floating point exceptions, p.187-192, C++ Design Patterns and Derivatives Pricing,
2nd ed, Mark S. Joshi, 2008

see post https://msdn.microsoft.com/en-us/library/aa289157%28v=vs.71%29.aspx#floapoint_topic8

*/

/*
test
0 1 -> division by zero exception
1 1e6 -> float overflow
*/

#include "FPSetup.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	EnableFloatingPointExceptions();

	try
	{
		double x;
		double y;
		cin >> x;
		cin >> y;

		double z = y / x;
		double t = exp(z);
		cout << z << " " << t << "\n";

	}
	catch (fe_divide_by_zero&)
	{
		cout << "div by zero\n";
	}
	catch (float_exception&)
	{
		cout << "other floating point exception\n";
	}
	catch (...)
	{
		cout << "exception caught\n";
	};

	char c;
	cin >> c;

	return 0;
}