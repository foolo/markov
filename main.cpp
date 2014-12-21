#include <iostream>
#include "TextSource.h"


#define CHECK(A,B) \
	if ((A) != (B)) { \
		std::cerr << "@"<< __LINE__ << ":"; \
		std::cerr << "Expected: (" << #A << " == " << #B << ") Found: (" << (A) << " != " << (B) << ")" << std::endl; \
		exit(1); \
	}

void runtests()
{
	{
		std::vector<std::string> result = TextSource::Split("test  split a string.that. is amazing", ' ');
		CHECK(result.size(), 7);
		CHECK(result.at(0), "test");
		CHECK(result.at(1), "");
		CHECK(result.at(2), "split");
		CHECK(result.at(3), "a");
		CHECK(result.at(4), "string.that.");
		CHECK(result.at(5), "is");
		CHECK(result.at(6), "amazing");
	}
	{
		std::vector<std::string> result = TextSource::GetTokensInLine("test  split a string.that. is amazing");
		CHECK(result.size(), 9);
		CHECK(result.at(0), "test");
		CHECK(result.at(1), "split");
		CHECK(result.at(2), "a");
		CHECK(result.at(3), "string");
		CHECK(result.at(4), ".");
		CHECK(result.at(5), "that");
		CHECK(result.at(6), ".");
		CHECK(result.at(7), "is");
		CHECK(result.at(8), "amazing");
	}
	
	{
		std::string s = "what is this ";
		TextSource::replaceAll(s, "i", "siri");
		CHECK(s, "what siris thsiris ");
	}
}

int main(int argc, char* argv[])
{
	runtests();
	std::cout << "TESTS PASSED" << std::endl;
	return 0;
}
