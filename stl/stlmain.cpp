#include <iostream>
#include <cassert>
#include <deque>

using namespace std;

const static int intArg1 = 5;
const static int intArg2 = 15;
const static int intArg3 = 30;
const static long longArg1 = 5;
const static long longArg2 = 15;

const static int intMagic1 = 10;
const static int intMagic2 = 20;
const static float floatMagic1 = 10.0;
const static float floatMagic2 = 20.0;

/*template<typename T>
T sum(T arg1, T arg2)
{
	return arg1 + arg2;
}*/

/*
nontype template function parameters.
*/
/*template<typename T, int magic>
T sum(T arg1, T arg2)
{
	return arg1 + arg2 + magic;
}*/


//'float' is not a valid type for a template constant parameter
/*template<typename T, float magic>
T sum(T arg1, T arg2)
{
	return arg1 + arg2 + magic;
}*/


template<typename T=int, int magic = 100>
T sum(T arg1, T arg2)
{
	return arg1 + arg2 + magic;
}

//Overloading 
template<typename T=int, int magic = 100>
 T sum(T arg1, T arg2, T arg3)
{
	return arg1 + arg2 + arg3;
}

template<typename T>
class TStack
{
public:
	bool Empty() const
	{
		return elements.empty();
	}

	T pop()
	{

	}

private:
	std::deque<T> elements;

};

int main()
{
	std::cout << "stlmain cpp..." << std::endl;

	//argument deduction. deduct T by argument intArg1.
	std::cout << "::sum(intArg1, intArg2) :" << ::sum(intArg1, intArg2) << std::endl;

	std::cout << "::sum(intArg1, intArg2) :" << ::sum<int>(intArg1, intArg2) << std::endl;
	std::cout << "::sum(intArg1, intArg2, intMagic1) :" << ::sum<int, intMagic1>(intArg1, intArg2) << std::endl;

	//std::cout << "::sum(intArg1, intArg2) :" << ::sum<int>(intArg1, intArg2) << std::endl;
	//error: 'float' is not a valid type for a template constant parameter
	//std::cout << "::sum(floatArg1, floatArg2, floatMagic1) :" << ::sum<float, intMagic1>(floatArg1, floatArg2) << std::endl;
	
	return 0;
}

