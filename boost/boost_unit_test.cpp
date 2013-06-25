// #define BOOST_TEST_INCLUDED

// #define BOOST_TEST_DYN_LINK


//运行参数 exe --build_info=yes --log_level=all --show_progress=yes --output_format=xml(hrf)
#define BOOST_TEST_MAIN

#include "boost/test/unit_test.hpp"
#include "boost/smart_ptr/scoped_ptr.hpp"
#include "boost/smart_ptr/weak_ptr.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"



BOOST_AUTO_TEST_SUITE(s_test)


BOOST_AUTO_TEST_CASE(t_scoped_ptr)
{
  boost::scoped_ptr<int> p(new int(20));
  boost::shared_ptr<int> sp(new int(20));

  
  BOOST_CHECK_EQUAL(*p, 20);
  BOOST_CHECK(p);
  boost::weak_ptr<int> wp = sp;
  BOOST_CHECK_EQUAL(wp.use_count(), 1);

  boost::shared_ptr<int> sp_copy = sp;

  BOOST_CHECK_EQUAL(sp.use_count(), 1);
  p.reset();
  BOOST_CHECK(p);
}


BOOST_AUTO_TEST_CASE(t_test)
{
  boost::scoped_ptr<int> p(new int(20));

  BOOST_CHECK_EQUAL(*p, 10);
  BOOST_CHECK(1);
}




BOOST_AUTO_TEST_SUITE_END()
