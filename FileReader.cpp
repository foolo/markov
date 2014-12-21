#include "FileReader.h"

FileReader::FileReader()
{
}

FileReader::FileReader(const std::string& filename) :
m_ifstream(filename.c_str())
{
}

bool FileReader::open(const std::string& filename)
{
	m_ifstream.close();
	m_ifstream.open(filename.c_str());
	return m_ifstream.is_open();
}

bool FileReader::is_open()
{
	return m_ifstream.is_open();
}

bool FileReader::read_line(std::string& lineOut)
{
	return getline(m_ifstream, lineOut);
}

FileReader::~FileReader()
{
}

