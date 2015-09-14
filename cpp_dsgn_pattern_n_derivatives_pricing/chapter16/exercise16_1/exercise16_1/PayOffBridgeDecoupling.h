// PayOffBridgeDecoupling.h

/*
ex 16.2 Implement a class using the PIMPL idiom

pimpl : pointer to implementation

the bridge pattern - pimpl

ref: C++ Design Pattern Advanced C++ Programming Seminar, Summer Term 2009
Georg Altmann, University Erlangen-Nurember - System Simulation, 04/06/2009

*/


#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H

#include<memory>

class PayOff; // forward declaration of impl

class PayOffBridge
{
public:

	PayOffBridge(const PayOffBridge& original);
	PayOffBridge(const PayOff& innerPayOff);

	double operator()(double Spot) const;
	~PayOffBridge();
	PayOffBridge& operator=(const PayOffBridge& original);

private:

	PayOff* ThePayOffPtr;//pointer to impl
	
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
