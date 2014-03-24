//g++ test.cpp -o test.linux

//preprocessing: just process preprocess output to stdout
//g++ -E test.cpp > test.ii

//compilation: output is assemble file output to .s
//g++ -S test.ii

//assemble: -c compile or assemble dont link output to .o
//g++ -c test.s

//linking: output to a.out or -o filename.suffix
//g++ test.o -o test.linux




//g++ -x c++ test.cpp -o test.linux

//g++ -x c++ test.cpp -o -DNDEBUG -O3 test.linux

#define DataCenterOperation(DataCenterObjectName, ManagerName, FunName, Args...) \
  DataCenterObjectName->Get##ManagerName()->FunName(Args)  
//DataCenterObjectName->Get#ManagerName()->FunName(Args)


// #define DataCenterOperation(DataCenterObjectName, ManagerName, FunName, Args...) \
//   DataCenterObjectName->Get#ManagerName()->FunName(Args) //enclosed in double quotation marks

#define DefPrint(Arg1) std::cout << #Arg1 << std::endl  


#include <string>
#include <iostream>

#include <cstdint>

class TmDSAManager
{
public:
  void Print1(std::string arg1)
  {
    std::cout << "class TmDSAManger::Print1()  arg1: " << arg1  << std::endl;
  }
};

class TmMatchManager
{
public:
  void Print2(int arg1, std::string arg2)
  {
    std::cout << "class TmMatchManger::Print2:: arg1: " << arg1 << "  arg2: " << arg2 << std::endl;
  }
};


class TmDataCenter
{
public:
  TmDataCenter()
  {
    m_DSAManager = new TmDSAManager;
    m_MatchManager = new TmMatchManager;
  }
  ~TmDataCenter()
  {
    delete m_DSAManager;
    delete m_MatchManager;
    m_DSAManager = NULL;
    m_MatchManager = NULL;
  }
  
  TmDSAManager* GetDSAManager()
  {
    return m_DSAManager;  
  }

  TmMatchManager* GetMatchManager()
  {
    return m_MatchManager; 
  }
  
private:
  TmDSAManager* m_DSAManager;
  TmMatchManager* m_MatchManager;
};

template<typename T>
class slist_node {
public:
  typedef T value_type;
  slist_node(T t) {
    _M_data = t;
    _M_next = NULL;
  }
  
  slist_node<T>& operator++() {
    return *(this->_M_next);
  }


  // private:
  slist_node<T>* _M_next;
  value_type _M_data;
};


// template<typename T>
// slist_node<T>* operator++() {
//   return this->_M_next;
// }



template<typename T>
std::ostream& operator<<(std::ostream& os, slist_node<T>* _node) {
  slist_node<T>* node = _node;
  os << _node->_M_data;
  while (node->_M_next != NULL) {
    //++node;
    node = node->_M_next;
    os << " " << node->_M_data;
  }
    
  return os;
}

// template<typename T>
// slist_node<T>* reverse_slist(slist_node<T>* _node) {

//   if (_node == NULL || _node->_M_next == NULL) {
//     return _node; 
//   }
  
//   slist_node<T>* nodeoriginhead = _node;
//   slist_node<T>* nodeit;
//   slist_node<T>* nodeitpre;
//   slist_node<T>* nodenewhead;
//   slist_node<T>* nodeitnew;
//   bool bNewHeadFound = false;
  
//   //nodeit = nodeoriginhead;

//   while(nodeoriginhead->_M_next != NULL) {
//     nodeit = nodeoriginhead;
//   while(nodeit->_M_next != NULL) {
//     nodeitpre = nodeit;
//     nodeit = nodeit->_M_next;
//   }
//     nodeitpre->_M_next = NULL;

//     if (bNewHeadFound == true) {
//       nodeitnew->_M_next = nodeit;
//       nodeitnew = nodeitnew->_M_next;
//     } else {
//       nodenewhead = nodeit;
//       nodeitnew = nodenewhead;
//       bNewHeadFound = true;
//     }
//   }
//   //nodeitnew->_M_next = nodeit;
//   nodeitnew->_M_next = nodeoriginhead;

//   return nodenewhead;
//   //_node = nodenewhead;
  
// }

template<typename T>
slist_node<T>* reverse_slist(slist_node<T>* slisthead) {

  if (slisthead == NULL | slisthead->_M_next == NULL ) {
    return slisthead;
  }

  slist_node<T>* cur = slisthead;
  slist_node<T>* pre = NULL;
  slist_node<T>* tmp;

  while (cur->_M_next) {
    tmp = cur;
    cur = cur->_M_next;
    tmp->_M_next = pre;
    pre = tmp;
    
  }

  cur->_M_next = pre;
  return cur;
}



class CA0 {
public:
  virtual void print0() {
    std::cout << "CA0 print0" << std::endl;
  }
  virtual void print1() {
    std::cout << "CA0 print1" << std::endl;
  }
  virtual void print2() {
    std::cout << "CA0 print2" << std::endl;    
  }
};


class CA1 : CA0 {
public:  
  virtual void print0() {
    std::cout << "CA1 print0" << std::endl;
  }
  virtual void print1() {
    std::cout << "CA1 print1" << std::endl;
  }
  virtual void print2() {
    std::cout << "CA1 print2" << std::endl;    
  }
};


class CA2 : CA1 {
public:  
  virtual void print0() {
    std::cout << "CA2 print0" << std::endl;
  }
  virtual void print1() {
    std::cout << "CA2 print1" << std::endl;
  }
  virtual void print2() {
    std::cout << "CA2 print2" << std::endl;    
  }
};

typedef void (*printfunc)(void);

int main() {
  TmDataCenter* DC = new TmDataCenter;
  // DataCenterOperation(DC, DSAManager, Print1, "Yes");
  // DataCenterOperation(DC, MatchManager, Print2, 100, "No");
  //DataCenterOperation(DC, "DSAManager", Print1, "Yes");
  DefPrint(Jack);


  slist_node<int>* slist = new slist_node<int>(10);
  slist_node<int>* slistit = slist; 
  
  for(int i=1; i<5; ++i) {
    slist_node<int>*  newNode = new slist_node<int>(i);

    while(slistit->_M_next != NULL) {
      //++(*slistit);
      slistit = slistit->_M_next;
    }

    slistit->_M_next = newNode;
    
  }



  // slistit = slist;
  // std::cout << slistit->_M_data << " "; 
  // while(slistit->_M_next != NULL) {

  //   slistit = slistit->_M_next;
  //   std::cout << slistit->_M_data << " "; 
  // }

  // std::cout << std::endl;

  std::cout << slist << std::endl;
  slist_node<int>* reslist = reverse_slist(slist);
  std::cout << reslist << std::endl;


  CA0 ca0;
  ca0.print0();

  std::cout << (int*)&ca0 << std::endl;
  //  std::cout << (int*)(ca0) << std::endl;


#if __GNUC__
#if __x86_64  || __ppc64__
  
  typedef std::int64_t myptrdiff;
  
#else
  typedef std::int32_t myptrdiff;
  
#endif
#endif
  


#if _WIN32 || _WIN64
#if _WIN64
  
  typedef std::int64_t myptrdiff;
  
#else
  typedef std::int32_t myptrdiff;
#endif
#endif

  
  printfunc pfun0 = (printfunc)*((myptrdiff*)*(myptrdiff*)(&ca0));
  pfun0();

  printfunc pfun1 = (printfunc)*(((myptrdiff*)*(myptrdiff*)(&ca0) +1) );
  pfun1();

  printfunc pfun2 = (printfunc)*(((myptrdiff*)*(myptrdiff*)(&ca0) +2) );
  pfun2();
  
  std::cout << std::showbase << (int*)&ca0 << std::endl;

  return 0;
}
