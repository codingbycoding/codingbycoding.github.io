#include <functional>
#include <iostream>

void test_stl_algo() {
	std::plus<int> s_plus;
	std::cout << "std::plus : " << s_plus(100, 200) << std::endl;
}
