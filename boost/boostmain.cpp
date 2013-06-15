//g++ -Id:/boost_1_47_0/ -Bd:/boost_1_47_0/stage/lib -Ld:/boost_1_47_0/stage/lib -lboost_date_time-vc100-mt-gd-1_47


//g++ -ID:\Source\boost_1_47_0\include -LD:\Source\boost_1_47_0\stage\lib -lboost_date_time-vc100-mt-gd-1_47.lib
#include <iostream>
#include <vector>

#include "boost/timer.hpp"
#include "boost/progress.hpp"

#include "boost/date_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"


#include "boost/smart_ptr.hpp"

int main()
{
  boost::progress_timer progress_t;
  std::cout << "boostmain.cpp" << __FILE__ << __LINE__ << std::endl;

  boost::timer t;

  std::cout << "max timespan:" << t.elapsed_max()/3600 << "h" << std::endl;



  std::vector<long> v(1000*10000);
  boost::progress_display progress_d(v.size());
  for(std::vector<long>::const_iterator it = v.begin(); it!=v.end(); it++)
    {
      // if(it != v.begin())
      // 	--it;
      ++progress_d;
    }


  std::cout << boost::gregorian::day_clock::local_day() << std::endl;

  // boost::gregorian::date d(2013,06,15);
  // std::cout << boost::gregorian::to_simple_string(d);
  return 0;
}


