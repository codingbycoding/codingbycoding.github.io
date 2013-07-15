//g++ -g  -ID:\boost_1_47_0 -o  boost_asio.exe boost_asio.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_date_time-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a -lws2_32


#define _WIN32_WINNT 0x0501

#include "boost/asio.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

int main()
{

  boost::asio::io_service ioserv;


  boost::asio::deadline_timer dt(ioserv, boost::posix_time::seconds(1));
  std::cout << "expires_at: " << dt.expires_at() << std::endl;
  dt.wait();
  
  std::cout << "The End!" << std::endl;
  return 0;
}
