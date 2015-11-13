


#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class timer {

public:
		timer():begTime(0){}
		~timer(){}
	
		void start() {
			begTime = clock();
		}

		double elapsedTime() {
			return (clock() - begTime) / CLOCKS_PER_SEC;
		}

		bool isTimeout(unsigned long seconds) {
			return seconds >= elapsedTime();
		}
private:
		//unsigned long begTime;
		double begTime;


};

#endif
