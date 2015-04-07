#ifndef ADAM_EFFECTIVE_CPP_B_H_
#define ADAM_EFFECTIVE_CPP_B_H_


#include <cassert>


class B {
public:
	B() : x_(0) { //default ctor
		
	}

	explicit B(int b) { //explict to avoid impliment convert 
		
	}
	
	// B(int b) { //explict to avoid impliment convert ctor
		
	// }
	
	B(const B& rhs) { //copy ctor
		
	}

	B& operator= (const B& rhs) { //copy assign ctor
		return *this;//this is import princple because A=B=C will valid;
	}

	const int& operator[] (int index) const {
		assert(index>0 && index<100);
		return y_[index];
	}

	int& operator[] (int index) {
		return const_cast<int&>(static_cast<const B&>(*this)[index]);//casting away constness.
	}

	void print() const;
	
private:
	int x_;
	int y_[100];
};


extern B theB;

#endif
