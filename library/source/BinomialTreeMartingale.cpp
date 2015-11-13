

#include <BinomialTreeMartingale.h>
#include <Arrays.h>
#include <Normals.h>

#include <cmath>
#include <iostream>

using namespace std;

BinomialTreeMartingale::BinomialTreeMartingale(double Spot_,
												double Strike_,
												const Parameters& r_,
												const Parameters& d_,
												double Volatility_,
												unsigned long Steps_,
												double Time_)
	: Spot(Spot_),Strike(Strike_),r(r_),d(d_),
        Volatility(Volatility_),Steps(Steps_),Time(Time_)
{}


double BinomialTreeMartingale::GetThePrice(const TreeProduct& TheProduct,unsigned long Steps)
{
		double deltaT = (double)(Time/Steps);
		double Rn= exp(r.Integral(0.0, deltaT));
		double uN = exp(Volatility * sqrt(deltaT));
		double dN = 1/uN;
		double qN = (Rn - dN)/(uN - dN);

  		double etaN = floor(log(Strike/(Spot * pow(dN,(double)(Steps))))/log(uN/dN)) + 1.0;

		double theta1  =(etaN - Steps * qN)/sqrt(Steps * qN * (1.0 - qN));
		double tmp = qN * uN/Rn;
		double theta2  =(etaN - Steps * tmp)/sqrt(Steps * tmp * (1.0 - tmp));

		return Spot * (1.0 - CumulativeNormal(theta2) ) -
						(Strike/pow(Rn,(double)(Steps))) * (1.0 - CumulativeNormal(theta1));
}
