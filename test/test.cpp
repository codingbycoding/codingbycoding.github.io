//preprocessing: just process preprocess output to stdout
//g++ -E test.cpp > test.ii

//compilation: output is assemble file output to .ii
//g++ -S test.cpp

//assemble: -c compile or assemble dont link output to .s
//g++ -c test.ii

//linking: output to a.out or -o filename.suffix
//g++ test.o


//g++ test.cpp -o test.linux

//g++ test.cpp -o -DNDEBUG -O3 test.linux

#define DataCenterOperation(DataCenterObjectName, ManagerName, FunName, Args...) \
  DataCenterObjectName->Get##ManagerName()->FunName(Args)  
//DataCenterObjectName->Get#ManagerName()->FunName(Args)


// #define DataCenterOperation(DataCenterObjectName, ManagerName, FunName, Args...) \
//   DataCenterObjectName->Get#ManagerName()->FunName(Args) //enclosed in double quotation marks

#define DefPrint(Arg1) std::cout << #Arg1 << std::endl  


#include <string>
#include <iostream>

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


int main()
{
  TmDataCenter* DC = new TmDataCenter;
  // DataCenterOperation(DC, DSAManager, Print1, "Yes");
  // DataCenterOperation(DC, MatchManager, Print2, 100, "No");
  //DataCenterOperation(DC, "DSAManager", Print1, "Yes");
  DefPrint(Jack);


  
  return 0;
}
