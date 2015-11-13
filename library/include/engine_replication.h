//engine_replication.h

//engine to compute barrier price through replication

#ifndef ENGINE_REP_H
#define ENGINE_REP_H

#include<memory>
#include<options.h>

using namespace std;

template<typename T, typename U>
class EngineRepli{

public:
	EngineRepli(shared_ptr<T>& Option_, shared_ptr<U>& FinalPayOff_)
		:Option(Option_), FinalPayOff(FinalPayOff_)
	{}

	~EngineRepli(){}

	double DoReplication(unsigned long steps, double Spot, double t){
		Option->GeneratePtf(steps, FinalPayOff);
		return Option->GetValue(Spot, t, FinalPayOff);
	}

	double DoReplication(unsigned long steps, vector<double> _Vol, double Spot, double t)  //time-dep vol
	{
		Option->GeneratePtf(steps, _Vol, FinalPayOff);
		return Option->GetValue(Spot, _Vol, t, FinalPayOff);

	}

	double DoReplication1(unsigned long steps, double Spot, double t) //unequal time step
	{
		Option->GeneratePtf1(steps, FinalPayOff);
		return Option->GetValue(Spot, t, FinalPayOff);

	}

private:
	shared_ptr<T> Option;
	shared_ptr<U> FinalPayOff;

};

#endif
