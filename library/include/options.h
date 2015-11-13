//hedging_strategy.h

#ifndef OPTIONS_H
#define  OPTIONS_H



#include <vector>
#include <memory>



//Assume market maker's role
//Will not close out the position once sold
//Final p&l against option payoff


namespace MyOption{ //To avoid conflicts w/ QL

	class Option{
		//abstract class

	public:
		Option(double Spot,
			double Strike,
			double r,
			double d,
			double Vol,
			double Expiry);
		virtual ~Option(){}

		virtual double GetValue(double Spot) = 0;
		virtual double GetValue(double Spot, double Vol, double Expiry) = 0;
		virtual double GetValue(double Spot, double r, double Vol, double Expiry) = 0;

		virtual double GetDelta(double Spot, double Vol, double Expiry) = 0;
		virtual double GetGamma(double Spot, double Vol, double Expiry) = 0;

		virtual long IsTouched(double Spot) const = 0;
		virtual double GetPayOff(double Spot) const = 0;

		virtual double GetStrike() const { return Strike; }
		virtual double GetVol() const { return Vol; }
		virtual double GetExpiry() const { return Expiry; }
		virtual double Getr() const { return r; }
		virtual double Getd() const { return d; }

		virtual void SetStrike(double Strike_);
		virtual void SetVol(double Vol_);
		virtual void SetExpiry(double Expiry_);
		virtual void Setr(double r_);
		virtual void Setd(double d_);

	protected:
		double Spot;
		double Strike;
		double r;
		double d;
		double Vol;
		double Expiry;

	};

	class CallOption : public Option{

	public:
		CallOption(double Spot,
			double Strike,
			double r,
			double d,
			double Vol,
			double Expiry);
		virtual ~CallOption(){}
		virtual double GetValue(double Spot);
		virtual double GetValue(double Spot, double Vol, double Expiry);
		virtual double GetValue(double Spot, double r, double Vol, double Expiry);

		virtual double GetDelta(double Spot, double Vol, double Expiry);
		virtual double GetGamma(double Spot, double Vol, double Expiry);
		virtual long IsTouched(double Spot) const; //Buy stock when price goes above K and sell it when falls below K
		//i.e. limit order
		virtual double GetPayOff(double Spot) const;
	private:

	};

	class PutOption : public Option{

	public:
		PutOption(double Spot,
			double Strike,
			double r,
			double d,
			double Vol,
			double Expiry);
		virtual ~PutOption(){}
		virtual double GetValue(double Spot);
		virtual double GetValue(double Spot, double Vol, double Expiry);
		virtual double GetValue(double Spot, double r, double Vol, double Expiry);

		virtual double GetDelta(double Spot, double Vol, double Expiry);
		virtual double GetGamma(double Spot, double Vol, double Expiry);
		virtual long IsTouched(double Spot) const;
		virtual double GetPayOff(double Spot) const;
	private:

	};

	class DigitalCallOption : public Option{

	public:
		DigitalCallOption(double Spot,
			double Strike,
			double r,
			double d,
			double Vol,
			double Expiry);
		virtual ~DigitalCallOption(){}
		virtual double GetValue(double Spot);
		virtual double GetValue(double Spot, double Vol, double Expiry);
		virtual double GetValue(double Spot, double r, double Vol, double Expiry);

		virtual double GetDelta(double Spot, double Vol, double Expiry);
		virtual double GetGamma(double Spot, double Vol, double Expiry);
		virtual long IsTouched(double Spot) const;
		virtual double GetPayOff(double Spot) const;
	private:

	};

	class DigitalPutOption : public Option{

	public:
		DigitalPutOption(double Spot,
			double Strike,
			double r,
			double d,
			double Vol,
			double Expiry);
		virtual ~DigitalPutOption(){}
		virtual double GetValue(double Spot);
		virtual double GetValue(double Spot, double Vol, double Expiry);
		virtual double GetValue(double Spot, double r, double Vol, double Expiry);

		virtual double GetDelta(double Spot, double Vol, double Expiry);
		virtual double GetGamma(double Spot, double Vol, double Expiry);
		virtual long IsTouched(double Spot) const;
		virtual double GetPayOff(double Spot) const;
	private:

	};

	class CallSpreadOption : public Option{

	public:
		CallSpreadOption(double Spot,
			double Strike,
			double r,
			double d,
			double Vol,
			double Expiry,
			double epsilon);
		virtual ~CallSpreadOption(){}
		virtual double GetValue(double Spot);
		virtual double GetValue(double Spot, double Vol, double Expiry);
		virtual double GetValue(double Spot, double r, double Vol, double Expiry);

		virtual double GetDelta(double Spot, double Vol, double Expiry);
		virtual double GetGamma(double Spot, double Vol, double Expiry);
		virtual long IsTouched(double Spot) const;
		virtual double GetPayOff(double Spot) const;
	private:
		double epsilon;
	};

}

#endif
