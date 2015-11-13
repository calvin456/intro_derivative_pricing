//Vanilla3Template.cpp

#include "Vanilla3Template.h"

template<class T> 
VanillaOptionTemplate<T>::VanillaOptionTemplate(const T& ThePayOff_, double Expiry_) 
	:  _ThePayOff(ThePayOff_), Expiry(Expiry_)
{}

template<class T> 
double VanillaOptionTemplate<T>::OptionPayOff(double Spot) const{
	return _ThePayOff(Spot);
	
}
/*
template<class T>
double VanillaOptionTemplate<T>::OptionPayOff(const std::vector<double>& Spots) const{
	return _ThePayOff(Spots);

}
*/
template<class T>
double VanillaOptionTemplate<T>::OptionPayOff(const const MJArray& Spots) const{
	return _ThePayOff(Spots);

}

template<class T> 
double VanillaOptionTemplate<T>::GetExpiry() const{
	return Expiry;
	
}

template<class T>
double VanillaOptionTemplate<T>::GetStrike() const
{
	return _ThePayOff.GetStrike();
}

template<class T>
void VanillaOptionTemplate<T>::SetExpiry(double Expiry_)
{
	Expiry = Expiry_;
}

template<class T>
void VanillaOptionTemplate<T>::SetStrike(double Strike_)
{
	return _ThePayOff.SetStrike(Strike_);
}