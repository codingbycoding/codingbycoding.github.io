#include <iostream>

#include "boost/lexical_cast.hpp"

int main()
{
	std::cout << "include iostream" << std::endl;
	std::cout << "Hello https://code.google.com" << std::endl;

	using boost::lexical_cast;
	using boost::bad_lexical_cast;

	int a;
	try
	{
		a = lexical_cast<int, std::string>("20j");
	}
	catch(bad_lexical_cast& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "a:" << a << std::endl;

	return 0;
}
