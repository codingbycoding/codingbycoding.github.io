//g++ -g  -ID:\boost_1_47_0 -o  boost_filesystem.exe boost_filesystem.cpp D:\boost_1_47_0\mingw\stage\lib\libboost_filesystem-mgw44-mt-1_47.a  D:\boost_1_47_0\mingw\stage\lib\libboost_system-mgw44-mt-1_47.a




#include "boost/filesystem.hpp"


int main()
{
  boost::filesystem::path p("./boost_filesystem.cpp");
  std::cout << p.parent_path() << std::endl;
  std::cout << p.filename() << std::endl;
  std::cout << p.stem() << std::endl;
  std::cout << p.extension() << std::endl;
  std::cout << p.root_name() << std::endl;

  // assert(boost::filesystem::status(p).type() == boost::filesystem::file_not_found);
  // assert(boost::filesystem::status(p).type() == boost::filesystem::directory_file);
  
  return 0; 
}



