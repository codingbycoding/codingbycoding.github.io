//C++ Primer 5th

//g++ -std=c++0x -o test.linux test.cpp

#include <iostream>

int g_TestInt;

void Testfunction()
{
  int a;
  char ch;
  std::cout << "a: " <<  a << " ch: " << ch << std::endl;
}


int main()
{

  unsigned int una = 2;
  int sib = -2;

  //!!![Caution:never mix unsigned with signed]
  std::cout << una * sib << std::endl; //!!![Caution:not -4 but 4294967292]
  std::cout << sib * una << std::endl; //!!![Caution:not -4 but 4294967292]

  std::cout << "联盟" << L'L' << std::endl;

  std::cout << "g_TestInt: " << g_TestInt << std::endl;
  Testfunction();


  // int* inull = nullptr; //c++11
  return 0;
  
}



