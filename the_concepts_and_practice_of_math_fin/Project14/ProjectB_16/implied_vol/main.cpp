//main.cpp

//Compute implied vol for exotic part using QuantLib. Analytical pricer fails test so far. 

// Was unable to compute 1-mth and 2-mth price using VG pricer from QL

#include <iostream>

#include "vg_ql.h"
#include "implied_vol_ql.h"

using namespace std;
using namespace QuantLib;

int main(int argc, char **argv) {

	try {

		Real price(0.0), iv(0.0);

		Real underlying = 100.0;
		Real strike = 100.0;
		Spread dividendYield = 0.0;
		Rate riskFreeRate = 0.05;
		Volatility volatility = .10;
		//Real kappa = 1e-08;

		Real nu = 0.2;
		Real theta = 0.0;

		cout << "VG Price Vanilla Call - ATM: " << endl;

		cout << "tenor\t " << "price\t " << "implied vol" << endl;

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, Jan, 2000);

		//price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		//iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "1 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		//price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		//iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "2 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "3 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "4 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "5 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "6 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "7 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "8 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "9 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "10 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "11 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "12 month " << price << "\t " << iv << endl;


		//---------------------------------------------------------------------------------------------------------------------
		strike = 105.0;

		price = 0.0, iv = 0.0;

		cout << endl << "Heston Price Vanilla Call - ATB 115%: " << endl;

		cout << "tenor\t " << "price\t " << "implied vol" << endl;

		maturity = Date(31, Jan, 2000);

		//price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		//iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "1 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		//price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		//iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "2 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "3 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "4 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "5 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "6 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "7 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "8 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "9 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "10 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "11 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = vg_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, nu, theta);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "12 month " << price << "\t " << iv << endl;

		//---------------------------------------------------------------------------------------------

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