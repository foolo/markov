#pragma once

#include <istream>

class SerializeUtils
{
public:
	static unsigned read_unsigned(std::istream &s);
	static unsigned long read_unsigned_long(std::istream &s);
	static std::string read_string(std::istream &s);
	static void assert(std::istream& s, const std::string &expected);

};
