//protoc --proto_path=. --cpp_out=./gen *.proto

//g++ test.cpp gen/*.cc -lprotobuf -o test.linux

//option optimize_for = LITE_RUNTIME; 
//g++ test.cpp gen/*.cc -lprotobuf-lite -o test.linux

#include <iostream>
#include <cstdlib>

#include "gen/testproto.pb.h"


int main(int argc, char* argv[]) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;
        
    testpackage::Response res[2];
    std::cout << "res[0] size: " << sizeof(res[0]) << " :" << res[0].res_result_code() << std::endl;
    
    res[0].set_res_result_code(100);
    std::cout << "res[0] size: " << sizeof(res[0]) << " :" << res[0].res_result_code() << std::endl;

    res[0].add_res_results("result 0");
    for(int i=0; i<res[0].res_results_size(); ++i) {
        std::cout << "| " << res[0].res_results(i);
    }
    std::cout << std::endl;


    res[0].SetExtension(testpackage::surprise, "big surprise !!!");
    std::cout << "extension:" << res[0].GetExtension(testpackage::surprise) << std::endl;

    std::cout << "ByteSize:" << res[0].ByteSize() << std::endl;


    testpackage::TestDataVoid tdv;
    std::cout << "tdv ByteSize:" << tdv.ByteSize() << std::endl;

    testpackage::TestDataInt1 tdi1;
    std::cout << "tdi1 ByteSize:" << tdi1.ByteSize() << std::endl;
    tdi1.set_data1(5);
    std::cout << "New tdi1 ByteSize:" << tdi1.ByteSize() << std::endl;
    std::cout << std::endl;


    testpackage::TestDataInt2 tdi2;
    std::cout << "tdi2 ByteSize:" << tdi2.ByteSize() << std::endl;
    tdi2.set_data1(5);
    tdi2.set_data2(65535);
    std::cout << "New tdi2 ByteSize:" << tdi2.ByteSize() << std::endl;


    testpackage::Request req;

    // testpackagebase::TimeStamp ti = testpackagebase::TimeStamp::default_instance();
    // ti.set_time(10000);
    // req.set_allocated_time(&ti);

    testpackagebase::TimeStamp* ti = new testpackagebase::TimeStamp();
    ti->set_time(10000);
    req.set_allocated_time(ti);
    
    std::cout << "time:" << req.time().time() << std::endl;

    google::protobuf::ShutdownProtobufLibrary();
    return EXIT_SUCCESS;
}
