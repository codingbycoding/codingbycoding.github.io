#include <iostream>
#include <cassert>


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
