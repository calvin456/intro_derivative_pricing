// main.cpp

/*
b.11 project 9: Simple interest-rate derivative pricing

test analytical functions
outdated. Post-crisis multi-curve framework + collateral. Formulas should be rewritten
negative rates -> implication??
*/


#include <vector>
#include <iostream>
#include <fstream>
#include <interest_derivatives_analytical.h>
using namespace std;

int main(){

	try{

		//p.307 our discount curve

		vector<vector<double>> dsct_rates(25, vector<double>(2, 0));

		dsct_rates[0][0] = 0;
		dsct_rates[0][1] = 1;

		dsct_rates[1][0] = 0.5;
		dsct_rates[1][1] = 0.975609756;

		dsct_rates[2][0] = 1;
		dsct_rates[2][1] = 0.949991019;

		dsct_rates[3][0] = 1.5;
		dsct_rates[3][1] = 0.923971427;

		dsct_rates[4][0] = 2;
		dsct_rates[4][1] = 0.898032347;

		dsct_rates[5][0] = 2.5;
		dsct_rates[5][1] = 0.872449235;

		dsct_rates[6][0] = 3;
		dsct_rates[6][1] = 0.847375747;

		dsct_rates[7][0] = 3.5;
		dsct_rates[7][1] = 0.822893781;

		dsct_rates[8][0] = 4;
		dsct_rates[8][1] = 0.799043132;

		dsct_rates[9][0] = 4.5;
		dsct_rates[9][1] = 0.775839012;

		dsct_rates[10][0] = 5;
		dsct_rates[10][1] = 0.753282381;

		dsct_rates[11][0] = 5.5;
		dsct_rates[11][1] = 0.73136604;

		dsct_rates[12][0] = 6;
		dsct_rates[12][1] = 0.710078203;

		dsct_rates[13][0] = 6.5;
		dsct_rates[13][1] = 0.689404609;

		dsct_rates[14][0] = 7;
		dsct_rates[14][1] = 0.669329748;

		dsct_rates[15][0] = 7.5;
		dsct_rates[15][1] = 0.649837584;

		dsct_rates[16][0] = 8;
		dsct_rates[16][1] = 0.630911969;

		dsct_rates[17][0] = 8;
		dsct_rates[17][1] = 0.630911969;

		dsct_rates[18][0] = 8.5;
		dsct_rates[18][1] = 0.61253689;

		dsct_rates[19][0] = 9;
		dsct_rates[19][1] = 0.594696597;

		dsct_rates[20][0] = 9.5;
		dsct_rates[20][1] = 0.577375683;

		dsct_rates[21][0] = 10;
		dsct_rates[21][1] = 0.560559119;

		dsct_rates[22][0] = 10.5;
		dsct_rates[22][1] = 0.544232274;

		dsct_rates[23][0] = 11;
		dsct_rates[23][1] = 0.52838092;

		dsct_rates[24][0] = 11.5;
		dsct_rates[24][1] = 0.512991226;

		//compute swap rates 
		vector<vector<double>> swap_co_init(25, vector<double>(2, 0));
		vector<vector<double>> swap_co_ter(25, vector<double>(2, 0));

		//cout << "co-terminal swap rate" << endl; cout << endl;
		for (size_t i(0); i < dsct_rates.size(); ++i){
			//swap co-terminal
			swap_co_ter[i][0] = dsct_rates[i][0];
			swap_co_ter[i][1] = swap_rate(dsct_rates, dsct_rates[i][0]);

			swap_co_init[i][0] = dsct_rates[i][0];
			swap_co_init[i][1] = swap_rate_co_initial(dsct_rates, dsct_rates[i][0]);
		}

		vector<vector<double>> dsct_rte_co_ter(25, vector<double>(2, 0));
		discount_from_swap_rate_co_terminal(swap_co_ter, dsct_rte_co_ter);

		vector<vector<double>> dsct_rte_co_init(25, vector<double>(2, 0));
		discount_from_swap_rate_co_initial(swap_co_init, dsct_rte_co_init);

		cout << "\t" << "co-terminal" << "\t\t" << "co-initial" << endl;
		cout << "tenor\t " << "dsct rte\t " << "swap rte\t " << "dsct rte\t " << "swap rte\t " << "dsct rte\t " << endl;

		for (size_t i(0); i < dsct_rates.size(); ++i){
			cout << dsct_rates[i][0] << "\t "
				<< dsct_rates[i][1] << "\t "

				<< swap_co_ter[i][1] << "\t "
				<< dsct_rte_co_ter[i][1] << "\t "

				<< swap_co_init[i][1] << "\t "
				<< dsct_rte_co_init[i][1]
				<< endl;
		}

		//project 10 price caplet and FRA
		//price a FRA and caplet starting in ten 10 years current fwd rate .06, strike .07, vol .2,
		//price of the zcp expiring in ten years .5 
		//and they are both of length .5

		cout << "caplet " << black_formula_caplet(.9, .06, 10.0, 10.5, .07, .20) << endl;

		cout << "floorlet " << black_formula_floorlet(.9, .06, 10.0, 10.5, .07, .20) << endl;

		//price European swaption using co-terminal rates
		cout << "payer swaption " <<
			black_formula_payer_swaption(annuity_swap(dsct_rates, 0, 24),
			swap_co_ter[0][1], .06, .15, swap_co_ter[24][0]) << endl;

		cout << "receiver swaption " <<
			black_formula_rec_swaption(annuity_swap(dsct_rates, 0, 24),
			swap_co_ter[0][1], .06, .15, swap_co_ter[24][0]) << endl;

		

		//--------------------------------------------------------------------------------------------------------

		double tmp;
		cin >> tmp;

		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "unknown error" << std::endl;
		return 1;
	}



}