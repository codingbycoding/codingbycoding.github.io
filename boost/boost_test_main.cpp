//bjam  --toolset=gcc --with-test --stagedir="D:\boost_1_47_0\mingw\stage" --build-dir="D:\boost_1_47_0\mingw\b2" link=static runtime-link=shared threading=multi debug release stage 

//

//g++ -ID:\boost_1_47_0 -o  boost_test_main.exe boost_test_main.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_test_exec_monitor-mgw44-mt-1_47.a;


#include "boost/test/minimal.hpp"


int test_main(int argc, char* argv[])
{

  BOOST_CHECK(sizeof(int) == 4);
  // BOOST_REQUIRE(sizeof(int) == 3);
  BOOST_ERROR("test boost error");
  BOOST_FAIL("test boost error");
  return 0; 
}
