#pragma once

#ifndef _DRMS_TIMER_H
#define _DRMS_TIMER_H

#include <chrono>

namespace DRMS {
	class Timer {
	public:
		Timer();
		~Timer();

		double end();

	private:
		bool isEnded = false;

		std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;

		std::chrono::time_point<std::chrono::high_resolution_clock> time;
		std::chrono::time_point<std::chrono::high_resolution_clock> oldTime;
	};
}

#endif // !_DRMS_TIMER_H

