#ifndef ADAM_EFFECTIVE_CPP_EFFECTIVE_H_
#define ADAM_EFFECTIVE_CPP_EFFECTIVE_H_

#include <iostream>
#include <cassert>
#include <new>


class AgainstDefaultCompilerGen {

private:
	AgainstDefaultCompilerGen(const AgainstDefaultCompilerGen&);//on purpose only declare this to against compiler default gen ctor.
	AgainstDefaultCompilerGen& operator= (const AgainstDefaultCompilerGen&);//the same as above.
};


class AbstractClass {
public:
	virtual ~AbstractClass() = 0;
};


class CarSpecification {
 public:
 CarSpecification(float speed, float price, float weight, float length, float width, float height) :
	speed_(speed),
		price_(price),
		weight_(weight),
		length_(length),
		width_(width),
		height_(height) {
		
		}

 CarSpecification() :
	speed_(0),
		price_(0),
		weight_(0),
		length_(0),
		width_(0),
		height_(0) {
		
		}	
	
 private:
	float speed_;//the declaration order will be the init order no matter what the order it will be appreance in the inialis list.
	float price_;
	float weight_;
	float length_;
	float width_;
	float height_;
};


class Car {
 public:
 Car() : carSpecification_() {
		
	}
	
	virtual ~Car() {
		inner_log(); // test ctor and dtor should not call a virtual function.
	}

	virtual void inner_log() {
		std::cout << __func__ << ":" << __LINE__ << std::endl;
	}

 private:
	CarSpecification carSpecification_;
	std::string brand_;
};


class AudiCar : public Car {
public:
	~AudiCar() {
		inner_log();
	}

	virtual void inner_log() {
		std::cout << __func__ << ":" <<  __LINE__ << std::endl;
	}
};


class BWMCar : public Car {
public:
	~BWMCar() {
		inner_log();
	}

	virtual void inner_log() {
		std::cout << __func__ << ":" << __LINE__ << std::endl;
	}
};


class Timeline {
 public:
	Timeline() {
		pTag_ = new char[100];
		/* pTag_ = {'T', 'i', 'm', 'e', 'l', 'i', 'n', 'e'}; */
	}

	~Timeline() {
		delete pTag_;
		pTag_ = NULL;
	}
	
	static const int innerVal = 1;//This is only a declare. class integral type(ints, bools, chars) only declare is OK. but the others are not.


	static const float innerF; // = 1.1f;//This is only a declare. class integral type(ints, bools, chars) only declare is OK. but the others are not.

	void print() const {
		std::cout << "Timeline:" << pTag_ << std::endl;
	}

	char* getTag() const {
		//bitFlag_ = 0;//would make compiler failed
		mut_bitFlag_ = 0;//wouldn't make compiler failed
		return pTag_;
	}
	
 private:
	enum {EVENT_SIZE = 5};//enum hack more like #define than const because access a const's address is legal, however access a #define address is noramlly illegal. And "enmu hack" is techni base of metaprogramming.  
	int max_event_per_day[EVENT_SIZE];

	char* pTag_;
	int bitFlag_;
	mutable int mut_bitFlag_;//can be modified in a const member function
};


//overuse #define example
template <typename T>
bool fun_test(const T& arg) {
	std::cout << "arg:" << arg << std::endl;
}

template <typename T>
inline void callWithMax(const T& lhs, const T& rhs) {
	fun_test(lhs > rhs ? lhs : rhs);
}


class Month {
 private:
	static Month Jan() {
		Month(1);
	}

	static Month Feb() {
		Month(2);
	}
	
 private:
	explicit Month(int mon) {
		
	}
};


class Rational {
 public:
 Rational(int numerator=0, int denominator=1) 
	 : numerator_(numerator), denominator_(denominator) {
		
	}
	
	const Rational operator*(const Rational& rhs) const {
		return Rational(numerator_ * rhs.numerator(), denominator_ * rhs.denominator());
	}

	const int numerator() const {
		return numerator_;
	}

	const int denominator() const {
		return denominator_;
	}
	
 private:
	int numerator_;
	int denominator_;
};


//if you need convert all the parameters you should make the function non-member
const Rational operator*(const Rational& lhs, const Rational& rhs);


int doSomething() throw();


class Base {
 public:
	explicit Base();
	virtual void mf1();
	virtual void mf2();
	void mf3();
	void mf4();
	virtual void mfB();//derived class derived this interface and default behavior.
 private:
	
};


class Derived : public Base {
 public:
	using Base::mf2;//make Base::mf2 available here
	explicit Derived();
	virtual void mf1();
	virtual void mf2(int x);
	void mf3();
	void mf4(); 
	
 private:
	
};


class Airport {
 public:
 Airport() : name_("Airport") {
	}

	const std::string name() const {
		return name_;
	} 
 private:	
	std::string name_;	
};

class Airplane {
 public:
	virtual void fly(const Airport& dst_airport) = 0;//pure virtual method but still has its definition and it must be redefine in its derived class.
	
 protected:
	void defaultFly(const Airport& dst_airport);
	
 
};

class ModeA_Airplane : public Airplane {
 public:
	void fly(const Airport& dst_airport);
	
};

class ModeB_Airplane : public Airplane {
 public:
	void fly(const Airport& dst_airport);
};

class ModeC_Airplane : public Airplane {
 public:
	void fly(const Airport& dst_airport);
};


class Person {
 public:
	void sleep(); 
};

class Student : private Person { //what is private derived means ?
 public:
	void snap();
	//error: ‘Person’ is an inaccessible base of ‘Student’
};


void eat(const Person& person); 
void study(const Student& student);



class MultiBase {
	
 private:
	std::string name_;// must make all the direct derived class  inharit virtually to avoid multi data member copy 
};

class MultiA : virtual public MultiBase { //virtual derived to avoid multi data member copy of MultiBase

};

class MultiB  : virtual public MultiBase { //virtual derived to avoid multi data member copy of MultiBase

};

class MultiAB {
	
};


template <typename C>
void printSomething(const C& c) {
	typename C::const_iterator cit = c.cbegin();// if no typename keyword C::const_iterator the compiler will compilent
	//typename C::const_iterator cit = c.cbegin();// if no typename keyword C::const_iterator the compiler 
	std::cout << "*cit:" << *cit << std::endl;
}


template<typename T>
class Calculator {
 public:
	template<typename Y>//use member function template to accept "all compatible types"
		Calculator(const Y& rhs); 
};

struct t_trait_A {
	
};

struct t_trait_B {
	
};

template<typename T>
void test_trait(const T& t, t_trait_A) {
	std::cout << "t_trait_A test_trait t:" << t << std::endl;
}

template<typename T>
void test_trait(const T& t, t_trait_B) {
	std::cout << "t_trait_B test_trait t:" << t << std::endl;
}


class NewHandlerHolder {
 public:
	NewHandlerHolder(std::new_handler nh);
	~NewHandlerHolder();
	
 private:
	std::new_handler handler_;
};


class Alloc_T {
 public:
	void* operator new(std::size_t size) throw (std::bad_alloc);
	/* void* operator new(std::size_t size); */
	void* operator new(std::size_t size, std::ostream& os);
	void* operator new(std::size_t size, const std::nothrow_t&) throw (); 
	void operator delete(void*);
	static std::new_handler set_new_handler(std::new_handler p);
	
 private:
	static std::new_handler currentHandler_; 
};

#endif
