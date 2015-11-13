//options.cpp

#include <options.h>
#include <BlackScholesFormulas.h>
#include <algorithm>

using namespace std;

using namespace MyOption;

Option::Option(double Spot,
				double Strike,
				double r,
				double d,
				double Vol,
				double Expiry)
	:Spot(Spot), Strike(Strike), r(r), d(d), Vol(Vol), Expiry(Expiry)
{}

void Option::SetStrike(double Strike_) { Strike = Strike_; }
void Option::SetVol(double Vol_) { Vol = Vol_; }
void Option::SetExpiry(double Expiry_) { Expiry = Expiry_; }
void Option::Setr(double r_) { r = r_; }
void Option::Setd(double d_) { d = d_; }

CallOption::CallOption(double Spot,
						double Strike,
						double r,
						double d,
						double Vol,
						double Expiry)
	: Option(Spot, Strike, r, d, Vol, Expiry)
{}

double  CallOption::GetValue(double Spot){

	return  BSFunction::BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);

}

double  CallOption::GetValue(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);

}

double CallOption::GetValue(double Spot, double r, double Vol, double Expiry){
	return BSFunction::BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);
}

double  CallOption::GetDelta(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesCallDelta(Spot, Strike, r, d, Vol, Expiry);
}

double  CallOption::GetGamma(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesGamma(Spot, Strike, r, d, Vol, Expiry);
}


long CallOption::IsTouched(double Spot) const {

	return (Spot > Strike ? 1 : 0);
}


double CallOption::GetPayOff(double Spot) const {

	return max(Spot - Strike, 0.0);
}
//----------------------------------------------------------------------
PutOption::PutOption(double Spot,
					double Strike,
					double r,
					double d,
					double Vol,
					double Expiry)
	: Option(Spot, Strike, r, d, Vol, Expiry)
{}

double  PutOption::GetValue(double Spot){

	return BSFunction::BlackScholesPut(Spot, Strike, r, d, Vol, Expiry);

}

double  PutOption::GetValue(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesPut(Spot, Strike, r, d, Vol, Expiry);

}

double PutOption::GetValue(double Spot, double r, double Vol, double Expiry){
	return BSFunction::BlackScholesPut(Spot, Strike, r, d, Vol, Expiry);
}

double PutOption::GetPayOff(double Spot) const {

	return min(Strike-Spot, 0.0);
}

double  PutOption::GetDelta(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesCallDelta(Spot, Strike, r, d, Vol, Expiry) - 1.0;
}

double  PutOption::GetGamma(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesGamma(Spot, Strike, r, d, Vol, Expiry);
}


long PutOption::IsTouched(double Spot) const {

	return (Spot < Strike ? 1 : 0);
}




//---------------------------------------------------------------------
DigitalCallOption::DigitalCallOption(double Spot,
										double Strike,
										double r,
										double d,
										double Vol,
										double Expiry)
	: Option(Spot, Strike, r, d, Vol, Expiry)
{}

double  DigitalCallOption::GetValue(double Spot){

	return BSFunction::BlackScholesDigitalCall(Spot, Strike, r, d, Vol, Expiry);

}

double  DigitalCallOption::GetValue(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesDigitalCall(Spot, Strike, r, d, Vol, Expiry);

}

double DigitalCallOption::GetValue(double Spot, double r, double Vol, double Expiry){
	return BSFunction::BlackScholesDigitalCall(Spot, Strike, r, d, Vol, Expiry);
}

double DigitalCallOption::GetPayOff(double Spot) const {

	return Spot > Strike ? 1.0 : 0.0;
}

double  DigitalCallOption::GetDelta(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesGamma(Spot, Strike, r, d, Vol, Expiry) - 1.0;
}

double  DigitalCallOption::GetGamma(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesDigitalCallGamma(Spot, Strike, r, d, Vol, Expiry);
}


long DigitalCallOption::IsTouched(double Spot) const {

	return (Spot > Strike ? 1 : 0);
}

//----------------------------------------------------------------------
DigitalPutOption::DigitalPutOption(double Spot,
									double Strike,
									double r,
									double d,
									double Vol,
									double Expiry)
	: Option(Spot, Strike, r, d, Vol, Expiry)
{}

double  DigitalPutOption::GetValue(double Spot){

	return BSFunction::BlackScholesDigitalPut(Spot, Strike, r, d, Vol, Expiry);

}

double  DigitalPutOption::GetValue(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesDigitalPut(Spot, Strike, r, d, Vol, Expiry);

}

double DigitalPutOption::GetPayOff(double Spot) const {

	return Spot < Strike ? 1.0 : 0.0;
}

double DigitalPutOption::GetValue(double Spot, double r, double Vol, double Expiry){
	return BSFunction::BlackScholesDigitalPut(Spot, Strike, r, d, Vol, Expiry);
}

double  DigitalPutOption::GetDelta(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesGamma(Spot, Strike, r, d, Vol, Expiry) - 1.0; //?????????????????????
}

double  DigitalPutOption::GetGamma(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesDigitalCallGamma(Spot, Strike, r, d, Vol, Expiry); //??????????????????????
}


long DigitalPutOption::IsTouched(double Spot) const {

	return (Spot < Strike ? 1 : 0);
}


//---------------------------------------------------------------------
CallSpreadOption::CallSpreadOption(double Spot,
									double Strike,
									double r,
									double d,
									double Vol,
									double Expiry,
									double epsilon)
	: Option(Spot, Strike, r, d, Vol, Expiry),epsilon(epsilon)
{}

double CallSpreadOption::GetValue(double Spot){

	return BSFunction::BlackScholesCall(Spot, Strike + epsilon, r, d, Vol, Expiry) - BSFunction::BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);
}

double CallSpreadOption::GetValue(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesCall(Spot, Strike + epsilon, r, d, Vol, Expiry) - BSFunction::BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);
}

double CallSpreadOption::GetPayOff(double Spot) const {

	return max(Spot - Strike + epsilon, 0.0) - max(Spot - Strike, 0.0);
}

double CallSpreadOption::GetValue(double Spot, double r, double Vol, double Expiry){
	return BSFunction::BlackScholesCall(Spot, Strike + epsilon, r, d, Vol, Expiry) - BSFunction::BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);
}

double  CallSpreadOption::GetDelta(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesCallDelta(Spot, Strike + epsilon, r, d, Vol, Expiry) - BSFunction::BlackScholesCallDelta(Spot, Strike, r, d, Vol, Expiry);

}

double  CallSpreadOption::GetGamma(double Spot, double Vol, double Expiry){

	return BSFunction::BlackScholesGamma(Spot, Strike + epsilon, r, d, Vol, Expiry) - BSFunction::BlackScholesGamma(Spot, Strike, r, d, Vol, Expiry);
}


long CallSpreadOption::IsTouched(double Spot) const {

	return (Spot > Strike ? 1 : 0);
}

//---------------------------------------------------------------------
