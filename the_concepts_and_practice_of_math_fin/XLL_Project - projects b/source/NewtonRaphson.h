//
//
//                  NewtonRaphson.h
//
//

#include<Terminator.h>
#include<Timer.h>
#include<cmath>

template<class T, double (T::*Value)(double) const, double (T::*Derivative)(double) const >
double NewtonRaphson(double Target,
                 double Start,
                 double Tolerance,
                 const T& TheObject)
{
    
    double y = (TheObject.*Value)(Start);
   
    double x=Start;

    while ( fabs(y - Target) > Tolerance )
    {
        double d = (TheObject.*Derivative)(x);
         
        x += (Target-y)/d;

        y = (TheObject.*Value)(x);
   
    }

    return x;
}

/*
ex. 9.1 Modify the Newton-Raphson routine so that it does not endlessly loop if a root is not found
*/

template<class T, double (T::*Value)(double) const, double (T::*Derivative)(double) const >
double NewtonRaphson1(double Target,
                 double Start,
                 double Tolerance,
                 const T& TheObject,
				 Terminator& Terminator_)				
{
    
    double y = (TheObject.*Value)(Start);
   
    double x = Start;
	
	double maxIterration = Terminator_.getPathsDone();
	
	unsigned long seconds = Terminator_.getTimeSpent();

	timer t;
	t.start();
	
	unsigned long i=0;
	
	while (fabs(y - Target) > Tolerance){

		if (i == maxIterration){
			cout << "Max # of iterations reached " << maxIterration << endl;
			break;
		}
			
		if (t.elapsedTime() >= seconds) {
			cout << "Max time elapsed " << seconds << endl;
			break;
		}
			
		double d = (TheObject.*Derivative)(x);
		x+= (Target-y)/d;
		y = (TheObject.*Value)(x);
		++i;
		
	}
	
    return x;
}


/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

