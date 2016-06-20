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

#include <map>
#include <unordered_map>



#include <stdexcept>

#include <cstdlib>

#include <numeric>
#include <algorithm>

#include <functional>


#include <memory>

#include <tuple>
#include <bitset>

#include <regex>

int g_TestInt;

void Testfunction() {
  int a;
  char ch;
  std::cout << "a: " <<  a << " ch: " << ch << std::endl;
}

//3 types def function return int(*)[5]
typedef int retType[5];
retType* func_0(int);
int (*func_1(int))[5];
auto func_2(int) -> int(*)[5];



bool checksize(const std::string& str, int size) {
  return str.size() == size;
}

class MyString_Base {

 public:
  MyString_Base()
      : m_name("") {
    
  }
  
  MyString_Base(const MyString_Base& in)
      : m_name(in.m_name) {
    
  }
  
  MyString_Base(MyString_Base&& in)
      : m_name(std::move(in.m_name)) {
    
  }
  
  virtual ~MyString_Base() {
    
  }

  MyString_Base& operator =(const MyString_Base& ) {
    
  }

  MyString_Base& operator =(MyString_Base&& ) {

    
  }

  virtual void print() {
    std::cout << "MyString_Base m_name:" << m_name; 
  }

  virtual void printProtected() {
    std::cout << "MyString_Base m_nameProtected: " << m_nameProtected; 
  }
  
 protected:
  std::string m_nameProtected;
 private:
  std::string m_name;
};


class MyString : public MyString_Base {
 public:
  MyString() : MyString_Base(), m_mystr("") {
    
  }
  
  explicit MyString(const std::string& str)
      : MyString_Base(), m_mystr(str) {
    
  }
  
  explicit MyString(std::string&& str)
      : MyString_Base(), m_mystr(str) {
    
  }

  MyString(const MyString& mystr)
      : MyString_Base() {
    
  }

  MyString(const MyString&& mystr)
      : MyString_Base() {
    
  }
    
  ~MyString() {
    
  }
  

  MyString& operator =(const MyString& mystr) {
    m_mystr = mystr.m_mystr;
    return *this;
  }

  MyString& operator =(const MyString&& mystr) {
    m_mystr = std::move(mystr.m_mystr);
    return *this;
  }


  void print() {
    std::cout << "MyString m_name: ";// << MyString_Base::m_name;n
    
  }

  void printProtected() {
    std::cout << "MyString m_nameProtected: " << m_nameProtected; 
  }
  
 private:
  friend std::ostream& operator << (std::ostream& os, const MyString& mystr) {
    os << mystr.m_mystr;
    return os;
  }

  friend std::istream& operator >> (std::istream& is, MyString& mystr) {
    is >> mystr.m_mystr;
    if(is) {
      ;
    }
    else {
      mystr.m_mystr = "";
    }
    return is;
  }

  
 private:
  std::string m_mystr;
};

template <typename T>
class Printer {
  typedef T value_type;

 public:
  Printer(const T& t)
      : m_content(t) {
    
  }

  Printer(T&& t)
      : m_content(std::move(t)) {
    
  }
  
  void operator()() {
    std::cout << m_content;
  }
  
 private:
  value_type m_content;
};


template <typename T1>
void printn(T1 t1) {
  std::cout << t1;
}

template <typename T1, typename... TArgs>
void printn(T1 t1, TArgs... args ) {
  // std::cout << sizeof...(args)+1;
  std::cout << t1 << " ";
  return printn(args...);
}
  
int main() {

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

  
      
  for(auto i : ivec) {
    std::cout << i;
    
  }
  std::cout << std::endl;


  std::string strarr[] = {"abc", "123", "World"};

  std::string* strbeg = begin(strarr);
  std::string* strend = end(strarr);
  for(std::string* it=strbeg; it!=strend; ++it) {
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
  
  if(!ili.empty()) {
    ili.erase(it);
  }

  auto it2 = ili.begin();
  //it2 = 100;

  auto it_f = ili.front();//!!![Caution return reference]
  //auto &it_f = ili.front();
  it_f = 100;
  
  std::cout << "ili: ";
  for(auto i : ili) {
    std::cout << i;
  }
  std::cout << std::endl;

  int isum = accumulate(ili.cbegin(), ili.cend(), 0);
  std::cout << "isum: " << isum << std::endl;


  std::cout << "find_if: " << std::endl;
  find_if(ili.begin(), ili.end(), [](int i){std::cout << "i: " << i << std::endl; return 3==i;});

  

  std::vector<std::string> strvec = {"Jack", "Rose", "Aka", "Page"};
  
  auto checksize3 = bind(checksize, std::placeholders::_1, 3);

  auto itfinded = find_if(strvec.begin(), strvec.end(), checksize3);
  if(itfinded != strvec.end()) {
    std::cout << "itfinded: " << *itfinded << std::endl; 
  }


  // std::istream_iterator<int> isBeg(std::cin), isEOF;
  // std::cout << accumulate(isBeg, isEOF, 0) << std::endl;

#define MAPISUNORDERED

  //#undef MAPISUNORDERED  

#ifdef   MAPISUNORDERED
   std::unordered_map<std::string, std::string> AuthorEntrymap;
#else
  std::map<std::string, std::string> AuthorEntrymap;
#endif  

  AuthorEntrymap.insert( {std::string("TCP/IP Illustrate"), std::string("Stevens")} );

  for(auto it = AuthorEntrymap.cbegin(); it!=AuthorEntrymap.cend(); ++it) {
    std::cout << it->first <<  ":" << it->second << "    ";
  }
  std::cout << std::endl;

  
  for(auto it : AuthorEntrymap) {
    std::cout << it.first <<  ":" << it.second << "    ";
  }

  std::cout << std::endl;

#ifdef   MAPISUNORDERED  
  std::cout << " buckets info:" << std::endl;
  std::cout << AuthorEntrymap.max_bucket_count() << " : " << AuthorEntrymap.bucket_count();
#endif

  std::cout << std::endl;


  std::allocator<std::string> stralloc;
  auto const palloc = stralloc.allocate(10);
  auto qalloc = palloc; 
  stralloc.construct(qalloc++, 5, 'c');
  stralloc.construct(qalloc++, 5, 'a');

  std::cout << *(qalloc-2) << std::endl;
  std::cout << *(qalloc-1) << std::endl;

  MyString mstr(std::string("my"));

  // std::cout << "MyString:" << mstr << std::endl;
  // std::cin >> mstr;
  // std::cout << "MyString:" << mstr << std::endl;

  // int ia = (int)(1.15*100);
  // int ib = (int)(1.150000*100);

  int ia = (1.15*100 + .5);
  int ib = (1.150000*100 + .5); //the term for it is truncation a fact of life in computing 
  std::cout << "ia:" << ia << " ib:" << ib << std::endl;
  

  std::map<std::string, std::function<int(int, int)> > bifunmap;

  bifunmap = {
    {"+", [](const int& lhs, const int& rhs){return lhs+rhs;} },
    {"-", [](const int& lhs, const int& rhs){return lhs-rhs;} },
    {"*", std::multiplies<int>()},
    {"/", std::divides<int>()}    
    
  };
  

  std::cout << "function map:";
  std::cout << bifunmap["+"](2, 3) << "  ";
  std::cout << bifunmap["/"](200, 4) << "  ";
  
  std::cout << std::endl;


  Printer<std::string> per("per");
  per();
  std::string strper2 = "per2";
  std::cout << std::endl;
  Printer<std::string> per2(strper2);
  per2();
  std::cout << std::endl;

  printn(2, 3, "hello", 100, "world");
  std::cout << std::endl;


  std::tuple<int, int, std::string> tup3(0, 1, "tup3");
  std::cout << "tup3:" << std::get<0>(tup3);
  std::cout << std::endl;

  decltype(tup3) tup3_2(100, 200, "tup3_2");
  std::cout << "tup3_2 size:" << std::tuple_size<decltype(tup3_2)>::value << std::endl;

  std::cout << "tup3_2:" << std::get<0>(tup3_2);
  std::cout << std::endl;


  try {
    // std::bitset<32> bitvec("2323");
    std::bitset<32> bitvec("1100");
    std::cout << "bitvec: " << bitvec << std::endl;
    std::cout << "bitvec.to_ulong(): " << bitvec.to_ulong() << std::endl;
  } catch (std::invalid_argument& e) {
    std::cout << "File: " << __FILE__ << " Line: "<< __LINE__ << " invalid_argument "<< e.what() << std::endl;
  } catch (std::overflow_error& e) {
    std::cout << "File: " << __FILE__ << " Line: "<< __LINE__ << " overflow_error "<< e.what() << std::endl;
  } catch (...) {
    std::cout << "File: " << __FILE__ << " Line: "<< __LINE__ << " catch(...) "<< std::endl;
  }



  //  std::string strpattern("^cie");
  std::string strpattern("*is*");
  //strpattern = "[[:alpha:]]*" + strpattern + "[[:alpha:]]*";
  std::string strtesttext("this");
  std::smatch reresults;
  
  try {
    std::regex re(strpattern);
    //std::regex re(strtesttext, std::regex::basic | std::regex::icase);
    if(std::regex_search("this", re)) {
      //if(std::regex_search(strtesttext, re)) {
      //std::cout << reresults.str() << std::endl;
    } else {
      std::cout << "regex_search failed." << std::endl;
    }
    

  } catch (std::regex_error& e) {
    std::cout << "File: " << __FILE__ << " Line: "<< __LINE__ <<  " " << e.what() << std::endl;
  }
  // catch (...) {
  //   std::cout << "File: " << __FILE__ << " Line: "<< __LINE__ << " catch(...) "<< std::endl;
  // }




  //   try {
  //   std::regex re(strpattern);
  //   //std::regex re(strtesttext, std::regex::basic | std::regex::icase);
  //   if(std::regex_search(strtesttext, reresults, re)) {
  //     std::cout << reresults.str() << std::endl;
  //   } else {
  //     std::cout << "regex_search failed." << std::endl;
  //   }
    

  // } catch (std::regex_error& e) {
  //   std::cout << "File: " << __FILE__ << " Line: "<< __LINE__ <<  " " << e.what() << std::endl;
  // }
  // // catch (...) {
  // //   std::cout << "File: " << __FILE__ << " Line: "<< __LINE__ << " catch(...) "<< std::endl;
  // // }


  std::default_random_engine e;
  for(size_t i=0; i<5; i++) {
    std::cout << e() << " ";
  }

  std::uniform_int_distribution<unsigned> uid(0,9);
  for(size_t i=0; i<5; i++) {
    std::cout << uid(e) << " ";
  }
  
  std::cout << std::endl;

  std::cout << true << " " <<  false << " " << std::boolalpha << true << " " << false << std::endl;
  std::cout << std::noboolalpha;
  int i2cout = 87999999;
  std::cout << i2cout << " dec:" << std::dec << i2cout << " oct:" << std::oct << i2cout << " hex:" << std::hex << i2cout << std::endl;
  
  return EXIT_SUCCESS;  
}


  
  
  


  
  
  
