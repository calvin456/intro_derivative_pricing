#include<MyFunctions.h>
#include<minmax.h>
#include<cmath>
#include <stdlib.h>

double mean(MJArray& variates){ //compute sample mean
	double tmp(0.0);
	
	for (unsigned long i =0; i < variates.size(); i++)
            tmp += variates[i];
		
	return (1.0/variates.size())*tmp;	
}

double std_dev(MJArray& variates){ //compute correct std dev
	double tmp(0.0);
	
	double x_mu(mean(variates));
	
	for (unsigned long i =0; i < variates.size(); i++){
        double a(variates[i] - x_mu);   
		tmp += a * a;
	}	
	return (1.0/variates.size() - 1)*sqrt(tmp);	
}

double rmse(MJArray& variates, double theta){ //root mean square error
	double tmp(0.0);
	
	for (unsigned long i =0; i < variates.size(); i++){
        double a(variates[i] - theta);   
		tmp += a * a;
	}	
	return (1.0/variates.size())*tmp;	
	
}


double factorial(unsigned long n){
	
	return (n==1 ||n==0) ? 1:factorial(n-1)*n;
	
}

// A space optimized Dynamic Programming Solution
//http://www.geeksforgeeks.org/dynamic-programming-set-9-binomial-coefficient/

double binomialCoeff(unsigned long n, unsigned long k)
{
    double* C = (double*)calloc(k+1, sizeof(double));
    unsigned long i, j;
	double res;

    C[0] = 1;

    for(i = 1; i <= n; i++)
    {
        for(j = min(i, k); j > 0; j--)
            C[j] += C[j-1];
    }

    res = C[k];  // Store the result before freeing memory

    free(C);  // free dynamically allocated memory to avoid memory leak

    return res;
}