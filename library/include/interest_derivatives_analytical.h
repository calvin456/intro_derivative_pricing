//interest_derivatives_analytical.h

#include<vector>
using namespace std;

double p_t(double rate, double tenor); //compute the zcp

//compute annuity of swap
double annuity_swap(const std::vector<std::vector<double>>& zcps, size_t start, size_t end);
//swap-rate formulas
double swap_rate(const std::vector<std::vector<double>>& zcps, double tenor);

double swap_rate_co_initial(const std::vector<std::vector<double>>& zcps, double tenor);

//discount from swap-rates bootstraping

//do the same for co-initial rate. i.e.  w/equal start date and variable end date
void discount_from_swap_rate_co_initial(const std::vector<std::vector<double>> & swap_rates, std::vector<std::vector<double>>& dsct_factors);

//co-terminal swap rate, i.e. All fwd swap rate share the same terminal date
void discount_from_swap_rate_co_terminal(const std::vector<std::vector<double>>& swap_rates, std::vector<std::vector<double>>& dsct_factors);

//Black formulas - European options analytical formulas

//caplet - call option on libor rate
double black_formula_caplet(double annuity, double fwd_libor, double t1, double t2, double strike, double vol);

//floorlet - put option on libor rate
double black_formula_floorlet(double annuity, double fwd_libor, double t1, double t2, double strike, double vol);

//payer swaption - call option on option on swap contract. Pays swap rate
double black_formula_payer_swaption(double annuity, double swap_rate, double strike, double vol, double expiry);

//receiver swaption - put option on option on swap contract. Receive swap rate
double black_formula_rec_swaption(double annuity, double swap_rate, double strike, double vol, double expiry);

//compute vega for payer swaption
double black_swaption_vega(double annuity, double swap_rate, double strike, double vol, double expiry);

