//C++ Primer 5th

//gcc 4.8.2
//g++ -std=c++11 -o test.linux test.cpp
//g++ -std=c++11 -m32 -o test.linux test.cpp


#include <iostream>
#include <vector>
#include <string>

#include <iterator>


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


  std::vector<int> ivec = {2, 3, 4};
  for(auto i : ivec)
  {
    std::cout << i;
    
  }
  std::cout << std::endl;


  std::string strarr[] = {"abc", "123", "World"};

  std::string* strbeg = begin(strarr);
  std::string* strend = end(strarr);
  for(std::string* it=strbeg; it!=strend; ++it)
  {
    std::cout << *it;
  }
  std::cout << std::endl;

  int* ip; 
  std::cout << "size(p): " << sizeof(ip) << std::endl;//-m32:4 -m64:8
  
  // int* inull = nullptr; //c++11
  return 0;
  
}



