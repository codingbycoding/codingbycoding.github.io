//g++ -g  -ID:\boost_1_47_0 -o  boost_asio_socket_serv.exe boost_asio_socket_serv.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_date_time-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a -lws2_32



#define _WIN32_WINNT 0x0501 //workaround for boost  
#include "boost/asio.hpp"


int main()
{

  try
    {
      std::cout << "server start..." << std::endl;

      boost::asio::io_service ioserv;
  
      boost::asio::ip::address addr = boost::asio::ip::address::from_string("127.0.0.1");
      boost::asio::ip::tcp::endpoint endp(addr, 8888);
  
      boost::asio::ip::tcp::acceptor accp(ioserv, endp);
      // std::cout << "local_endpoint: " << accp.local_endpoint().address() << std::endl;
      std::cout << "local_endpoint: " << accp.local_endpoint() << std::endl;
      while(true)
	{
	  boost::asio::ip::tcp::socket sock(ioserv);

	  accp.accept(sock);
	  // std::cout << "client: " << sock.remote_endpoint().address() << std::endl;
	  std::cout << "client: " << sock.remote_endpoint() << std::endl;	  
	  sock.write_some(boost::asio::buffer("HelloWorld."));

	}
    }
  catch(std::exception& e)
    {
      std::cout << "exception: " << e.what() << std::endl;
    }

  
  std::cout << "" << std::endl;
  return 0;
}
