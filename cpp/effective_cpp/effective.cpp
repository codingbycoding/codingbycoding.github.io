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

void Base::mfB() {
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


void Airplane::defaultFly(const Airport& dst_airport) {
	std::cout << "defaultFly dst_airport:" << dst_airport.name() << std::endl;
}

void Airplane::fly(const Airport& dst_airport) {
	std::cout << "Airplane::fly" << std::endl;
}

void ModeA_Airplane::fly(const Airport& dst_airport) {
	std::cout << "ModeA_Airplane::fly" << std::endl;
	Airplane::fly(dst_airport);
}

void ModeB_Airplane::fly(const Airport& dst_airport) {
	std::cout << "ModeB_Airplane::fly" << std::endl;
	Airplane::fly(dst_airport);
}

void ModeC_Airplane::fly(const Airport& dst_airport) {
	std::cout << "ModeC_Airplane::fly" << std::endl;
	Airplane::fly(dst_airport);
}


void Person::sleep() {
	std::cout << "I'm sleeping." << std::endl; 
}

void Student::snap() {
	std::cout << "Dont know slepp. Call Person::sleep to snap." << std::endl;
	Person::sleep();
}

void eat(const Person& person) {
	std::cout << "eat " << std::endl; 
}

void study(const Student& student) {
	std::cout << "study " << std::endl; 
}

template<typename T>
template<typename Y>
Calculator<T>::Calculator(const Y& rhs) {
	
}


NewHandlerHolder::NewHandlerHolder(std::new_handler nh)
	: handler_(nh) {
	
}

NewHandlerHolder::~NewHandlerHolder() {
	std::set_new_handler(handler_);
}


std::new_handler Alloc_T::currentHandler_ = 0;//why???

void* Alloc_T::operator new(std::size_t size) throw (std::bad_alloc) {
	std::set_new_handler(currentHandler_);
	std::cout << "Alloc_T::operator new" << std::endl;
	return ::operator new(size);
}


void* Alloc_T::operator new(std::size_t size, std::ostream& os) {
	std::set_new_handler(currentHandler_);
	os << "Alloc_T::operator new with std::ostream&" << std::endl;
	return ::operator new(size);
}

void* Alloc_T::operator new(std::size_t size, const std::nothrow_t&) throw () {
	std::set_new_handler(currentHandler_);
	std::cout << "Alloc_T::operator new with std::nothrow&" << std::endl;
	return ::operator new(size);
}


// void* Alloc_T::operator new(std::size_t size) {
// 	std::set_new_handler(currentHandler_);
// 	std::cout << "Alloc_T::operator new" << std::endl;
// 	return ::operator new(size);
// }

void Alloc_T::operator delete(void* p) {
	std::cout << "Alloc_T::operator delete" << std::endl;
	return ::operator delete(p);
}


std::new_handler Alloc_T::set_new_handler(std::new_handler p) {
	std::new_handler old_handler = currentHandler_;
	currentHandler_ = p;
	return old_handler;
}
