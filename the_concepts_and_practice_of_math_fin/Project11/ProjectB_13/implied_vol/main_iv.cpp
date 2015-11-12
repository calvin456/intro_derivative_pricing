//main.cpp

//Compute implied vol for swaption using QuantLib. 

// BGM model has flat volatility. Needs to be reworked to get abcd var-cov structure.

#include <iostream>

#include "swaption_lmm_ql.h"

using namespace std;
using namespace QuantLib;



int main(int argc, char **argv) {

	try {

		Real Spot0(.04);

		double Strike(.06);
		double Expiry(.05);
		unsigned long NumberOfDates(12);

		//Rate Numeraire(1);

		double correl(.1);
		double a(.05);
		double b(.09);
		double c(.44);
		double d(.11);

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(01, Jan, 2006);

		//Real ql_lmm_swaption,ql_iv_lmm_swaption;
		Rate s(0.005);

		Size start(1);
		Size length(2);

		cout << "swaption " << start << "X" << length -1 <<  ": " << endl;
		
		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0);i < 9;++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d); 

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d); 

			cout << "interest rate : " << Spot0 << " - " <<	ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}

		length = 6;

		cout << endl << "swaption " << start << "X" << length - 1 << ": " << endl;

		Spot0 = 0.04;
		

		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0); i < 9; ++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d);

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

			cout << "interest rate : " << Spot0 << " - " << ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}

		length = 11;

		cout << endl << "swaption " << start << "X" << length - 1 << ": " << endl;

		Spot0 = 0.04;

		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0); i < 9; ++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d);

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

			cout << "interest rate : " << Spot0 << " - " << ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}


		start = 5,length = 2;

		cout << endl << "swaption " << start << "X" << length - 1 << ": " << endl;

		Spot0 = 0.04;

		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0); i < 9; ++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d);

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

			cout << "interest rate : " << Spot0 << " - " << ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}


		length = 6;

		cout << endl << "swaption " << start << "X" << length - 1 << ": " << endl;

		Spot0 = 0.04;

		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0); i < 9; ++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d);

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

			cout << "interest rate : " << Spot0 << " - " << ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}

		length = 11;

		cout << endl << "swaption " << start << "X" << length - 1 << ": " << endl;

		Spot0 = 0.04;

		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0); i < 9; ++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d);

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

			cout << "interest rate : " << Spot0 << " - " << ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}

		start = 10,length = 2;

		cout << endl << "swaption " << start << "X" << length - 1 << ": " << endl;

		Spot0 = 0.04;

		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0); i < 9; ++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d);

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

			cout << "interest rate : " << Spot0 << " - " << ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}

		start = 10, length = 6;

		cout << endl << "swaption " << start << "X" << length - 1 << ": " << endl;

		Spot0 = 0.04;

		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0); i < 9; ++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d);

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

			cout << "interest rate : " << Spot0 << " - " << ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}

		start = 10, length = 11;

		cout << endl << "swaption " << start << "X" << length - 1 << ": " << endl;

		Spot0 = 0.04;

		// calculate swaption price starting w / strike 400 bps and increase by 2 bps up to 800 bps

		//European swaption 

		cout << "implied vol :" << endl;

		for (size_t i(0); i < 9; ++i){

			double ql_lmm_swaption = swaption_lmm(todaysDate, start, length, Spot0, Strike, correl, a, b, c, d);

			double ql_iv_lmm_swaption = swaption_iv_lmm(todaysDate, start, length, ql_lmm_swaption, Spot0, Strike, correl, a, b, c, d);

			cout << "interest rate : " << Spot0 << " - " << ql_lmm_swaption << " - " << ql_iv_lmm_swaption << endl;

			Spot0 += s;
		}


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