#ifndef ADAM_EFFECTIVE_CPP_A_H_
#define ADAM_EFFECTIVE_CPP_A_H_

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
		return *this;//this is import princple because A=B=C will valid;
	}

	const int& operator[] (int index) const {
		assert(index>0 && index<100);
		return y_[index];
	}

	int& operator[] (int index) {
		return const_cast<int&>(static_cast<const A&>(*this)[index]);//casting away constness.
	}


	void testOtherObj();
	
private:
	int x_;
	int y_[100];
};

#endif
