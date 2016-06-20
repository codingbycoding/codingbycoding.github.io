//g++  -ftemplate-depth-NN metamain.cpp  -o metamain.exe

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


template <unsigned long long N>
struct sumToOne
{
  static unsigned const value = sumToOne<N-1>::value + N;
	/* data */
};

template <>
struct sumToOne<1>
{
  static unsigned const value = 1;
	/* data */
};


template<class T>
class typetraits
{
  typedef typename T::value_type value_type;
};


template<>
class typetraits<int>
{
  typedef int value_type;
};

int main()
{

  std::cout << "metaprogramming::" << binary<130>::value << std::endl;
  // std::cout << "metaprogramming::" << sumToOne<65535>::value << std::endl;
  std::cout << "metaprogramming::" << sumToOne<100>::value << std::endl;
  return 0;
}
