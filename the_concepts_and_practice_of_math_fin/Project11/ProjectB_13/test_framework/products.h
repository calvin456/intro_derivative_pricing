//products.h

#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <vector>

using namespace std;

namespace Product{ //To avoid naming conflict with QuantLib

	struct CashFlow{
		double time;
		double amount;
	};


	//abstract base class
	class BGMProducts{
	public:
		BGMProducts(const std::vector<double>& times_, double Strike_);
		virtual ~BGMProducts(){}

		void setStrike(double Strike_);

		virtual std::vector<double> GetUnderlyingTimes() const = 0;
		virtual std::vector<double> GetEvolutionTimes() const = 0;
		virtual void reset() = 0;

		virtual bool DoNextStep(const std::vector<double>& fwd_rtes, std::vector<CashFlow>& cf) = 0;

	protected:
		std::vector<double> times;
		double Strike;
		unsigned long M;
	};

	class Swaption :public BGMProducts{
		//European swaption
	public:
		Swaption(const std::vector<double>& times_, double Strike_);
		virtual ~Swaption(){}

		virtual std::vector<double> GetUnderlyingTimes() const;
		virtual std::vector<double> GetEvolutionTimes() const;
		virtual void reset(){}

		virtual bool DoNextStep(const std::vector<double>& fwd_rtes, std::vector<CashFlow>& cf);
	private:

	};

	class TriggerSwap :public BGMProducts{
		//A swap-based trigger swap which at each stage knocks-out 
		//if the swap-rate for the remaining times is above a ref rate,
		//and otherwise is a swap at strike

		//up-and-out. In the book, p.325 up-and-in instead
	public:
		TriggerSwap(const std::vector<double>& times_, double Strike_, double ref_rate_);
		virtual ~TriggerSwap(){}

		void set_i(unsigned long a);

		virtual std::vector<double> GetUnderlyingTimes() const;
		virtual std::vector<double> GetEvolutionTimes() const;
		virtual void reset();

		virtual bool DoNextStep(const std::vector<double>& fwd_rtes, std::vector<CashFlow>& cf);
	private:
		double ref_rate;
		unsigned long _i_;
	};

	class Caplet : public BGMProducts{
		//call option on fwd libor rate - 1st rate
	public:
		Caplet(const std::vector<double>& times_, double Strike_);
		virtual ~Caplet(){}

		std::vector<double> GetUnderlyingTimes() const;
		std::vector<double> GetEvolutionTimes() const;
		virtual void reset(){}

		virtual bool DoNextStep(const std::vector<double>& fwd_rtes, std::vector<CashFlow>& cf);
	private:

	};

};

#endif