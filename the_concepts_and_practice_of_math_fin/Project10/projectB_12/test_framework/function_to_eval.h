

#ifndef FUNC_TO_EVAL_H
#define FUNC_TO_EVAL_H

typedef enum{ fwd, caplet, floorlet } product;

class FuncToEval{

public:

	FuncToEval(double f0_, double strike_, double vol_, double t1_, double t2_, product product_ = fwd);

	double operator()(double fwd_rte) const;

private:

	double f0;
	double strike;
	double vol;
	double t1;
	double t2;
	product _product;
};

#endif