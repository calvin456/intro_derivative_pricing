//libor_in_arrear_fra_analytical.cpp

#include "libor_in_arrear_fra_analytical.h"
#include <cmath>

using namespace std;

//analytical formula for libror in arrear FRA
//use zcp t1 as numeraire 
//assume f rate are log-normal

//In-arrear products have a convexity correction.

double libor_in_arrear_fra(double fwd_rte, double strike, double vol, double t0, double t1) {

	double tau(t1 - t0);

	double vol_square(vol*vol*tau*tau);

	//convexity correction
	double cc(tau * fwd_rte * fwd_rte / (1.0 + tau * fwd_rte) * exp(vol_square));

	double fwd_rte_in_arrear(fwd_rte + cc);

	return tau * (fwd_rte_in_arrear - strike);



}