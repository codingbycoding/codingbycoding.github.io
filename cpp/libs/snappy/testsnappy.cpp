///home/adam/snappy/libtool -o testsnappy.linux --mode=compile  g++ testsnappy.cpp -I/home/adam/snappy -L/home/adam/snappy/.libs -lsnappy

//g++ testsnappy.cpp -I/home/adam/snappy -L/home/adam/snappy -lsnappy -o testsnappy.linux

//g++ testsnappy.cpp -I/home/adam/snappy -L/home/adam/snappy/.libs/ -lsnappy -o testsnappy.linux


#include <string>
#include <cstdlib>
#include <cstring>

#include "snappy.h"


int main(int argc, char* argv[]) {

	// const char* input = "ZZZZZZZZZZKKKKKKKKKKZZZZZZZZZZZZZ"
	// "ZZZZZZZZZZKKKKKKKKKKZZZZZZZZZZZZZ"
	// "ZZZZZZZZZZKKKKKKKKKKZZZZZZZZZZZZZ"
	// "ZZZZZZZZZZKKKKKKKKKKZZZZZZZZZZZZZ"
	// "ZZZZZZZZZZKKKKKKKKKKZZZZZZZZZZZZZ"
	// "ZZZZZZZZZZKKKKKKKKKKZZZZZZZZZZZZZ"
	// "ZZZZZZZZZZKKKKKKKKKKZZZZZZZZZZZZZ";


	const char* input = "0123456789";
	
	size_t input_length = strlen(input); 
	char* output = new char[snappy::MaxCompressedLength(input_length)];
	size_t output_length;
	snappy::RawCompress(input, input_length, output, &output_length);

	size_t uncompressed_length;
	if(!snappy::GetUncompressedLength(output, output_length, &uncompressed_length)) {
		std::cout << "GetUncompressedLength Failed" << std::endl;
	}

	char* uncompressed = new char[uncompressed_length];
	if(!snappy::RawUncompress(output, output_length, uncompressed)) {
		std::cout << "RawUncompress Failed" << std::endl;
	}

	delete [] output;
	output = NULL;
	delete [] uncompressed;
	uncompressed = NULL;
	
	return EXIT_SUCCESS;
}
