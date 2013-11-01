// g++ -std=c++98 algo_intro.cpp -o algo_intro.linux
// g++ algo_intro.cpp -o algo_intro.linux
// g++ -std=c++11 algo_intro.cpp -o algo_intro.linux

//g++ -std=c++98 -DNDEBUG algo_intro.cpp -o algo_intro.linux

#include <iostream>
#include <cstring>
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
// template<typename T>
// void inertTIPreTJ(T* t, int i, int j, int n)
// {
//   assert(j>=0);
//   assert(i>j);
//   assert(n>i);
  
//   T tmp = t[i];
//   int k = i;
//   do
//     {
//       t[k] = t[k-1];
//       k--;
//     }
//   while(k!=j);

//   t[k] = tmp;

// }



// template<typename T>
// void inertTIPostTJ(T* t, int i, int j, int n)
// {
//   assert(j>=0);
//   assert(i>j);
//   assert(n>i);
  
//   T tmp = t[i];
//   int k = i;
//   do
//     {
//       t[k] = t[k-1];
//       k--;
//     }
//   while(k!=j-1); //different to inserTIPostTJ

//   t[k] = tmp;

// }



// template<typename T>
// void insertionSort(T* t, int n, bool bforward = true)
// {
//   assert(n>=1);

//   if(bforward)
//     {
//       for(int i=1; i<n; i++)
// 	{
// 	  int j=0;//different
// 	  do
// 	    {
// 	      if(t[i] < t[j])//different
// 		{
// 		  inertTIPostTJ(t, i, j, n);//different
// 		  break;
// 		}
// 	      else
// 		{
// 		  j++;//different
// 		}
	  
// 	    }
// 	  while(j<i);
// 	}

//     }
//   else
//     {
//       for(int i=1; i<n; i++)
// 	{
// 	  int j=i-1; //different
// 	  do
// 	    {
// 	      if(t[i] <= t[j]) //different
// 		{
// 		  inertTIPostTJ(t, i, j, n);
// 		  break;
// 		}
// 	      else
// 		{
// 		  j--;//different
// 		}
	  
// 	    }
// 	  while(j>i);
// 	}
      
//     }
// }


template<typename T>
void inertTIPreTJ(T* t, int i, int j, int n)
{
  assert(j>=0);
  assert(i>j);
  assert(n>i);
  
  T tmp = t[i];
  int k = i;

  while(k!=j)
    {
      t[k] = t[k-1];
      k--;
    }


  t[k] = tmp;

}


template<typename T>
void inertTIPostTJ(T* t, int i, int j, int n)
{
  assert(j>=0);
  assert(i>j);
  assert(n>i);
  
  T tmp = t[i];
  int k = i;
  
  while(k!=j+1) //different to inserTIPostTJ    
    {
      t[k] = t[k-1];
      k--;
    }


  t[k] = tmp;

}



template<typename T>
void insertionSort(T* t, int n, bool bforward = true)
{
  assert(n>=1);

  if(bforward)
    {
      for(int i=1; i<n; i++)
	{
	  int j=0;//different
	  do
	    {
	      if(t[i] < t[j])//different
		{
		  inertTIPreTJ(t, i, j, n);//different
		  break;
		}
	      else if(t[i] = t[j])//different
		{
		  inertTIPostTJ(t, i, j, n);//different
		  break;
		}
	      else
		{
		  j++;//different
		}
	  
	    }
	  while(j<i);
	}

    }
  else
    {
      for(int i=1; i<n; i++)
	{
	  int j=i-1; //different
	  do
	    {
	      if(t[i] >= t[j]) //different
		{
		  inertTIPostTJ(t, i, j, n);
		  break;
		}
	      else if (j==0)
		{
		  inertTIPreTJ(t, i, j, n);
		  break;
		}
	      else
		{
		  j--;//different
		}
	  
	    }
	  while(j>=0);
	}
      
    }
}





template<typename T>
void insertionSort(T* t, int n)
{
  assert(n>=1);

      for(int i=1; i<n; i++)
	{
	  int j=i-1;
	  int key = t[i];
	  
	  while(j>=0)
	    {
	      if(t[i] < t[j])//different
		{
		  t[j+1] = t[j];
		  j--;//different
		}
	    }
	  t[j] = key;
	  
	  
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

  int* t1 = new int[12];
  memcpy(t1, t, 12*sizeof(int));

  int* t2 = new int[12];
  memcpy(t2, t, 12*sizeof(int));

  std::cout << "insertionSort use insertTIPreTJ" << std::endl;
  printArray(t1, 12);
  insertionSort(t1, 12, true);
  printArray(t1, 12);

  std::cout << "insertionSort use insertTIPostTJ" << std::endl;
  printArray(t2, 12);
  insertionSort(t2, 12, false);
  printArray(t2, 12);  
  
  return 0;
}
