//g++ -g  -ID:\boost_1_47_0 -o  boost_function.exe boost_function.cpp

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


// template<class T1 , class T2 >
// // typename boost::result_of<T1(T2)>::value call_func(T1 t1, T2 t2)
// result_type call_func_re(T1 t1, T2 t2)
// {
//   typedef T2 result_type;
//   return t1(t2);
// }

class BigClass
{
private:
  int _a;
public:
  BigClass():_a(0){}
  void print()
  {
    for(int i=0; i<2; ++i)
      {
	std::cout << "_a: " << ++_a << std::endl;
      }
  }
};

template <class T>
void print(T t)
{
  boost::unwrap_ref(t).print();
}

int main()
{
  Func func = sqrt;
  boost::result_of<Func(double)>::type x = func(0.0016);
  std::cout << x << std::endl;
  std::cout << typeid(x).name() << std::endl;


  BOOST_AUTO( x_auto, func(0.0016));
  std::cout << x_auto << std::endl;

  // BOOST_AUTO( x_call, call_func_re(func, 0.0016));
  // std::cout << x_call << std::endl;


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
  std::cout << "unwrap_ref: " << boost::unwrap_ref(strref).size() << std::endl;

  // BOOST_AUTO(sref, boost::ref(std::string("Hello")));
  BOOST_AUTO(sref, strref);  
  std::cout << typeid(sref).name() << std::endl;
  *sref.get_pointer() = "World.";
  std::cout << boost::unwrap_ref(sref) << std::endl;

  
  
  BigClass b;
  b.print();
  std::cout << "************" << std::endl;
  // BOOST_AUTO(brc, boost::cref(b));
  // print(brc);
  // brc.get().print();
  std::cout << "************" << std::endl;
  BOOST_AUTO(br, boost::ref(b));
  br.get().print();
  std::cout << "************" << std::endl;
  print(br);
}
