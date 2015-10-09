//main.cpp

//Compute implied vol for exotic part using QuantLib. 


#include <iostream>

#include "jdp_ql.h"
#include "implied_vol_ql.h"

using namespace std;
using namespace QuantLib;

int main(int argc, char **argv) {

	try {

		Real price, iv;

		Real underlying = 100.0;
		Real strike = 100.0;
		Spread dividendYield = 0.0;
		Rate riskFreeRate = 0.05;
		Volatility volatility = .10;
		Real kappa = 1e-08;
		Real m = .9; //.2
		Real nu = 0.1;

		cout << "Merton76 Price Vanilla Call - ATM: " << endl;

		cout << "tenor\t " << "price\t " << "implied vol" << endl;

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, Jan, 2000);

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "1 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "2 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "3 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "4 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "5 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "6 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "7 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "8 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "9 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "10 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "11 month " << price << "\t " << iv << endl;


		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "12 month " << price << "\t " << iv << endl;


		//---------------------------------------------------------------------------------------------------------------------
		strike = 105.0;

		cout << endl << "Merton76 Price Vanilla Call - ATB 115%: " << endl;

		cout << "tenor\t " << "price\t " << "implied vol" << endl;

		maturity = Date(31, Jan, 2000);

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		//iv = implied_vol_ql(todaysDate, settlementDate, maturity, 100.0, 100.0, price, 0.0, 0.05, 0.1);

		cout << "1 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "2 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "3 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "4 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "5 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "6 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "7 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "8 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "9 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "10 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "11 month " << price << "\t " << iv << endl;

		maturity += 1 * Months;

		price = jdp_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, m, nu);

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