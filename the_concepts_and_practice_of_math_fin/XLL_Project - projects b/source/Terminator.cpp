#include <Terminator.h>

//default constructor
//max time spent 10 min
//max paths done 100 mm
Terminator::Terminator():TimeSpent(600),PathsDone(100000000)
{};

Terminator::Terminator(const unsigned long TimeSpent_,const unsigned long PathsDone_)
:TimeSpent( TimeSpent_),PathsDone(PathsDone_)
{};

unsigned long Terminator::getTimeSpent(){
	return TimeSpent;
};

unsigned long Terminator::getPathsDone(){
	return PathsDone;
};