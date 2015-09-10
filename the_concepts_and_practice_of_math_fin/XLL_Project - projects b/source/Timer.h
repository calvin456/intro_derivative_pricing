


#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class timer {
	private:
		//unsigned long begTime;
		double begTime;
	public:
		void start() {
			begTime = clock();
		}

		double elapsedTime() {
			return (clock() - begTime) / CLOCKS_PER_SEC;
		}

		bool isTimeout(unsigned long seconds) {
			return seconds >= elapsedTime();
		}
};

#endif