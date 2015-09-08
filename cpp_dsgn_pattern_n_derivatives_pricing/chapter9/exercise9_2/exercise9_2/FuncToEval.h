


#ifndef FUNC_TO_EVAL_H
#define FUNC_TO_EVAL_H

class FuncToEval{
	
public:
	FuncToEval();
	virtual ~FuncToEval(){}
	virtual double operator()(double x) const = 0;

protected:
	double x;
};		


class Func1: public FuncToEval{

public:
	Func1(){};
	virtual ~Func1(){};
	virtual double operator()(double x) const;
private:

};

class Func2 : public FuncToEval{

public:
	Func2(){};
	virtual ~Func2(){};
	virtual double operator()(double x) const;
private:

};

class Func3 : public FuncToEval{

public:
	Func3(){};
	virtual ~Func3(){};
	virtual double operator()(double x) const;
private:

};

class Func4 : public FuncToEval{

public:
	Func4(){};
	virtual ~Func4(){};
	virtual double operator()(double x) const;
private:

};

#endif