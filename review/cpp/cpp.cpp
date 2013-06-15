#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <typeinfo>

#include "cpp.h"

using namespace std;

class ArrayClass
{
public:
	ArrayClass();
	~ArrayClass();
	bool operator ==(const ArrayClass&);
	bool operator !=(const ArrayClass&);
	ArrayClass& operator = (const ArrayClass&);
};

class TestClass
{
public: 
	TestClass();

  //explicti only effective on class constructor to suppress implicit convert
  // and constructor with only one parameter default has implicit convert operation
  explicit TestClass(int _id)
    : m_Id( _id )
  {

  }

  std::string ToString()
  {
    stringstream ss;
    /*		std::string result = "TestClass";
		result = result + " id:";
		result = m_Id;*/
    ss << "TestClass" << " id:" <<  m_Id;
    return ss.str();
  }

  /*	TestClass(int _id)
	: m_Id( _id )
	{

	}*/

private:
  int m_Id;
};


template<typename T>
void printf_typeid(T type)
{
  std::cout << "printf_typeid:" << typeid(type).name() << std::endl;
}

int main()
{
  std::cout << "review cpp..." << std::endl;
	
  cout << "Run __FILE__:" << __FILE__ << " __LINE__:" << __LINE__ << " __DATE__:" << __DATE__ << " __TIME__:" << __TIME__ << endl;
	
  ofstream outfile("MakefileJ");
  if( !outfile )
    {
      cerr << "ofstream failed..." << endl;
    }
  assert(1);

  //Test non explicit class constructor
  //TestClass test = 3;
  TestClass test = TestClass(3);
  std::cout << test.ToString() << std::endl;


  std::cout << "typeid(test).name():" << typeid(test).name() << std::endl;
  std::cout << "typeid(&test).name():" << typeid(&test).name() << std::endl;

  static const int TestInt = 12;	
  //#define TestInt TestInt
#define TestInt 12.0f
	if(12 == TestInt)
	  {
	    std::cout << "TestInt equal!!!" << std::endl;
	    printf_typeid(TestInt);
	  }
	printf_typeid(0);
	return 0;
}
