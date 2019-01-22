#include <iostream>
#include "SerializeUtils.h"

unsigned SerializeUtils::read_unsigned(std::istream& s) {
	std::istream::pos_type pos = s.tellg();
	unsigned tmp;
	if (!(s >> tmp)) {
		std::cout << "read_unsigned failed at position " << pos << std::endl;
		exit(1);
	}
	return tmp;
}

unsigned long SerializeUtils::read_unsigned_long(std::istream& s) {
	std::istream::pos_type pos = s.tellg();
	unsigned long tmp;
	if (!(s >> tmp)) {
		std::cout << "read_unsigned_long failed at position " << pos << std::endl;
		exit(1);
	}
	return tmp;
}

std::string SerializeUtils::read_string(std::istream& s) {
	std::istream::pos_type pos = s.tellg();
	std::string tmp;
	if (!(s >> tmp)) {
		std::cout << "read_string failed at position " << pos << std::endl;
		exit(1);
	}
	return tmp;
}

void SerializeUtils::assert(std::istream& s, const std::string &expected) {
	std::string str = read_string(s);
	if (str != expected) {
		std::cout << "unexpected value " << str << " != " << expected << " at position " << s.tellg() << std::endl;
		exit(1);
	}
}
