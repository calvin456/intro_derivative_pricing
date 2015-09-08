//main.cpp

/*
exercise 4.1

run code compiled w/ gcc 4.8.1-4 vs cl 18.00.31101 on CPU every thing else being equal

gcc printf: 0.002

cl printf: 0.003

*/

#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

int main(){
	clock_t start;
	double duration;
	int i, n, p;
	double * pointer;

	start = clock();
	n = 0;
	p = 5;

	while (n<10000){

		pointer = new double[p];

		for (i = 0; i<p; i++){
			pointer[i] = i;
		}

		delete[] pointer;
		n++;

	}

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	cout << "printf: " << duration << '\n';

	double tmp;
	cin >> tmp;

	return 0;

}