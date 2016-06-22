//g++ inside_cpp_obj.cpp -o inside_cpp_obj.linux

#include <iostream>
#include "inside_cpp_obj.h"


CEmpty::CEmpty() {
	std::cout << "CEmpty size:" << sizeof(*this) << std::endl;
}


CBase::CBase() {
	std::cout << "CBase size:" << sizeof(*this) << std::endl;
}

CX::CX() {
	std::cout << "CX size:" << sizeof(*this) << std::endl;
}

void CX::abc() {
	
}

CY::CY() {
	std::cout << "CY size:" << sizeof(*this) << std::endl;
}

void CY::cba() {
}


CXY::CXY() {
	std::cout << "CXY size:" << sizeof(*this) << std::endl;
}

CSize::CSize() : count_(0), dummy_count_(0) {// the initialization sequence is the sequence of the member declare in class.
	std::cout << "class CSize size:" << sizeof(*this) << std::endl;
}

CSize::~CSize() {
	
}


void CSize::Echo() {
	std::cout << "CSize::Echo()" << std::endl;
}


CSizeDerived::CSizeDerived() {
	std::cout << "class CSizeDerived size:" << sizeof(*this) << std::endl;
}

CSizeDerived::~CSizeDerived() {
	
}

void CSizeDerived::Echo() {
	std::cout << "CSizeDerived::Echo()" << std::endl;
}

int main(int argc, char* argv[]) {
	CSize size;
	CSizeDerived size_derived;

	size_derived.Echo();
	size = size_derived; //copy ctor will directly address vptr of CSize instead of copy from CSizeDerived 
	
	size.Echo();
	(static_cast<CSizeDerived*>(&size))->Echo();//failed... because size = size_derived will sliced the part of CSizeDerived and vptr will relocate to CSize vtbl  ...

	//bitwise copy semantics will be invalid if a class has a virtual base class
	
	// size_derived = static_cast<CSizeDerived>(size);//failed 
	
	
	std::cout << "sizeof(int):" << sizeof(int) << std::endl;

	CEmpty empty;

	CXY cxy;

	
	return 0;
}
