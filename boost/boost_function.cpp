//g++ -g  -ID:\boost_1_47_0 -o  boost_function.exe boost_function.cpp

#include <iostream>
// #include <algorithm>
#include <cmath>
#include <typeinfo>

#include <algorithm>
#include <sstream>

#include "boost/utility/result_of.hpp"

#include "boost/ref.hpp"
#include "boost/typeof/typeof.hpp"

#include "boost/bind.hpp"

#include "boost/assign.hpp" 

#include "boost/utility.hpp"
#include "boost/typeof/typeof.hpp"

#include "boost/function.hpp"

#include "boost/signals2.hpp"

#include "boost/make_shared.hpp"
#include "boost/shared_ptr.hpp"

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


class TestClass
{
private:
  int _a;
public:
  TestClass():_a(0){}
  void print()
  {
    std::cout << "_a: " << ++_a << std::endl;
  }

  void print(std::string str )
  {
    std::cout << "str: " << str << std::endl;
  }

  void print(int a )
  {
    std::cout << "a: " << a << std::endl;
  }

  void print(std::string str1, std::string str2 )
  {
    std::cout << "str1: " << str1 << "   str2: " << str2 << std::endl;
  }
};


template<class T1, class T2, class T3>
class DemoClass
{
private:
  T1 _a;
  T2 _b;
  T3 _c;
  
public:
  DemoClass(int a=0, int b=0, int c=0):_a(a), _b(b), _c(c){}
  DemoClass(T1 a, T2 b, T3 c):_a(a), _b(b), _c(c){}  
  void print()
  {
    std::cout << "_a: " << _a << "   _b: " << _b << "   _c: "  << _c << std::endl;
  }

  void print(T1 t1, T2 t2, T3 t3)
  {
    std::cout << "t1: " << t1 << "   t2: " << t2 << "   t3: "  << t3 << std::endl;
  }
  
  template<class TT1> 
  void print(TT1 t1)
  {
    std::cout << "t1: " << t1 << std::endl;
  }
  
  template<class TT1, class TT2>
  void print(T1 t1, T2 t2)
  {
    std::cout << "t1: " << _a << "   _b: " << _b << "   _c: "  << _c << std::endl;
  }

  template<class TT1, class TT2, class TT3>  
  void print(TT1 t1, TT2 t2, TT3 t3)
  {
    std::cout << "t1: " << t1 << "   t2: " << t2 << "   t3: "  << t3 << std::endl;
  }

  
};

// template<>
// class DemoClass
// {
// private:
//   int  _a;
//   int  _b;
//   int  _c;
  
// public:
//   DemoClass(int a=0, int b=0, int c=0):_a(a), _b(b), _c(c){}
//   void print()
//   {
//     std::cout << "_a: " << _a << "   _b: " << _b << "   _c: "  << _c << std::endl;
//   }

// };

// template <int N>
// void echo(int x)
// {
//   std::cout << "echo  : " << t << std::endl;
// }

template <class T>
void echo(T t)
{
  std::cout << "echo t : " << t << std::endl;
}

template <class T1, class T2>
void echo(T1 t1, T2 t2)
{
  std::cout << "echo  t1 : " << t1 << "   t2: " << t2 << std::endl;
}



void slot_func()
{
  std::cout << "slot_func called..." << std::endl;
}

template <class T>
void Tslot(T t)
{
  std::cout << "TSlot called  t : " << t << std::endl;
}


template <int N>
struct Cslot
{

  typedef int result_type;
  
  result_type operator()(int x)
  {
    std::cout << "TSlot<" << N << "> called  x : " << x << std::endl;
    return x*N;
  }


};

template<int NN>
bool operator==(const struct Cslot<NN>& , const struct Cslot<NN>&)
{
  return true;
}

template <class T>
void print(T t)
{
  boost::unwrap_ref(t).print();
}



template <class T1, class T2>
void print(T1 t1, T2 t2)
{
  std::cout << "arg1: " << t1 << "  arg2: " << t2 << std::endl;
}


struct printer
{
  typedef std::string result_type; //without this then boost::bind<typename> 
  // void operator()(std::string str)
  result_type operator()(int str)  
  {
    // print<std::string, int>(std::string("abc"), 123);
    // print(str, 123);
    std::stringstream ss;
    ss <<  "arg: " << str << std::endl;
    return ss.str(); 
  }

};


class FuncClass
{
public:
  FuncClass(int a=0):m_a(a)
  {
  }
  
  // void SetFunc(boost::function<void(int)> fun)
  // {
  //   m_func = fun;
  // }
  template<typename CallBack>
  void SetFunc(CallBack fun)
  {
    m_func = fun;
  }  
  
  void Run()
  {
    if(m_func.empty())
      {
	std::cout << "m_func empty." << std::endl;
      }
    else
      {
	m_func(m_a);
      }
  }
  
private:
  boost::function<void(int)> m_func;
  int m_a;
};



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
  std::cout << "************" << std::endl;  
  print(b);
  std::cout << "************" << std::endl;
  print(br);  


  boost::bind(print<std::string, int>, _1, _2)("abc", 123);
  boost::bind(print<std::string, std::string>, _1, "jack")("abc", 123);

  DemoClass<std::string, std::string, std::string> demo("a", "b", "c");
  // DemoClass demoS;
  // boost::bind(&DemoClass<std::string, std::string, std::string>::print, &demo, "jack", _1, _2)("abc", "123");
  TestClass test;
  boost::bind(&TestClass::print, test)();  
  boost::bind(&TestClass::print, test, "Hello", _1)("World");
  boost::bind(&TestClass::print, &test, "Hello", _1)("World");
  // boost::bind(DemoClass<std::string, std::string, std::string>::print<std::string, std::string, int>, &demo, "jack", _1, _2)("abc", 123);  


  using namespace  boost::assign;
  std::list<int> l = list_of(1)(2)(3)(4)(5);
  for(std::list<int>::iterator it = l.begin(); it!=l.end(); ++it) 
  // BOOST_FOREACH(BOOST_AUTO(it, l.begin()), l)
    {
      std::cout << *it << std::endl; 
    }
  
  // std::for_each( l.begin(), l.end(),  boost::bind(&TestClass::print, test, _1) );
  // std::for_each( l.begin(), l.end(),  printer );
  std::cout << "for_each begin..." << std::endl;
  std::for_each( l.begin(), l.end(),  printer() );
  // std::cout << boost::bind<std::string>(printer(), _1)(998) << std::endl; //without result_type in functor
  std::cout << boost::bind(printer(), _1)(998) << std::endl;  //with result_type in functor

  BOOST_AUTO(x_f, boost::bind(std::greater<int>(), _1, _2) );
  std::cout << x_f(20,30) << std::endl;
	     
  boost::function<int(int,int)> func2;
  func2 = std::max<int>;
  if(func2)
    {
      std::cout << "func2(10,20): " << func2(10,20) << std::endl;
      std::cout << std::endl;
    }
  else
    {
      std::cout << std::endl;
    }
  
  func2 = 0;
  
  if(func2.empty())
    {
      std::cout << "func2 empty" << std::endl;
    }
  else
    {
      std::cout << "func2 not empty." << std::endl;
    }


  boost::function<void(TestClass&, std::string, std::string)> func2_mem1;
  TestClass tf1;
  func2_mem1 = boost::bind(&TestClass::print, _1, _2, _3);
  func2_mem1(tf1, "Come","On");

  std::cout << "seperator******************" << std::endl;
  
  boost::function<void(std::string, std::string)> func2_mem2;
  TestClass tf2;  
  func2_mem2 = boost::bind(&TestClass::print, &tf2,  _1, _2);    
  func2_mem2("Come","On");



  boost::function<void(int)> echoI = echo<int>;
  FuncClass fun;
  fun.SetFunc(echoI);
  fun.Run();


  fun.SetFunc(boost::bind<void>(echo<int,int>, _1, 20));
  fun.Run();


  boost::signals2::signal<void()> s;
  s.connect(&slot_func);
  s();


  boost::signals2::signal<int(int)> s_Cslot_2;
  boost::signals2::connection c11 = s_Cslot_2.connect(1, Cslot<1>());
  boost::signals2::connection c111 = s_Cslot_2.connect(1, Cslot<11>());
  boost::signals2::connection c22 = s_Cslot_2.connect(2, Cslot<2>());
  s_Cslot_2.connect(2, Cslot<22>());
  s_Cslot_2.connect(3, Cslot<3>());
  boost::signals2::connection c333 = s_Cslot_2.connect(3, Cslot<33>());
  s_Cslot_2.connect(Cslot<33333>());      

  // std::cout << "********************************" << std::endl;
  // s_Cslot_2(10);
  // std::cout << "********************************" << std::endl;
  
  
  std::cout << "result of signal call : " << *s_Cslot_2(8) << std::endl;

  s_Cslot_2.disconnect(1);
  s_Cslot_2.disconnect(Cslot<33333>());

  // boost::signals2::shared_connection_block bloc(c333);
  //bloc.unblock();
  c333.disconnect();
  std::cout << "after disconnect..." << std::endl;
  std::cout << "********************************" << std::endl;
  s_Cslot_2(10);
  std::cout << "********************************" << std::endl;
  

  std::cout << "################################" << std::endl;
  boost::signals2::signal<int(int)> sp_i_i_s;
  boost::shared_ptr<Cslot<88> > sp8(boost::make_shared<Cslot<88> >());
  sp_i_i_s.connect(boost::signals2::signal<int(int)>::slot_type(boost::ref(*sp8)).track(sp8));

  sp_i_i_s(88);
  std::cout << "after reset" << std::endl;
  std::cout << "################################" << std::endl;  
  sp8.reset();
  sp_i_i_s(88);



  std::cout << "################################" << std::endl;
  boost::signals2::signal<int(int)> sp_i_i_sss;
  boost::shared_ptr<Cslot<88> > sp888(boost::make_shared<Cslot<88> >());
  sp_i_i_sss.connect(*sp888);

  sp_i_i_sss(999);
  std::cout << "after reset" << std::endl;
  std::cout << "################################" << std::endl;  
  sp888.reset();//uncertain will happen
  sp_i_i_sss(999);

}
