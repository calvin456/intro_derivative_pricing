//main.cpp

//Compute implied vol for exotic part using QuantLib. Analytical pricer fails test so far. 


#include <iostream>

#include "heston_ql.h"
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
		Real sigma = .05; //.2
		Real rho = 0.0;

		cout << "Heston Price Vanilla Call - ATM: " << endl;

		cout << "tenor\t " << "price\t " << "implied vol" << endl;

		Date todaysDate(01, Jan, 2000);
		Date settlementDate(03, Jan, 2000);
		Date maturity(31, Jan, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "1 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(28, Feb, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "2 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Mar, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "3 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(30, Apr, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "4 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, May, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "5 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(30, Jun, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "6 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Jul, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "7 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Aug, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "8 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(30, Sep, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "9 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Oct, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "10 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(30, Nov, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "11 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Dec, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "12 month " << price << "\t " << iv << endl;


		//---------------------------------------------------------------------------------------------------------------------
		strike = 105.0;

		cout << endl << "Heston Price Vanilla Call - ATB 115%: " << endl;

		cout << "tenor\t " << "price\t " << "implied vol" << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Jan, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		//iv = implied_vol_ql(todaysDate, settlementDate, maturity, 100.0, 100.0, price, 0.0, 0.05, 0.1);

		cout << "1 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(28, Feb, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "2 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Mar, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "3 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(30, Apr, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "4 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, May, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "5 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(30, Jun, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "6 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Jul, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "7 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Aug, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "8 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(30, Sep, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "9 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Oct, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "10 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(30, Nov, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

		iv = implied_vol_ql(todaysDate, settlementDate, maturity, underlying, strike, price, dividendYield, riskFreeRate, volatility);

		cout << "11 month " << price << "\t " << iv << endl;

		todaysDate = Date(01, Jan, 2000);
		settlementDate = Date(03, Jan, 2000);
		maturity = Date(31, Dec, 2000);

		price = heston_ql_call(todaysDate, settlementDate, maturity, underlying, strike, dividendYield, riskFreeRate, volatility, kappa, sigma, rho);

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