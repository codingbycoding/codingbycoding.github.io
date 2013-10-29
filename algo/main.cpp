// g++ -std=c++98 algo_intro.cpp -o algo_intro.linux
// g++ algo_intro.cpp -o algo_intro.linux
// g++ -std=c++11 algo_intro.cpp -o algo_intro.linux

//g++ -std=c++98 -DNDEBUG algo_intro.cpp -o algo_intro.linux

#include <iostream>
#include <cassert> 

class TestAlgo
{

public:
  TestAlgo()
  {
    
  }


  ~TestAlgo()
  {
    
  }

  void Print()
  {
    m_iPrintCount++;
    std::cout << "PrintCount: " << m_iPrintCount << std::endl;
  }

  int getPrintCount()
  {
    
  }

  static int InitCount()
  {
    TestAlgo::m_iPrintCount = 0;
  }

  static void Initializa()
  {
    m_iPrintCount = 0;
  }
  
public:
  static int m_iPrintCount;
};


int TestAlgo::m_iPrintCount = TestAlgo::InitCount();

  // TestAlgo::Initializa();
template<typename T>
void inertTIPreTJ(T* t, int i, int j, int n)
{
  assert(j>=0);
  assert(i>j);
  assert(n>i);
  
  T tmp = t[i];
  int k = i;
  do
    {
      t[k] = t[k-1];
      k--;
    }
  while(k!=j);

  t[k] = tmp;

}

template<typename T>
void insertionSort(T* t, int n)
{
  assert(n>=1);

  for(int i=1; i<n; i++)
    {
      int j=0;
      do
	{
	  if(t[i] < t[j])
	    {
	      inertTIPreTJ(t, i, j, n);
	      break;
	    }
	  else
	    {
	      j++;
	    }
	  
	}
      while(j<i);
    }
}

template<typename T>
void printArray(T* t, int N)
{
  std::cout << "printArray:" << std::endl;
  for(int i=0; i<N; i++)
    {
      std::cout << t[i] << " ";
    }

  std::cout << std::endl;
}

int main()
{

  TestAlgo test;
  test.Print();
  test.Print();
  test.Print();

  int t[] = {2, 3, 2, 8, 100, 99, 23, 37, 20000, 89932, 31314, 31340};

  printArray(t, 12);
  insertionSort(t, 0);
  printArray(t, 12);
  
  return 0;
}
