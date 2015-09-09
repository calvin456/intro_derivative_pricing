//WrapperMain.cpp

/*
reproduced from p. 193, C++ Design Patterns and Derivatives Pricing,
2nd ed, Mark S. Joshi, 2008
*/

//
//		requires PayOff3.cpp

#include <iostream>
#include <wrapper2.h>
#include <PayOff3.h>

using namespace std;

int main(){

	double S;
	double K1, K2;

	cout << " spot\n";
	cin >> S;

	cout << "strike1\n";
	cin >> K1;

	cout << "strike2\n";
	cin >> K2;

	PayOffCall one(K1);
	PayOffPut two(K2);

	PayOff* p = one.clone();
	Wrapper<PayOff> four = p;

	{
		PayOff* q = two.clone();
		Wrapper<PayOff> five = q;

		cout << "four :" << (*four)(S);
		cout << " five :" << (*five)(S) << endl;

		four = five;
	}
	cout << "four :" << (*four)(S) << "\n";

	char c;
	cin >> c;

	return 0;
}