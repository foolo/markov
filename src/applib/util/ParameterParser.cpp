#include <deque>
#include <vector>
#include <iostream>
#include "ParameterParser.h"

ParameterParser::ParameterParser(int argc, char* argv[])
{
	std::deque<std::string> params;
	for (int i = 1; i < argc; i++) {
		params.push_back(argv[i]);
	}

	while (!params.empty()) {
		if (params.front().substr(0, 1) == "-") {
			if (params.size() >= 2) {
				m_named_params[params.front()] = params.at(1);
				params.pop_front();
				params.pop_front();
			}
			else {
				std::cout << "expected value after parameter" << params.front();
				exit(1);
			}
		}
		else {
			m_free_params.push_back(params.front());
			params.pop_front();
		}
	}
}

std::string ParameterParser::get_param(const std::string& name) {
	auto res = m_named_params.find(name);
	if (res == m_named_params.end()) {
		std::cout << "parameter " << name << " not found" << std::endl;
		exit(1);
	}
	return res->second;
}

std::string ParameterParser::get_string(const std::string& param_name)
{
	return get_param(param_name);
}

int ParameterParser::get_int(const std::string& param_name, int default_value)
{
	auto res = m_named_params.find(param_name);
	if (res == m_named_params.end()) {
		return default_value;
	}
	return std::stoi(res->second);
}
