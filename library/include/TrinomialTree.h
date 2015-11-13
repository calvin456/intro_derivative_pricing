/*
ex 8.3 write a trinomial tree class

Pricing Options Using Trinomial Trees
Paul Clifford Yan Wang Oleg Zaboronski Kevin Zhang
29.11.2010

www2.warwick.ac.uk/ fac/ sci/ maths/ people/ staff/ oleg_zaboronski/ fm/ trinomial_tree_2008.pdf

*/

#ifndef TRINOMIAL_TREE_H
#define TRINOMIAL_TREE_H

#pragma warning( disable : 4786 )


#include <TreeProducts.h>
#include <vector>
#include <Parameters.h>

namespace MyTrinomialTree{ // To avoid naming conflict with QL

	class TrinomialTree
	{

	public:
		TrinomialTree(double Spot_,
			const Parameters& r_,
			const Parameters& d_,
			double Volatility_,
			unsigned long Steps,
			double Time);


		double GetThePrice(const TreeProduct& TheProduct);

		//protected:

		void BuildTree();

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

		std::vector<std::vector<std::pair<double, double> > > TheTree;

	};


}

#endif
