#include "Timer.h"

Timer::Timer()
{
	Reset();
}

void Timer::Reset()
{
	m_oldClock = clock();
	m_startTime = clock();
}

bool Timer::CheckAlarm(long intervalMs)
{
	clock_t clockdiff = clock() - m_oldClock;
	long diffMs = 1000 * clockdiff / CLOCKS_PER_SEC;
	if (diffMs > intervalMs)
	{
		m_oldClock = clock();
		return true;
	}
	return false;
}

void Timer::ReportProgressIfNeeded(long intervalMs, IProgressReporter &progressReporter)
{
	if (CheckAlarm(intervalMs))
	{
		progressReporter.ReportProgress();
	}
}

Timer::~Timer()
{
}

