// g++ -std=c++98 -ggdb algo_intro.cpp -o algo_intro.linux
// g++ algo_intro.cpp -o algo_intro.linux
// g++ -std=c++11 algo_intro.cpp -o algo_intro.linux

//g++ -std=c++98 -DNDEBUG algo_intro.cpp -o algo_intro.linux

#include <iostream>
#include <cstring>
#include <cassert> 
#include <cstdlib>
#include <algorithm>

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
// 	      if(t[i] >= t[j]) //different
// 		{
// 		  inertTIPostTJ(t, i, j, n);
// 		  break;
// 		}
// 	      else
// 		{
// 		  j--;//different
// 		}
	  
// 	    }
// 	  while(j>=0);
// 	}
      
//     }
// }
template<typename T>
void selectionSort(T* t, int n)
{
  assert(n>1);
  for(int i=0; i<n; i++)
    {
      int j=i+1;
      int key = t[i];
      int iIndexMin = i;
      
      while(j<n)
	{
	  if(t[j] < key)
	    {
	      key = t[j];
	      iIndexMin = j;
	    }
	  j++;
	}
      
      std::swap(t[i], t[iIndexMin]);
    } 
}


template<typename T>
void insertionSort(T* t, int n)
{
  assert(n>1);

  for(int i=1; i<n; i++)
    {
      int j=i-1;//different
      T key = t[i];

      while(j>=0 && key < t[j])
	{

	  t[j+1] = t[j];
	  j--;
	}
      t[j+1] = key;
    }

}


template<typename T>
void merge(T* t, int iBeginIndex, int iMidIndex, int iEndIndex)
{

  int n1 = iMidIndex-iBeginIndex+1;
  T* t1 = new T[n1];
  for(int i=0; i<n1; i++)
    {
      t1[i] = t[i+iBeginIndex];
    }
  
  int n2 = iEndIndex-iMidIndex;
  T* t2 = new T[n2]; 
  for(int j=0; j<n2; j++)
    {
      t2[j] = t[j+n1+iBeginIndex];
    }

  int n = n1+n2;
  int i=0;
  int j=0;
  for(int k=0; k<n; k++)
    {
      if(i<n1 && (j==n2 || t1[i] <= t2[j]) )
	{
	  t[k+iBeginIndex] = t1[i];
	  i++;
	}
      else
	{
	  t[k+iBeginIndex] = t2[j];
	  j++;
	}
    }
  
  delete [] t1;
  delete [] t2; 
}

template<typename T>
void merge_sort(T* t, int iBeginIndex, int iEndIndex)
{
  assert(iEndIndex>=iBeginIndex);
  
  if(iBeginIndex<iEndIndex)
    {
      int n = iEndIndex-iBeginIndex+1;
      
      merge_sort(t, iBeginIndex, iBeginIndex+(n/2)-1);
      merge_sort(t, iBeginIndex+(n/2), iEndIndex);
      merge(t, iBeginIndex, iBeginIndex+(n/2)-1, iEndIndex);
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

  // std::cout << "insertionSort use insertTIPreTJ" << std::endl;
  // printArray(t1, 12);
  // insertionSort(t1, 12, true);
  // printArray(t1, 12);

  // std::cout << "insertionSort use insertTIPostTJ" << std::endl;
  // printArray(t2, 12);
  // insertionSort(t2, 12, false);
  // printArray(t2, 12);

  

  std::cout << "insertionSort" << std::endl;
  printArray(t2, 12);
  insertionSort(t2, 12);
  printArray(t2, 12);
  delete[] t2;


  int* randis = new int[20];
  for(int i=0; i<20; i++)
    {
      randis[i] = random()%300;
    }

  std::cout << "insertionSort randis" << std::endl;
  printArray(randis, 20);
  insertionSort(randis, 20);
  printArray(randis, 20);
  delete[] randis;


  int* randis2selectction = new int[20];
  for(int i=0; i<20; i++)
    {
      randis2selectction[i] = random()%100;
    }

  std::cout << "selectionSort randis2selectction" << std::endl;
  printArray(randis2selectction, 20);
  selectionSort(randis2selectction, 20);
  printArray(randis2selectction, 20);
  delete[] randis2selectction;


#define NLEN 28
  int* randis2merge_sort = new int[NLEN];
  for(int i=0; i<NLEN; i++)
    {
      randis2merge_sort[i] = random()%255;
    }

  std::cout << "merge_sort randis2merge_sort" << std::endl;
  printArray(randis2merge_sort, NLEN);
  merge_sort(randis2merge_sort, 0, NLEN-1);
  printArray(randis2merge_sort, NLEN);
  delete[] randis2merge_sort; 

  
  return 0;
}
