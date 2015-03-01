#ifndef IFILEREADER_H
#define	IFILEREADER_H

#include <string>

class ITextSource
{
public:

	virtual ~ITextSource()
	{
	};
	virtual bool open(const std::string& filename) = 0;
	virtual bool is_open() = 0;
	virtual bool read_line(std::string& lineOut) = 0;
};

#endif	/* IFILEREADER_H */
