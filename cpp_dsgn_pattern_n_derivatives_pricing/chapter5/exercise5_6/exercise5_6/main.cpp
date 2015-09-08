// main.cpp


/*
Write a template class that implements a reference counted wrapper.

This will be similar to the wrapper class but instead of making a clone of the inner object when the wrapper
is copied, an internal counter is increased and the inner object is shared.

When a copy is destroyed, the inner counter is decremented.

When the inner counter reaches zero, the object is destroyed.

Note that both the counter and the inner object will be shared across copies of the object.
*/

#include<iostream>

#include<PayOff3.h>

#include"ref_count_wrapper.h"

using namespace std;

int main()
{
	//test shared wrapper class by emza0114

	double Strike(100.0);

	PayOffCall call_payoff(Strike);

	SharedWrapper<PayOff> payoff1(call_payoff);
	SharedWrapper<PayOff> payoff2(call_payoff);

	cout << "1st instance w/ spot @ 100 : ";
	cout << payoff1->operator()(100.0) << endl;
	cout << "2nd instance w/ spot @ 120 : ";
	cout << payoff2->operator()(120.0) << endl;

	double tmp;
	cin >> tmp;

	return 0;
}