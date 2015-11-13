//
//
//                   Vanilla3.h
//
//

//Add get and set method to vanilla option class


#ifndef VANILLA_3_H
#define VANILLA_3_H

#include <PayOffBridge.h>
#include<memory>

namespace Vanilla{ //To avoid conflict with QuantLib

	class VanillaOption
	{
	public:

		VanillaOption(const PayOffBridge& ThePayOff_, double Expiry);

		double OptionPayOff(double Spot) const;
		double GetExpiry() const;
		double GetStrike() const;
		void SetStrike(double Strike_);
		void SetExpiry(double Expiry_);
	private:

		double Expiry;
		PayOffBridge ThePayOff;
	};

	//10.3

	class VanillaOption1
	{
	public:

		VanillaOption1(PayOff* ThePayOffPtr_, double Expiry);
		VanillaOption1(std::unique_ptr<PayOff>& ThePayOffPtr_, double Expiry);

		double OptionPayOff(double Spot) const;
		double GetExpiry() const;

	private:

		double Expiry;
		std::unique_ptr<PayOff> ThePayOffPtr; //smart pointer
	};

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
