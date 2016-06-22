//g++ -g  -ID:\boost_1_47_0 -o  boost_asio.exe boost_asio.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_date_time-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a -lws2_32


#define _WIN32_WINNT 0x0501 //workaround for boost  

#include "boost/asio.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/system/error_code.hpp"






class CMyTimer
{
public:
  template<typename F>
  CMyTimer(  booost::asio::io_service& IOServ, int MaxCount, F f )
    : m_Deadline(IOServ, boost::posix_time::millisec(500))
    , m_Func(f)
    , m_MaxCount(MaxCount)
    , m_Count(0)
  {
    m_Deadline.async_wait(boost::bind(&CMyTimer::CallFunc, this, boost::placeholders::error));
  }

  void CallFunc()
  {
    if(m_Count >= m_MaxCount)
      {
	return;
      }

    m_Func();
    ++m_Count;
    std::cout << "Current Count: " << m_Count << std::endl;
    m_Deadline.expires_at(m_Deadline.expires_at() + boost::posix_time::millisec(500));
    m_Deadline.async_wait(boost::bind(&CMyTimer::CallFunc, this, boost::placeholders::error));
    
  }
  
private:
  int m_Count;
  int m_MaxCount;
  boost::deadline_timer m_Deadline;
  boost::function<void()> m_Func;
};


void async_print(const boost::system::error_code& e)
{
  std::cout << "asio_print e: " << e.message() << std::endl;//e.
}


int main()
{
  boost::asio::io_service ioserv;

  boost::asio::deadline_timer dt(ioserv, boost::posix_time::seconds(1));
  std::cout << "expires_at: " << dt.expires_at() << std::endl;
  //  dt.wait();

  dt.async_wait(&async_print);
  ioserv.run();
  
  std::cout << "The End!" << std::endl;
  return 0;
}
