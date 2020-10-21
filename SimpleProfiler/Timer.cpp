#include "Timer.h"
#include "Profiler.h"

namespace Benchmark
{

Timer::Timer(const char *name) :
	m_name(name),
	m_startTimePoint(std::chrono::high_resolution_clock::now()),
	m_stopped(false)
{
}

Timer::~Timer()
{
	if(!m_stopped)
		stop();
}

void Timer::stop()
{
	auto endTimePoint = std::chrono::high_resolution_clock::now();

	long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

	Profiler::getInstance().writeProfile({ m_name, start, end, std::this_thread::get_id() });

	m_stopped = true;
}

}