/*
ex. 9.2 Take your favourite numerical integration routine,e.g. the trapezium rule, and write a template routine to carry it out
*/

#include"FuncToEval.h"

#include<NumericalIntegration.h>
#include<NumericalRule.h>

#include<iostream>
using namespace std;

int main(){

	double Tolerance(1e-6);
	double Low(0.0);
	double High(1.0);
	unsigned long Steps(100);

	//----------------------------------------------------------------
	cout << "1.0/((x + 1.0) * (x + 1.0))" << endl << endl;

	Func1 myFunc;
	
    Trapezium_rule<Func1> rule(Low, High, myFunc);

	double result = Numerical_integration<Trapezium_rule,Func1>(Tolerance,Steps,rule);
    
	cout << "test trapezium rule : \t " ;
    cout << "result " << result << "\n";
	//--------------------------------------------------------------
	Midpoint_rule<Func1> rule1(Low, High, myFunc);

	double result1 = Numerical_integration<Midpoint_rule,Func1>(Tolerance,Steps,rule1);
    
	cout << "test midpoint rule : \t ";
    cout << "result " << result1 << "\n";
	//-----------------------------------------------------------
	Simpson_rule<Func1> rule2(Low, High, myFunc);

	double result2 = Numerical_integration<Simpson_rule,Func1>(Tolerance,Steps,rule2);
    
	cout << "test Simpson's rule : \t ";
    cout << " result " << result2 << "\n";

	//----------------------------------------------------------

	cout << endl << "exp(-(x *x))" << endl << endl;

	Func2 myFunc1;

	Trapezium_rule<Func2> rule3(Low, High, myFunc1);

	double result3 = Numerical_integration<Trapezium_rule, Func2>(Tolerance, Steps, rule3);

	cout << "test trapezium rule : \t ";
	cout << "result " << result3 << "\n";
	//--------------------------------------------------------------
	Midpoint_rule<Func2> rule4(Low, High, myFunc1);

	double result4 = Numerical_integration<Midpoint_rule, Func2>(Tolerance, Steps, rule4);

	cout << "test midpoint rule : \t ";
	cout << "result " << result4 << "\n";
	//-----------------------------------------------------------
	Simpson_rule<Func2> rule5(Low, High, myFunc1);

	double result5 = Numerical_integration<Simpson_rule, Func2>(Tolerance, Steps, rule5);

	cout << "test Simpson's rule : \t ";
	cout << "result " << result5 << "\n";

	//----------------------------------------------------------

	cout << endl << "sqrt(x) * exp(-x)" << endl << endl;

	Func3 myFunc3;

	Trapezium_rule<Func3> rule6(Low, High, myFunc3);

	double result6 = Numerical_integration<Trapezium_rule, Func3>(Tolerance, Steps, rule6);

	cout << "test trapezium rule : \t ";
	cout << "result " << result6 << "\n";
	//--------------------------------------------------------------
	Midpoint_rule<Func3> rule7(Low, High, myFunc3);

	double result7 = Numerical_integration<Midpoint_rule, Func3>(Tolerance, Steps, rule7);

	cout << "test midpoint rule : \t ";
	cout << "result " << result7 << "\n";
	//-----------------------------------------------------------
	Simpson_rule<Func3> rule8(Low, High, myFunc3);

	double result8 = Numerical_integration<Simpson_rule, Func3>(Tolerance, Steps, rule8);

	cout << "test Simpson's rule : \t ";
	cout << "result " << result8 << "\n";

	//----------------------------------------------------------

	cout << endl << "pow(x,2.5)/((x + 1.0) * (x + 1.0))" << endl << endl;

	Func4 myFunc4;

	Trapezium_rule<Func4> rule9(Low, High, myFunc4);

	double result9 = Numerical_integration<Trapezium_rule, Func4>(Tolerance, Steps, rule9);

	cout << "test trapezium rule : \t ";
	cout << "result " << result9 << "\n";
	//--------------------------------------------------------------
	Midpoint_rule<Func4> rule10(Low, High, myFunc4);

	double result10 = Numerical_integration<Midpoint_rule, Func4>(Tolerance, Steps, rule10);

	cout << "test midpoint rule : \t ";
	cout << "result " << result10 << "\n";
	//-----------------------------------------------------------
	Simpson_rule<Func4> rule11(Low, High, myFunc4);

	double result11 = Numerical_integration<Simpson_rule, Func4>(Tolerance, Steps, rule11);

	cout << "test Simpson's rule : \t ";
	cout << "result " << result11 << "\n";

	//----------------------------------------------------------

	double tmp;
	cin >> tmp;

	return 0;
}