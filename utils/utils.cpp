//g++ -std=c++0x utils.cpp -o utils.linux

#include <cstdlib>
#include <iostream>
#include <cstdint>

#ifdef __cplusplus

extern "C" {
	
#include <time.h>
}

#endif


class FunCost {
public:
	explicit FunCost(std::string funName)
		: fun_name_(funName) {
		cl_beg_ = clock();
	}
	
	~FunCost() {
		std::cout << fun_name_ << " cost:" << (clock()-cl_beg_)/(CLOCKS_PER_SEC/1000) << "ms" << std::endl;
	}
	
private:
	clock_t cl_beg_;
	std::string fun_name_;
};


int main(int argc, char* argv[]) {
	FunCost funcost(__func__);
	
	time_t ti = time(NULL);	
	std::cout << "ti:" << ti << std::endl;

	// tm* p_t = localtime(&ti);
	tm t;
	tm* p_t = localtime_r(&ti, &t);
	
	char* asct = asctime(&t);
	std::cout << "asct:" << asct << std::endl;

	for(uint64_t i = 0; i< (1UL<<32); ++i) {
		tm t;
		tm t2 = t;
	}

	return EXIT_SUCCESS;
}
