#include <iostream>
#include <cassert>
#include <deque>
#include <cstdlib>

//using namespace std;

const static int intArg1 = 5;
const static int intArg2 = 15;
const static int intArg3 = 30;

const static long longArg1 = 5;
const static long longArg2 = 15;

const static int intMagic1 = 10;
const static int intMagic2 = 20;

const static float floatMagic1 = 10.2;
const static float floatMagic2 = 20.4;

const static float floatArg1 = 10.1;
const static float floatArg2 = 20.3;

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

template<typename T1, typename T2, typename T3, typename Result_Type>
Result_Type mix_sum(T1 arg1, T2 arg2, T3 arg3)
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

template<typename T>
class TemplateClass
{

	TemplateClass();

	template<typename T1>
	void copy()
	{

	}

	virtual ~TemplateClass() // template desconsturct can be virtual. because only one desconstruct can be init.
	{

	}

	// template<typename T1> 
	// virtual void virtualCopy() // template member function cannt to be virtual. because init number is not certain.
	// {

	// }	
};

int main()
{
	std::cout << "stlmain cpp..." << std::endl;

	//argument deduction. deduct T by argument intArg1.
	std::cout << "::sum(intArg1, intArg2) :" << ::sum(intArg1, intArg2) << std::endl;

	//template parameter specify by <int>
	std::cout << "::sum(intArg1, intArg2) :" << ::sum<int>(intArg1, intArg2) << std::endl;
	std::cout << "::sum(intArg1, intArg2, intMagic1) :" << ::sum<int, intMagic1>(intArg1, intArg2) << std::endl;

	//std::cout << "::sum(intArg1, intArg2) :" << ::sum<int>(intArg1, intArg2) << std::endl;
	//error: 'float' is not a valid type for a template constant parameter
	//std::cout << "::sum(floatArg1, floatArg2, floatMagic1) :" << ::sum<float, intMagic1>(floatArg1, floatArg2) << std::endl;
	std::cout << "::mix_sum(intArg1, longArg1, floatArg1) :" << ::mix_sum<int, long, float, float>(intArg1, longArg1, floatArg1) << std::endl;
	
	return EXIT_SUCCESS;
}