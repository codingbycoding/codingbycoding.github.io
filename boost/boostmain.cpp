 //bjam  --toolset=gcc --with-date_time --stagedir="D:\Source\boost_1_47_0\mingw\stage" --build-dir="D:\Source\boost_1_47_0\mingw\b2" link=static runtime-link=shared threading=multi debug release stage 



//g++ -Id:/boost_1_47_0/ -Bd:/boost_1_47_0/stage/lib -Ld:/boost_1_47_0/stage/lib -lboost_date_time-vc100-mt-gd-1_47


//g++ -ID:\Source\boost_1_47_0\include -LD:\Source\boost_1_47_0\stage\lib -lboost_date_time-vc100-mt-gd-1_47.lib

//g++ -I D:\Source\boost_1_47_0\include -L D:\Source\boost_1_47_0\mingw\stage\lib  -lboost_date_time-mgw44-mt-1_47   -o boostmain.exe boostmain.cpp

//g++ -ID:\Source\boost_1_47_0\include -o  boostmain.exe boostmain.cpp D:\Source\boost_1_47_0\mingw\stage\lib\libboost_date_time-mgw44-mt-1_47.a


#include <iostream>
#include <vector>
#include <string>

#include "boost/timer.hpp"
#include "boost/progress.hpp"

// #include "boost/date_time.hpp"
// #include "boost/date_time/gregorian/greg_date.hpp"

#include "boost/date_time/gregorian/gregorian.hpp"

//BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG will change time_duration last arg type from microseconds to nanoseconds
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#include "boost/date_time/posix_time/posix_time.hpp"


#include "boost/date_time/local_time/local_time.hpp"

#include "boost/smart_ptr.hpp"
#include "boost/make_shared.hpp"


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

boost::gregorian::date d(2013,06,15);
std::cout << boost::gregorian::to_simple_string(d) << std::endl;;

// boost::gregorian::date d_from = boost::gregorian::from_string("2013,86,15");

try
  {

boost::gregorian::date d_not(boost::date_time::not_a_date_time);
}
 catch(...)
   {
}
// if(d_from !=  boost::gregorian::date(boost::date_time::not_a_date_time) ) 
{
// std::cout << boost::gregorian::to_simple_string(d_from) << std::endl;
}

boost::gregorian::date_period dp(boost::gregorian::date(2013,06,16), boost::gregorian::days(30) );

std::cout << dp << std::endl;
dp.expand(boost::gregorian::days(30) );
std::cout << dp << std::endl;

boost::posix_time::time_duration td(12, 10, 30, 1000);
std::cout << boost::posix_time::to_simple_string(td) << std::endl;



boost::posix_time::ptime p(boost::gregorian::date(2013,06,16), boost::posix_time::hours(1) );

std::cout << "p: " << p << std::endl;





boost::posix_time::ptime ploc =  boost::posix_time::second_clock::local_time();
std::cout << "ploc: " << ploc << std::endl;


boost::posix_time::ptime plocmicrosec =  boost::posix_time::microsec_clock::local_time();//universal_time();
std::cout << "plocmicrosec: " << plocmicrosec << std::endl;



boost::local_time::tz_database tzDB;
{
boost::timer ter;
std::cout << "load date_time_zonespec.csv cost: ";
tzDB.load_from_file("D:/Source/boost_1_47_0/libs/date_time/data/date_time_zonespec.csv");
std::cout << std::endl;
}

//boost::local_time::time_zone_ptr shz = tzDB.time_zone_from_region("Asian/Shanghai"); shz == null Asia not Asian
boost::local_time::time_zone_ptr shz = tzDB.time_zone_from_region("Asia/Shanghai");
boost::local_time::time_zone_ptr nyz = tzDB.time_zone_from_region("America/New_York");

boost::local_time::local_date_time ldt_bj(boost::gregorian::date(2013,06,10), boost::posix_time::hours(5), shz, false );

std::cout << "shz.std_zone_name(): " << shz->std_zone_name() << std::endl;


boost::posix_time::time_duration flight_time = boost::posix_time::hours(15);

ldt_bj += flight_time;

std::cout << "Aisa/Shanghai: " << ldt_bj << std::endl;


boost::local_time::local_date_time ldt_ny = ldt_bj.local_time_in(nyz);
std::cout << "America/New_Yourk: " << ldt_ny << std::endl;




boost::scoped_ptr<std::string> sptr(new std::string("HelloWorld!") );
std::string* ptr = sptr.get();
// delete  ptr;
// ptr = null;

std::cout << *sptr << std::endl;

std::string* strptr = new std::string[5];
boost::scoped_array<std::string> sarray(strptr);
for(int i=0; i<5; i++)
  {
sarray[i] = std::string("Hello");

}

// std::string* strptr = new std::string[5];
// boost::scoped_array<int> sarray(new int[5]);
// for(int i=0; i<5; i++)
//   {
// sarray[i] = i;

// }

for(int i=0; i<5; i++)
  {
std::cout << "sarray[" << i << "]: " << sarray[i] << std::endl;

}




boost::shared_ptr<int> sint = boost::make_shared<int>(8);
std::cout << "boost::shared_ptr count: " << sint.use_count() << std::endl;
boost::shared_ptr<int> sint_c = sint;

std::cout << "boost::shared_ptr count: " << sint.use_count() << std::endl;


typedef std::vector<boost::shared_ptr<int> > v_s_i_t;
v_s_i_t vs(10);

int iIndex = 0;
for(v_s_i_t::iterator it=vs.begin(); it!= vs.end(); it++)
  {
    (*it) = boost::make_shared<int>(iIndex++);
  }


for(v_s_i_t::iterator it=vs.begin(); it!= vs.end(); it++)
  {
    std::cout << "**it: " << **it << std::endl;
  }

std::cout << "from beginning of function main to end total cost:"; //progress_t will disconstruct
return 0;
}
