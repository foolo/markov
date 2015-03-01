#ifndef FILEREADER_H
#define	FILEREADER_H

#include <fstream>
#include "ITextSource.h"

class FileReader : public ITextSource
{
private:
	std::ifstream m_ifstream;

public:
	FileReader();
	FileReader(const std::string& filename);
	virtual ~FileReader();
	virtual bool open(const std::string& filename);
	virtual bool is_open();
	virtual bool read_line(std::string& lineOut);
};

#endif	/* FILEREADER_H */
