#include <iostream>

#include "boost/lexical_cast.hpp"

int main()
{
	std::cout << "include iostream" << std::endl;
	std::cout << "Hello https://code.google.com" << std::endl;

	using boost::lexical_cast;
	using boost::bad_lexical_cast;

	return 0;
}
