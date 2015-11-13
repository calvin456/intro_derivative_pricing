/*
ex. 9.2 Take your favourite numerical integration routine,e.g. the trapezium rule, and write a template routine to carry it out
*/

#include<Terminator.h>
#include<Timer.h>
#include<cmath>


//code for computing an approximate value of an integral with given tolerance
template<
	template<class> class T1, 
	class T2
>
double Numerical_integration( double Tolerance,
                unsigned long Steps,
                T1<T2>& TheNumericalRule) 
{
    
	double i_old = TheNumericalRule(Steps);
    Steps*=2;
	double i_new = TheNumericalRule(Steps);
	
    do
    {
       i_old = i_new;
        Steps*=2;
		i_new =  TheNumericalRule(Steps);
    }
    while 
        ( (fabs(i_new-i_old) > Tolerance) );

    return i_new;
}

	template<
		template<class> class T1,
	class T2
	>
	double Numerical_integration1(double Tolerance,
	unsigned long Steps,
	T1<T2>& TheNumericalRule,
	Terminator& Terminator_)
	{

		double i_old = TheNumericalRule(Steps);
		Steps *= 2;
		double i_new = TheNumericalRule(Steps);

		double maxIterration = Terminator_.getPathsDone();

		unsigned long seconds = Terminator_.getTimeSpent();
		timer t;
		t.start();

		unsigned long i = 0;

		do
		{
			if (t.elapsedTime() >= seconds) {
				break;
			}
			else {

				i_old = i_new;
				Steps *= 2;
				i_new = TheNumericalRule(Steps);
			}
		} while
			((fabs(i_new - i_old) > Tolerance) && (i < maxIterration));

		return i_new;
	}