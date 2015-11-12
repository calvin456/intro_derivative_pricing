// main_num_int.cpp

/*

compute FRA in-arrears price
*/

#include<iostream>
#include<limits>

#include "libor_in_arrear_fra_analytical.h"

#include "function_to_eval.h"

#include <NumericalIntegration.h>
#include <NumericalRule.h>

using namespace std;

int main(int argc, char **argv) {

	try {

		double fwd_rte(0.06);
		double strike(0.07);
		double vol(.20);
		double t0(10);
		double t1(10.5);
		double numeraire(.5);

		//analytical pricing FRA in-arrears

		cout << "analytical pricing FRA in-arrears : ";

		cout << numeraire * libor_in_arrear_fra(fwd_rte, strike, vol, t0, t1) << endl;

		//numerical integration pricing FRA in-arrears

		cout << "numerical integration pricing FRA in - arrears" << endl;

		FuncToEval myFunc(fwd_rte, strike, vol, t0, t1, fwd);

		double Tolerance(1e-6);
		double Low(1.0e-10);
		double High(10.0);
		unsigned long Steps(100);

		Trapezium_rule<FuncToEval> rule(Low, High, myFunc);

		double result = numeraire * Numerical_integration<Trapezium_rule, FuncToEval>(Tolerance, Steps, rule);

		cout << "test trapezium rule : " << endl;
		cout << "\n result " << result << "\n";

		//--------------------------------------------------------------
		Midpoint_rule<FuncToEval> rule1(Low, High, myFunc);

		double result1 = numeraire * Numerical_integration<Midpoint_rule, FuncToEval>(Tolerance, Steps, rule1);

		cout << "test midpoint rule : " << endl;
		cout << "\n result " << result1 << "\n";
		//-----------------------------------------------------------
		Simpson_rule<FuncToEval> rule2(Low, High, myFunc);

		double result2 = numeraire * Numerical_integration<Simpson_rule, FuncToEval>(Tolerance, Steps, rule2);

		cout << "test Simpson's rule : " << endl;
		cout << "\n result " << result2 << "\n";

		//----------------------------------------------------------


		//numerical integration pricing caplet FRA in-arrears
		//Split integral and compute non-zero part. Start from strike rate up to "infinity"

		Low = 1.0e-10;
		High = 10.0;

		FuncToEval myFunc1(fwd_rte, strike, vol, t0, t1, caplet);

		Trapezium_rule<FuncToEval> rule3(Low, High, myFunc1);

		double result3 = numeraire * Numerical_integration<Trapezium_rule, FuncToEval>(Tolerance, Steps, rule3);

		cout << "test trapezium rule : " << endl;
		cout << "\n result " << result3 << "\n";
		//--------------------------------------------------------------
		Midpoint_rule<FuncToEval> rule4(Low, High, myFunc1);

		double result4 = numeraire * Numerical_integration<Midpoint_rule, FuncToEval>(Tolerance, Steps, rule4);

		cout << "test midpoint rule : " << endl;
		cout << "\n result " << result4 << "\n";
		//-----------------------------------------------------------
		Simpson_rule<FuncToEval> rule5(Low, High, myFunc1);

		double result5 = numeraire * Numerical_integration<Simpson_rule, FuncToEval>(Tolerance, Steps, rule5);

		cout << "test Simpson's rule : " << endl;
		cout << "\n result " << result5 << "\n";

		//----------------------------------------------------------



		double tmp;
		cin >> tmp;

		return 0;
	


	}
	catch (exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error" << endl;
		return 1;
	}
}