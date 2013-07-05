//g++ -g  -ID:\boost_1_47_0 -o  boost_function.exe boost_function.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_filesystem-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a

#include <iostream>
// #include <algorithm>
#include <cmath>
#include <typeinfo>

#include "boost/utility/result_of.hpp"

#include "boost/ref.hpp"
#include "boost/typeof/typeof.hpp"

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




  int ia = 100;
  boost::reference_wrapper<int> iref(ia);
  std::cout << iref.get() << std::endl;

  std::string str("HelloWorld!");
  boost::reference_wrapper<std::string> strref(str);

  std::cout << strref.get() << std::endl;
  strref.get() = "GCC";
  std::cout << strref.get() << std::endl;
  
  *strref.get_pointer() = "GoodBye.";
  std::cout << strref.get() << std::endl;
  std::cout << strref.get().size() << std::endl;

  // BOOST_AUTO(sref, boost::ref(std::string("Hello")));
  BOOST_AUTO(sref, strref);  
  std::cout << typeid(sref).name() << std::endl;
  *sref.get_pointer() = "World.";
  std::cout << boost::unwrap_ref(sref) << std::endl;
}
