//g++ effective.cpp -o effective.linux

#include <iostream>
#include <cstdlib>
#include <cassert>

class A {
public:
	A() : x_(0) { //default ctor
		
	}

	explicit A(int a) { //explict to avoid impliment convert 
		
	}
	
	// A(int a) { //explict to avoid impliment convert ctor
		
	// }
	
	A(const A& rhs) { //copy ctor
		
	}

	A& operator= (const A& rhs) { //copy assign ctor
		return *this;
	}

	const int& operator[] (int index) const {
		assert(index>0 && index<100);
		return y_[index];
	}

	int& operator[] (int index) {
		return const_cast<int&>(static_cast<const A&>(*this)[index]);
	}
	
private:
	int x_;
	int y_[100];
};


class AgainstDefaultCompilerGen {

private:
	AgainstDefaultCompilerGen(const AgainstDefaultCompilerGen&);//on purpose only declare this to against compiler default gen ctor.
	AgainstDefaultCompilerGen& operator= (const AgainstDefaultCompilerGen&);//the same as above.
};


class AbstractClass {
public:
	virtual ~AbstractClass() = 0;
};


AbstractClass::~AbstractClass() {
	
}

	
int main(int argc, char* argv[]) {

	A a0;
	A a1 = a0; //use copy ctor beause here is a new object being defined.
	A a2;
	a2 = a0; //use copy assign ctor beause here isn't a new object being defined.


	enum {array_size = 10};
	int iarry[array_size]; //enum hack

	const char* p_ch;//const occur at the left of aster means pointed data is const
	char* const cch = NULL;//const occur at the right of aster means pointer itself is const
	const char* const cp_ch = NULL;



	//A tempA = 2;
	return EXIT_SUCCESS;
}
