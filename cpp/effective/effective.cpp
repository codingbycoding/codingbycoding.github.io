#include "effective.h"


AbstractClass::~AbstractClass() {
	
}


class MsgBuffer {
public:
	MsgBuffer() {
		
	}

	explicit MsgBuffer(char* pMsg) {
		p_msg_ = pMsg;
	}

	MsgBuffer(const MsgBuffer& rhs) : p_msg_(rhs.p_msg_) {
		
	}

	MsgBuffer& operator= (const MsgBuffer& rhs) {
		// char* pOrig = p_msg_;
		// this = new char*;
		// MsgBuffer(rhs);
		// delete orig;
		return *this;
	}

	~MsgBuffer() {
		
	}
	
private:
	char* p_msg_;
};


//pass-by-value means call copy ctor.
//pass-by-reference-to-const

//undefined behavior

const float Timeline::innerF = 1.2f;//define is here




#define CALL_WITH_MAX(a, b) fun_test((a) > (b) ? (a) : (b))

void bad_use_of_define() {
	int a = 5, b = 0;

	CALL_WITH_MAX(++a, b);//a will be added twice.
	CALL_WITH_MAX(++a, b+10);//a will be added once.
}


//non-member function for 2*Rational because 2 cann't implict convert to Rational at as first parameter.
const Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.numerator()*rhs.numerator(), lhs.denominator()*rhs.denominator());
}




int doSomething() throw() {
	
	return 0;
}


Base::Base() {
	
}

void Base::mf1() {
	std::cout << "Base LINE:" << __LINE__ << ":" << __func__ << std::endl;
}

void Base::mf2() {
	std::cout << "Base LINE:" << __LINE__ << ":" << __func__ << std::endl;
}

void Base::mf3() {
	std::cout << "Base LINE:" << __LINE__ << ":" << __func__ << std::endl;
}

void Base::mf4() {
	std::cout << "Base LINE:" << __LINE__ << ":" << __func__ << std::endl;
}


Derived::Derived() {
	
}


void Derived::mf1() {
	std::cout << "Derived LINE:" << __LINE__ << ":" << __func__ << std::endl;
}

void Derived::mf2(int x) {
	std::cout << "Derived LINE:" << __LINE__ << ":" << __func__ << ":x" << std::endl;
}

void Derived::mf3() {
	std::cout << "Derived LINE:" << __LINE__ << ":" << __func__ << std::endl;
}

void Derived::mf4() {
	std::cout << "Derived LINE:" << __LINE__ << ":" << __func__ << std::endl;
}
