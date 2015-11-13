// pay_off_factory_multi.h

//ex 10.2 Our class cannot handle a double digital as it needs two strkes.
//Work out a solution that will handle options w/ multiple parameters

/*
ref. taken from quant finance books forum @ markjoshi.com.

Chap. 10, pb 2 (again)

Postby akbar » Sat Feb 26, 2011 11:17 pm
"Our class cannot handle a double digital as it needs two strikes. Work out a solution that will handle options with multiple parameters".

In one of the earlier posts of the forum, mj mentioned that the "short solution" to this problem is to use an array instead of a double to pass an arbitrary number of parameter. I assume this applies to the PayoffFactory::CreatePayoff(ID,double) and PayoffHelper<T>::Create(double) methods, along with the CreatePayOffFunction function pointer type definition.

However, using an array instead of a double means that an additional constructor, taking an array of doubles as argument, needs to be implemented for each of the classes of the PayOff inheritance hierarchy that have been developed so far in the book. This in order to be compatible with this new representation.
And there are a few of them: call, put, double digital, forward...

Above the fact that we clearly violate the open-closed principle, the solution appears far from short in the end. Is it the right approach, or is there a more elegant way of proceeding with mj's suggestion?
Maybe there is simply something that I've missed.
Thanks for you help in advance.

akbar	
     
    Posts: 28
    Joined: Fri Aug 10, 2007 7:12 pm

Top
Re: Chap. 10, pb 2 (again)

Postby mj » Sun Feb 27, 2011 2:44 am
the elegant solution is the one later in the book where we do template factories.

A solution that doesn't change the existing structure is not viable here.

mj	
    Site Admin
     
    Posts: 1361
    Joined: Fri Jul 27, 2007 7:21 am

Top
Re: Chap. 10, pb 2 (again)

Postby MoonDragon » Sun Apr 08, 2012 7:42 pm

    mj wrote:
    the elegant solution is the one later in the book where we do template factories.



Hello, is this part in the first version of your book (i only have this last)?

Regards

MoonDragon	
     
    Posts: 18
    Joined: Mon Jan 30, 2012 4:21 pm

Top
Re: Chap. 10, pb 2 (again)

Postby mj » Wed Apr 11, 2012 10:20 am
this is in the second ed only.

mj	
    Site Admin
     
    Posts: 1361
    Joined: Fri Jul 27, 2007 7:21 am 
*/

//test git diff

#ifndef PAYOFF_FACTORY_H
#define PAYOFF_FACTORY_H

#include <PayOff3.h>

#include <map>
#include <string>
#include <memory>
#include <Arrays.h>

using namespace std;


class PayOffFactory
{
public:
	typedef PayOff* (*CreatePayOffFunction)(const MJArray&);
	
	static PayOffFactory& Instance();

	void RegisterPayOff(string, CreatePayOffFunction);

	PayOff* CreatePayOff(string PayOffId, const MJArray& args);

	~PayOffFactory(){}

private:
	map<string, CreatePayOffFunction> TheCreatorFunctions;
	PayOffFactory(){}
	PayOffFactory(const PayOffFactory&){}
	PayOffFactory& operator=(const PayOffFactory&){ return *this; }

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
