/*exercise 5.4 & 5.5*/


#ifndef TERMINATOR_H
#define TERMINATOR_H



class Terminator
{
public:
	Terminator(); //default constructor
	Terminator(const unsigned long TimeSpent_,const unsigned long PathsDone_);
	unsigned long getTimeSpent();
	unsigned long getPathsDone();
	
	
private:
	unsigned long TimeSpent; //time in minute
	unsigned long PathsDone; 
};

#endif