//
//
//
//                               SimpleMC7.h
// 
//

#ifndef SIMPLEMC7_H
#define SIMPLEMC7_H

#include <Vanilla3.h>
#include <Parameters.h>
#include <MCStatistics.h>

#include<Terminator.h>

void SimpleMonteCarlo5(const VanillaOption& TheOption, 
						 double Spot,
						 const Parameters& Vol, 
						 const Parameters& r,
                         unsigned long NumberOfPaths,
						 StatisticsMC& gatherer);

/*
Exercice 5.4 Use the strategy pattern to allow the user to spec termination
conditions for MC, e.g., time spent on paths done
*/
						 
void SimpleMonteCarlo51(const VanillaOption& TheOption, 
						 double Spot,
						 const Parameters& Vol, 
						 const Parameters& r,
                         unsigned long NumberOfPaths,
						 StatisticsMC& gatherer,
						 Terminator& Terminator_);						 
						 


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

