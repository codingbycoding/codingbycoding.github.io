//g++ -g  -ID:\boost_1_47_0 -o  boost_function.exe boost_function.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_filesystem-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a

#include <iostream>
// #include <algorithm>
#include <cmath>
#include <typeinfo>

#include "boost/utility/result_of.hpp"

typedef double (*Func)(double);


template<class T1 , class T2 >
typename boost::result_of<T1(T2)>::value call_func(T1 t1, T2 t2)
{
  return t1(t2);
} 

int main()
{
  Func func = sqrt;
  boost::result_of<Func(double)>::type x = func(0.0016);
  std::cout << x << std::endl;
  std::cout << typeid(x).name() << std::endl;
}
