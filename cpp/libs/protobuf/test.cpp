//protoc --cpp_out=./gen *.proto

//g++ test.cpp gen/*.cc -lprotobuf -o test.linux

#include <iostream>
#include <cstdlib>

#include "gen/testproto.pb.h"


int main(int argc, char* argv[]) {

    testpackage::Response res[2];
    std::cout << "res[0] size: " << sizeof(res[0]) << " :" << res[0].res_result() << std::endl;
    
    res[0].set_res_result("test[0] res_result");
    std::cout << "res[0] size: " << sizeof(res[0]) << " :" << res[0].res_result() << std::endl;

  
    return EXIT_SUCCESS;
}
