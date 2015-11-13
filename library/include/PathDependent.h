//
//
//                      PathDependent.h
//
//
//

/*
ex 7.3 Rewrite the classes here so that they pass the logs of spot values around instead of the spot values.

Show that the discrete barrier option and the geometric Asian need fewer exponentiations.
*/


#ifndef PATH_DEPENDENT_H
#define PATH_DEPENDENT_H
#include <Arrays.h>
#include <vector>

namespace MyCashFlow{ //Avoid conflict with QL

	class CashFlow
	{
	public:

		double Amount;
		unsigned long TimeIndex;

		CashFlow(unsigned long TimeIndex_ = 0UL, double Amount_ = 0.0)
			: TimeIndex(TimeIndex_),
			Amount(Amount_){};


	};
}

	typedef  enum { level, logscale } method;

	class PathDependent
	{
	public:

		PathDependent(const MJArray& LookAtTimes);

		const MJArray& GetLookAtTimes() const;

		virtual unsigned long MaxNumberOfCashFlows() const = 0;
		virtual MJArray PossibleCashFlowTimes() const = 0;
		virtual unsigned long CashFlows(const MJArray& SpotValues,
			std::vector<MyCashFlow::CashFlow>& GeneratedFlows, method method_ = logscale) const = 0;
		virtual PathDependent* clone() const = 0;

		virtual ~PathDependent(){}

	private:

		MJArray LookAtTimes;

	};



#endif

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/
