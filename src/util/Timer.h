#pragma once

#include <ctime>
#include "util/IProgressReporter.h"

class Timer
{
private:
	clock_t m_oldClock;
	clock_t m_startTime;

public:
	Timer();
	virtual ~Timer();
	
	void Reset();
	bool CheckAlarm(long intervalMs);
	void ReportProgressIfNeeded(long intervalMs, IProgressReporter &progressReporter);
};
