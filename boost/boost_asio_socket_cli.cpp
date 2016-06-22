//g++ -g  -ID:\boost_1_47_0 -o  boost_asio_socket_cli.exe boost_asio_socket_cli.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_date_time-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a -lws2_32



#define _WIN32_WINNT 0x0501 //workaround for boost  
#include "boost/asio.hpp"


int main()
{

  try
    {
      std::cout << "client start..." << std::endl;

      boost::asio::io_service ioserv;
  
      boost::asio::ip::address dstaddr = boost::asio::ip::address::from_string("127.0.0.1");
      boost::asio::ip::tcp::endpoint dstendp(dstaddr, 8888);
  

      boost::asio::ip::tcp::socket sock(ioserv);

      sock.connect(dstendp);
      std::cout << "local_endpoint: " << sock.local_endpoint() << std::endl;
      
      std::vector<char> str(100,0);
      sock.read_some(boost::asio::buffer(str));
      std::cout << "receive from: " << sock.remote_endpoint() << "  " << &str[0] << std::endl;


    }
  catch(std::exception& e)
    {
      std::cout << "exception: " << e.what() << std::endl;
    }

  
  std::cout << "" << std::endl;
  return 0;
}
