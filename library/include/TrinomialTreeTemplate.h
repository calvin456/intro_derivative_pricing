//TrinomialTreeTemplate.h

/*
ex 9.3 Write a routine to price a vanilla option by Monte-Carlo or trees where the pay-off is passed in
as a template param express via a function object

Derive class will not be able to price American options

*/

#ifndef TRINOMIAL_TREE_TEMPLATE_H
#define TRINOMIAL_TREE_TEMPLATE_H

#include <PayOff3.h>
#include <vector>
#include <Parameters.h>

using namespace std;

class TrinomialTreeTemplate
{

public:
	TrinomialTreeTemplate(double Spot_,
							const Parameters& r_,
							const Parameters& d_,
							double Volatility_,
							unsigned long Steps_,
							double Time_)
	: Spot(Spot_), r(r_), d(d_), Volatility(Volatility_), Steps(Steps_), Time(Time_)
	{
		TreeBuilt = false;

		double deltaT = (double)(Time / Steps);
		up = exp(Volatility * sqrt(2.0 * deltaT));
		down = 1 / up;
		double a = exp(Volatility * sqrt(deltaT / 2.0));

		prob_up = pow((exp(r.Integral(0.0, deltaT / 2.0) - d.Integral(0.0, deltaT / 2.0)) - 1 / a) / (a - 1 / a), 2) *
					exp(-1.0 * r.Integral(0.0, deltaT));

		prob_down = pow((a - exp(r.Integral(0.0, deltaT / 2.0) - d.Integral(0.0, deltaT / 2.0))) / (a - 1 / a), 2) *
					exp(-1.0 * r.Integral(0.0, deltaT));

		prob_no_move = exp(-1.0  * r.Integral(0.0, deltaT)) - prob_up - prob_down;

	}

	void BuildTree()
	{
		TreeBuilt = true;
		TheTree.resize(Steps + 1);

		for (unsigned long i = 0; i <= Steps; i++){

			TheTree[i].resize(1 + i * 2);

			for (long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j = j + 1, k++)
				TheTree[i][k].first = Spot * pow(up, j);
		}

	}

	template<typename T>
	double GetThePrice(const T& TheProduct)
	{
		if (!TreeBuilt)	BuildTree();

		double deltaT = (double)(Time / Steps);

		for (long j = -static_cast<long>(Steps), k = 0; j <= static_cast<long>(Steps); j = j + 1, k++)
			TheTree[Steps][k].second = TheProduct.FinalPayOff(TheTree[Steps][k].first);

		for (unsigned long i = 1; i <= Steps; i++){
			unsigned long index = Steps - i;

			for (long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j = j + 1, k++){
				double Spot = TheTree[index][k].first;

				TheTree[index][k].second = prob_down*TheTree[index + 1][k].second +
					prob_no_move * TheTree[index + 1][k + 1].second + prob_up * TheTree[index + 1][k + 2].second;
			}
		}

		return TheTree[0][0].second;
	}

private:

	double Spot;
	Parameters r;
	Parameters d;
	double Volatility;
	unsigned long Steps;
	double Time;
	bool TreeBuilt;

	double up;
	double down;
	double prob_up;
	double prob_no_move;
	double prob_down;

	vector<vector<pair<double, double> > > TheTree;
};

#endif
