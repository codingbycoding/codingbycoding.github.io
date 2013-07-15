//bjam  --toolset=gcc --with-thread --stagedir="D:\boost_1_47_0\mingw\stage\complete" --build-dir="D:\boost_1_47_0\mingw\b2\complete" --build-type=complete

//bjam  --toolset=gcc --with-system --stagedir="D:\boost_1_47_0\mingw\stage" --build-dir="D:\boost_1_47_0\mingw\b2" link=static runtime-link=shared threading=multi debug release stage


//g++ -g  -ID:\boost_1_47_0 -o  boost_thread.exe boost_thread.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_date_time-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_thread-mgw44-mt-1_47.a

#include "boost/thread.hpp"
// #include
#include <iostream>

void ThreadFunc()
{
  std::cout << "ThreadFucn..." << std::endl;
}

int main()
{
  boost::thread t(ThreadFunc);
  return 0;
}
