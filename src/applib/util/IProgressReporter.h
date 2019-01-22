#pragma once

class IProgressReporter
{
public:
	virtual ~IProgressReporter() {};
	virtual void ReportProgress() = 0;
};
