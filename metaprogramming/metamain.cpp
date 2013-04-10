#include <iostream>

template <unsigned long N>
struct binary
{
	static unsigned const value = binary<N/10>::value * 2 + N%10;
	/* data */
};

template <>
struct binary<0>
{
	static unsigned const value = 0;
	/* data */
};
int main()
{

	std::cout << "metaprogramming::" << binary<130>::value << std::endl;
	return 0;
}