//protoc --proto_path=. --cpp_out=./gen *.proto

//g++ test.cpp gen/*.cc -lprotobuf -o test.linux

//option optimize_for = LITE_RUNTIME; 
//g++ test.cpp gen/*.cc -I/usr/local/include -lprotobuf-lite -o test.linux


#include <iostream>
#include <cstdlib>

#include "gen/testproto.pb.h"

#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

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

    const google::protobuf::Descriptor* desc = res[0].GetDescriptor();
    std::cout << "desc: " << desc->full_name() << " field_count: " << desc->field_count() << std::endl;
    std::stringstream ss;
    
    for(int i=0; i<desc->field_count(); i++) {
        const google::protobuf::FieldDescriptor* fieldDesc = desc->field(i);
        ss << i << ": name:" << fieldDesc->name() << std::endl;
    }
    


    testpackage::TestDataVoid tdv;
    std::cout << "tdv ByteSize:" << tdv.ByteSize() << std::endl;

    testpackage::TestDataInt1 tdi1;
    std::cout << "tdi1 ByteSize:" << tdi1.ByteSize() << std::endl;
    tdi1.set_data1(5);
    std::cout << "New tdi1 ByteSize:" << tdi1.ByteSize() << std::endl;
    std::cout << std::endl;

    
    std::string str;
    tdi1.SerializeToString(&str);
    std::cout << "str:" << str << std::endl;

    
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
	ti->mutable_ext_data()->set_ext_int1(2222);
	ti->mutable_ext_str()->set_ext_str_val("ext_str_val");
	ti->set_opt_name("opt_name");

	ti->add_rep_name("rep_name1");
	ti->add_rep_name("rep_name2");
	ti->add_rep_name("rep_name3");
	
    req.set_allocated_time(ti);
    
    std::cout << "time:" << req.time().time() << std::endl;

    // std::string str;
    // req.SerializeToString(&str);
    // std::cout << "str:" << str << std::endl;



	std::string str_output;
	google::protobuf::TextFormat::PrintToString(*ti, &str_output);
	std::cout << "str_output: "
			  << std::endl
			  << std::endl
			  << str_output << std::endl;

	
	// int fd = open("pbfile", O_CREAT, S_IRWXU);
	int fd = open("pbfile", O_TRUNC);
	if(-1 == fd) {
		std::cerr << "open failed! errno:" << strerror(errno) << std::endl;
	}
	
	google::protobuf::io::ZeroCopyOutputStream* raw_output = new google::protobuf::io::FileOutputStream(fd);

	if(!google::protobuf::TextFormat::Print(*ti, raw_output)) {
		std::cerr << "open failed! errno:" << strerror(errno) << std::endl;
	}

	close(fd);
    google::protobuf::ShutdownProtobufLibrary();
    return EXIT_SUCCESS;

}
