//Vanilla3Template.h
/*
ex 9.3 Write a routine to price a vanilla option by Monte-Carlo or trees where the pay-off is passed in 
as a template param express via a function object

*/

#ifndef VANILLA_OPTION_TEMPLATE
#define VANILLA_OPTION_TEMPLATE

#include<vector>
#include <Arrays.h>

using namespace std;

template<class T>
class VanillaOptionTemplate
{
public:
    VanillaOptionTemplate(const T& ThePayOff_, double Expiry_) ;

    double OptionPayOff(double Spot) const;
	//double OptionPayOff(const std::vector<double>& Spots) const; //overload 1x
	double OptionPayOff(const MJArray& Spots) const; //overload 1x

	double GetExpiry() const;
	double GetStrike() const;
	void SetStrike(double Strike_);
	void SetExpiry(double Expiry_);

private:
	T _ThePayOff;
    double Expiry;
};

#endif

