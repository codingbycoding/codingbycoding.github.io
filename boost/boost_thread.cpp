//bjam  --toolset=gcc --with-thread --stagedir="D:\boost_1_47_0\mingw\stage\complete" --build-dir="D:\boost_1_47_0\mingw\b2\complete" --build-type=complete

//bjam  --toolset=gcc --with-system --stagedir="D:\boost_1_47_0\mingw\stage" --build-dir="D:\boost_1_47_0\mingw\b2" link=static runtime-link=shared threading=multi debug release stage


//g++ -g  -ID:\boost_1_47_0 -o  boost_thread.exe boost_thread.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_date_time-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_thread-mgw44-mt-1_47.a



#define BOOST_THREAD_USE_LIB // solve undefined reference to `_imp___ZN5boost6threadD1Ev'

#include "boost/thread.hpp"

#include "boost/date_time/posix_time/posix_time.hpp"

#include <iostream>


void ThreadFunc0()
{
  std::cout << "ThreadFucn..." << std::endl;
  boost::this_thread::sleep(boost::posix_time::seconds(1));
}

struct TID_Print_True
{
  friend std::ostream& operator <<(std::ostream& os, struct TID_Print_True) 
  {
    os << "TID_Print_True";
    return os; 
  }
};

template<typename T1>
void ThreadFunc1(T1 t1)
{
  
  std::cout << "ThreadFucn1... t1: "  << t1 << std::endl;
  // boost::this_thread::sleep(
}


template<typename T1, typename T2>
void ThreadFunc2(T1 t1, T2 t2)
{
  if(typeid(t2) == typeid(TID_Print_True))
    {
      std::cout << "get_id(): " << boost::this_thread::get_id() << std::endl;
    }
  
  std::cout << "ThreadFucn2... t1: "  << t1 << "   t2:" << t2 << std::endl;
  // boost::this_thread::sleep(
}


template<typename T1> 
void ThreadFunc1End(T1 t1)
{
  std::cout << "ThreadFunc1End...  t1: " << t1 << std::endl;
}


template<typename T1, typename T2, typename T3, typename T4>
void ThreadFunc4(T1 t1, T2 t2, T3 t3, T4 t4)
{
  if(typeid(t2) == typeid(TID_Print_True))
    {
      std::cout << "get_id(): " << boost::this_thread::get_id() << std::endl;
    }
  
  std::cout << "ThreadFucn4... t1: "  << t1 << "   t2:" << t2 << std::endl;
  
  boost::this_thread::at_thread_exit(boost::bind(ThreadFunc1End<std::string>, "!!!"));
}




int main()
{
  boost::thread t(ThreadFunc0);
  // boost::thread tm = boost::make_thread(ThreadFunc);

  boost::mutex mu;

  try
    {
      mu.lock();
      //dosometing
      mu.unlock();
    }
  catch(...)
    {
      mu.unlock();
    }


  {
    boost::mutex::scoped_lock scopedLo(mu);
  }
  
  t.join();

  boost::thread t1(ThreadFunc1<std::string>, "HelloWorld");
  t1.join();


  boost::thread tb(boost::bind(ThreadFunc1<std::string>, "bind"));
  tb.join();

  boost::thread_group tg;
  tg.create_thread(boost::bind(ThreadFunc1<std::string>, "thread_group"));
  tg.create_thread(boost::bind(ThreadFunc1<std::string>, "thread_group"));
  tg.create_thread(boost::bind(ThreadFunc1<std::string>, "thread_group"));
  tg.create_thread(boost::bind(ThreadFunc2<std::string, struct TID_Print_True>, "test", TID_Print_True()));

  tg.create_thread(boost::bind(ThreadFunc4<std::string, int, int, int>, "thread_group", 0, 0, 0 ));
  tg.join_all();

  

  std::cout << "get_id: " << boost::this_thread::get_id() << std::endl;
  std::cout << "concurrentcy num: " << boost::thread::hardware_concurrency() << std::endl;
    
  return 0;
}
