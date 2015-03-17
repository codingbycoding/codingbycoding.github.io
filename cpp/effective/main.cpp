//g++ main.cpp effective.cpp a.cpp b.cpp -o effective.linux


#include <iostream>
#include <cstdlib>


#include "effective.h"
#include "a.h"
#include "b.h"

//#include <tr1/shared_ptr.h>

#include <boost/shared_ptr.hpp>

void bad_use_of_define();


void local_static_fun() {
	static int local_counter = 0;//this is what calls local-static(static variable in a function.
	std::cout << __func__ << "local_counter:" << local_counter++ << std::endl;
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


	AudiCar audi;

	std::cout << "Timeline::innerVal:" << Timeline::innerVal << std::endl;

	std::cout << "Timeline::innerF:" << Timeline::innerF << std::endl;
	
	//A tempA = 2;

	bad_use_of_define();

	callWithMax(88, 10);

	Timeline tl;
	tl.print();
	char* testch = tl.getTag();
	testch[0] = 'H';//const member function return value has been modified here.
	tl.print();

	local_static_fun();
	local_static_fun();
	//std::tr1::shared_ptr<A> apA;
	boost::shared_ptr<A> apA;


	int ax = 2;
	int ay = 3;
	std::swap(ax, ay);
	std::cout << "ax:" << ax << " ay:" << ay << std::endl;

	//two old-style casts. 
	//C-style cast
	// (T)expression;

	//function-style
	//T(expression);

	

	//new-style(four C++-style casts)
	// const_cast<T>(expression); //cast away the constness
	// dynamic_cast<T>(expression); //safe downcasting.
	// reinterpret_cast<T>(expression); //
	// static_cast<T>(expression);//implicit conversion

	
	Derived d;
	d.mf1();
	d.mf2();
	d.mf3();
	d.mf4();
	
	
	return EXIT_SUCCESS;
}
