//main.cpp

/*
std::auto_ptr<> deprecated since C++11. std::unique_ptr<> should be preferred instead.

*/

/*
//use of pointer
#include<iostream>
using namespace std;

int main(){

	int firstvalue = 5, secondvalue = 15;
	int * p1, * p2;

	p1 = &firstvalue;
	p2 = &secondvalue;

	*p1 = 10;
	*p2 = *p1;

	p1 = p2; //p1 = p2 (value of pointer is copied)
	*p1=20;

	cout << "firstvalue is " << firstvalue << endl;
	cout << "secondvalue is " <<  secondvalue << endl;

	double tmp;
    cin >> tmp;

	return 0;

}
*/

// auto_ptr example
#include <iostream>
#include <memory>

int main() {
	std::auto_ptr<int> p1(new int);
	*p1.get() = 10;

	std::auto_ptr<int> p2(p1);

	std::cout << "p2 points to " << *p2 << '\n';
	// (p1 is now null-pointer auto_ptr)

	double tmp;
	std::cin >> tmp;

	return 0;
}

