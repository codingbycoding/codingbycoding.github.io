//g++ -ggdb  -ID:\boost_1_47_0 -o  test_main.exe test_main.cpp

#include "boost/make_shared.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/scoped_ptr.hpp" 

int main()
{
  int* pi = new int(10);
  boost::shared_ptr<int> si = boost::make_shared<int>(20);

  boost::shared_ptr<int> si_1(pi);
  boost::shared_ptr<int> si_2(pi);

  std::cout << si.use_count() << std::endl;
  std::cout << si_1.use_count() << std::endl;
  std::cout << si_2.use_count() << std::endl;  
  
  //  delete pi;

  int* sspi = new int(100);
  {
    boost::scoped_ptr<int> ssi_1(sspi);
    boost::scoped_ptr<int> ssi_2(sspi);
  }
  
  boost::scoped_ptr<int> ssi_3(sspi);

  int* ppi = new int(100);
  delete ppi;
  // ppi = NULL;
  // assert(ppi);
  delete ppi;
  
  return 0;
}
