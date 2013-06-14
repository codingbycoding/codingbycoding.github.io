
//g++ -ID:\Source\boost_1_47_0\include -BD:\Source\boost_1_47_0\stage\lib -Lboost_date_time_vc100_mt_gd-1_47.lib
#include <iostream>
#include <vector>

#include "boost/timer.hpp"
#include "boost/progress.hpp"

#include "boost/smart_ptr.hpp"

int main()
{
  boost::progress_timer progress_t;
  std::cout << "boostmain.cpp" << __FILE__ << __LINE__ << std::endl;

  boost::timer t;

  std::cout << "max timespan:" << t.elapsed_max()/3600 << "h" << std::endl;



  std::vector<long> v(10000*10000);
  boost::progress_display progress_d(v.size());
  for(std::vector<long>::const_iterator it = v.begin(); it!=v.end(); it++)
    {
      // if(it != v.begin())
      // 	--it;
      ++progress_d;
    }
  return 0;
}
