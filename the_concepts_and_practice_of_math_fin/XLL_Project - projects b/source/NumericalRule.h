//Midpoint rule
template<class T>
class Midpoint_rule
{
public:
	Midpoint_rule(double Low_, double High_, T& TheFunction_)
		: Low(Low_),High(High_),TheFunction(TheFunction_)	
	{};

	double operator()(unsigned long Steps) const{	
		double h=(double)((High-Low)/Steps);
		double i_mid=0.0;
    
		for(unsigned long i = 1;i <=Steps;++i){
			i_mid+=TheFunction(Low+(double)((i-.5)*h));
		}
	
		return i_mid*=h;
	};

private:
	T TheFunction;
	double Low;
	double High;
	unsigned long Steps;   
};

//Trapezoidal rule
template<class T>
class Trapezium_rule
{
public:
	Trapezium_rule(double Low_, double High_, T& TheFunction_)
		:Low(Low_),High(High_),TheFunction(TheFunction_)	
	{};
	
	double operator()(unsigned long Steps) const{	
		double h=(double)((High-Low)/Steps);
		double i_trap=TheFunction(Low)/2.0 + TheFunction(High)/2.0;
    
		for(unsigned long i = 1;i <=Steps;++i){
			i_trap+=TheFunction(Low+(double)(i*h));
		};
	
		return i_trap*=h;
	};
	
private:
	T TheFunction;
	double Low;
	double High;
	unsigned long Steps;    
};



//Simpson's rule
template<class T>
class Simpson_rule
{
public:
	Simpson_rule(double Low_, double High_, T& TheFunction_)
		: Low(Low_),High(High_),TheFunction(TheFunction_)	
	{};

	double operator()(unsigned long Steps) const{	
		double h=(double)((High-Low)/Steps);
		double i_simpson=TheFunction(Low)/6.0 + TheFunction(High)/6.0;
    
		for(unsigned long i = 0;i <=Steps-1;++i){
			i_simpson+=TheFunction(Low+(double)(i*h))/3.0;
		}
	
		for(unsigned long i = 1;i <=Steps-1;++i){
			i_simpson+=2.0*TheFunction(Low+(double)((i-.5)*h))/3.0;
		}
	
		return i_simpson*=h;
	};

private:
	T TheFunction;
	double Low;
	double High;
	unsigned long Steps;   
};

