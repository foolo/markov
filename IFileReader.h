#ifndef IFILEREADER_H
#define	IFILEREADER_H

#include <string>

class IFileReader
{
public:

	virtual ~IFileReader()
	{
	};
	virtual bool open(const std::string& filename) = 0;
	virtual bool is_open() = 0;
	virtual bool read_line(std::string& lineOut) = 0;
};

#endif	/* IFILEREADER_H */
