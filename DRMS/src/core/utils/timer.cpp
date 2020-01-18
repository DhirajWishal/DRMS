#include "drmsafx.h"
#include "timer.h"

namespace DRMS {
	Timer::Timer() {
		startTimePoint = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer() {
		if (!isEnded)
			printf("Timer: %f ms", end());
	}

	double Timer::end() {
		isEnded = true;
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>
			(startTimePoint).time_since_epoch().count();
		auto stop = std::chrono::time_point_cast<std::chrono::microseconds>
			(endTimePoint).time_since_epoch().count();

		auto duration = stop - start;
		return duration * .001;
	}
}