#pragma once
#include <chrono>

namespace Timing
{
	using namespace std::chrono;
	using duration = std::chrono::duration<double>;
	using time_point = high_resolution_clock::time_point;
	using clock = high_resolution_clock;

	/* A clock class for getting the elapsed time */
	class Clock
	{
		time_point start;
	public:
		Clock() { start = clock::now(); }
		/* Returns the elapsed time since it was last called */
		inline duration operator()()
		{
			duration dur = (clock::now() - start);
			start = clock::now();
			return dur;
		}
	};

	/* A timer class */
	class Timer
	{
		time_point m_start, m_stop;
		bool isRunning = false;
	public:
		Timer() { m_start = m_stop = clock::now(); };
		inline duration operator()() const { return isRunning ? (clock::now() - m_start) : (m_stop - m_start); }
		inline void restart() { m_start = clock::now(); isRunning = true; };
		inline void start() { if (!isRunning) { m_start = clock::now(); isRunning = true; } };
		inline void stop() { if (isRunning) { m_stop = clock::now(); isRunning = false; } };
		inline bool running() const { return isRunning; };
	};
}