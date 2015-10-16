#ifndef IPROGRESSREPORTER_H
#define	IPROGRESSREPORTER_H

#include <string>

class IProgressReporter
{
public:
	virtual ~IProgressReporter() {};
	virtual void ReportProgress() = 0;
};

#endif	/* IPROGRESSREPORTER_H */
