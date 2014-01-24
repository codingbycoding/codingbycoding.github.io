//C++ Primer 5th

//gcc 4.8.2
//c++ -std=c++11 -o test.linux test.cpp
//g++ -std=c++11 -o test.linux test.cpp
//g++ -std=c++11 -m32 -o test.linux test.cpp

#include <iterator>

#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <list>

#include <stdexcept>

#include <cstdlib>

#include <numeric>


int g_TestInt;

void Testfunction()
{
  int a;
  char ch;
  std::cout << "a: " <<  a << " ch: " << ch << std::endl;
}

//3 types def function return int(*)[5]
typedef int retType[5];
retType* func_0(int);
int (*func_1(int))[5];
auto func_2(int) -> int(*)[5];



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
  std::cout << "ivec.capacity(): " << ivec.capacity() << " ivec.size(): " << ivec.size() << std::endl;

  ivec.resize(30);
  std::cout << "ivec.resize(30):" << std::endl;
  ivec.push_back(88);
  std::cout << "ivec.capacity(): " << ivec.capacity() << " ivec.size(): " << ivec.size() << std::endl;

  
      
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

  //throw std::runtime_error("test runtime_error.\n");
  
  // try
  // {
  //   throw runtime_error("test runtime_error.\n");
  // }
  // catch()
  // {
    
  // }
  // catch(...)
  // {
    
  // }
  

  std::cout << "flush." << std::flush;

  std::cout << std::endl;


  std::string strfsname("fsname.txt");
  
  // std::ofstream f1(strfsname);
  std::ofstream f1(strfsname, std::ofstream::app);
  // if(f1.good())
  // {
  //   f1 << "f1 Hello" << std::endl;
  // }
  // else
  // {
  //   std::cout << "f1.good failed." << std::endl;
  // }

  // std::ofstream f2(strfsname);
  // if(f2.good())
  // {
  //   f2 << "f2 Hello" << std::endl;
  // }
  // else
  // {
  //   std::cout << "f2.good failed." << std::endl;
  // }


  std::list<int> ili = {0, 1, 2, 3, 4, 5};

  auto it = ili.begin();//!!![Caution return iterator]
  
  if(!ili.empty())
  {
    ili.erase(it);
  }

  auto it2 = ili.begin();
  //it2 = 100;

  auto it_f = ili.front();//!!![Caution return reference]
  //auto &it_f = ili.front();
  it_f = 100;
  
  std::cout << "ili: ";
  for(auto i : ili)
  {
    std::cout << i;
  }
  std::cout << std::endl;

  int isum = accumulate(ili.cbegin(), ili.cend(), 0);
  std::cout << "isum: " << isum << std::endl; 
  
  return EXIT_SUCCESS;  
}
