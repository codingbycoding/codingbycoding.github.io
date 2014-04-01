//g++ test.cpp gen/*.cc -lprotobuf -o test.linux

#include <iostream>
#include <cstdlib>

#include "gen/testproto.pb.h"


int main(int argc, char* argv[]) {

  testpackage::Response res;
  res.set_res_result("test res_result");
  std::cout << "res size: " << sizeof(res) << " :" << res.res_result() << std::endl;
  
  return EXIT_SUCCESS;
}
