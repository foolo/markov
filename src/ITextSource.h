#pragma once

#include <string>

class ITextSource
{
public:

	virtual ~ITextSource()
	{
	};
	virtual bool open(const std::string& filename) = 0;
	virtual bool is_open() = 0;
	virtual bool read_word(std::string& wordOut) = 0;
	virtual std::streampos get_size() = 0;
	virtual std::streampos get_position() = 0;
};
