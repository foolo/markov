#include <iostream>
#include "UnitTests.h"

int main()
{
	try
	{
		UnitTests::Run();
	}
	catch (const char *err)
	{
		std::string errStr(err);
		std::cout << "CAUGTH: " << errStr << std::endl;
		return 1;
	}
	std::cout << "TESTS PASSED" << std::endl;
	return 0;
}
