//Trapezium.h


template<class T>
double  Trapezium_rule(double Low, double High,unsigned long Steps, T& TheFunction)
{

		double h=(High-Low)/Steps;
		double i_trap=TheFunction(Low)/2.0 + TheFunction(High)/2.0;
    
		for(unsigned long i = 0;i <= Steps;++i){
			i_trap+=TheFunction(Low+i*h);
		}

		return i_trap*=h;

}
