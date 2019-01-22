#pragma once

#include <map>
#include <string>

class ParameterParser
{
public:
	ParameterParser(int argc, char* argv[]);
	std::string get_string(const std::string &param_name);
	std::string get_string(const std::string &param_name, const std::string &default_value);
	int get_int(const std::string &param_name, int default_value);

private:
	std::string get_param(const std::string &name);
	std::map<std::string, std::string> m_named_params;
	std::vector<std::string> m_free_params;

};
