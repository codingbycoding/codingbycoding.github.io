// g++ -std=c++98 -ggdb algo_intro.cpp -o algo_intro.linux
// g++ algo_intro.cpp -o algo_intro.linux
// g++ -std=c++11 algo_intro.cpp -o algo_intro.linux

// g++ -std=c++98 -DNDEBUG algo_intro.cpp -o algo_intro.linux

#include <iostream>
#include <cstring>
#include <cassert> 
#include <cstdlib>
#include <algorithm>


#include <cmath>

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
  
  delete[] t1;
  delete[] t2; 
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
void bubblesort(T* t, int n)
{
  
  for(int i=0; i< n; i++)
    {
      int j=n-1;

      while(j>i)
	{
	  if(t[j] < t[j-1])
	    {
	      std::swap(t[j], t[j-1]);
	    }
	  j--;
	}
      
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

//i : the index of root
//n : total length of t
template<typename T>
void max_heapify(T* t, int i, int n)
{
  assert(i<n);

  int leftindex = 2*i+1;
  int rightindex = 2*i+2;
  int maxindex = i;
  
  if( leftindex<n && t[leftindex]>t[i] )  //t[2i+1]; //Left[i]
    {
      maxindex = leftindex;
    }
  if(rightindex<n && t[rightindex]>t[maxindex]) //  t[2i+2]; //Right[i]
    {
      maxindex = leftindex;
    }

  // if(maxindex != i)
  //   {
  //     std::swap(t[i], t[maxindex]);
  //     max_heapify(t, maxindex, 
  //   }

 
}

template<typename T>
void build_max_heapify(T* t, int n)
{
  for(int i=n-1; i>=0; i--)
    {
      int iindex = 1-1;
      max_heapify(t, iindex, n);
    }
}


template<typename T>
int partition(T* t, int iBeginIndex, int iEndIndex)
{
  assert(iBeginIndex<=iEndIndex);
  
  T pivotValue = t[iEndIndex];
  int i = iBeginIndex-1;
  
  for(int j=iBeginIndex; j<iEndIndex; j++)
    {
      if(t[j] <= pivotValue)
	{
	  i++;
	  std::swap(t[i], t[j]);
	}
      
    }

  std::swap(t[i+1], t[iEndIndex]);
  
  return i+1;
}


template<typename T>
void quick_sort(T* t, int iBeginIndex, int iEndIndex)
{

  if(iBeginIndex<iEndIndex)
    {
      int pivotIndex = partition(t, iBeginIndex, iEndIndex);
      quick_sort(t, iBeginIndex, pivotIndex-1);
      quick_sort(t, pivotIndex+1, iEndIndex);
    }
}



template<typename T>
int randomized_partition(T* t, int iBeginIndex, int iEndIndex)
{
  assert(iBeginIndex<=iEndIndex);

  //int iRandomIndex = random(iBeginIndex, iEndIndex);
  //std::swap(t[iRandomIndex], t[iEndIndex]);
  T pivotValue = t[iEndIndex];
  int i = iBeginIndex-1;
  
  for(int j=iBeginIndex; j<iEndIndex; j++)
    {
      if(t[j] <= pivotValue)
	{
	  i++;
	  std::swap(t[i], t[j]);
	}
      
    }

  std::swap(t[i+1], t[iEndIndex]);
  
  return i+1;
}


template<typename T>
void randomized_quick_sort(T* t, int iBeginIndex, int iEndIndex)
{

  if(iBeginIndex<iEndIndex)
    {
      int pivotIndex = randomized_partition(t, iBeginIndex, iEndIndex);
      randomized_quick_sort(t, iBeginIndex, pivotIndex-1);
      randomized_quick_sort(t, pivotIndex+1, iEndIndex);
    }
}


template<typename T>
void quick_sort_mod_tail_recursion(T* t, int iBeginIndex, int iEndIndex)
{

  while(iBeginIndex<iEndIndex)
    {
      int pivotIndex = partition(t, iBeginIndex, iEndIndex);
      quick_sort(t, iBeginIndex, pivotIndex-1);
      iBeginIndex = pivotIndex+1;
    }
}


template<typename T>
void  counting_sort_t(T* t, T* t_ret, int n, int maxvalue)
{
  int* t_temp = new int[maxvalue+1];
  for(int i=0; i<=maxvalue; i++)
    {
      t_temp[i] = 0;
    }

  for(int i=0; i<n; i++)
    {
      t_temp[t[i]]++;
    }

  for(int i=1; i<=maxvalue; i++)
    {
      t_temp[i] = t_temp[i] + t_temp[i-1];
    }

  for(int i=n-1; i>=0; i--)
    {
      t_ret[t_temp[t[i]]-1] = t[i]; // array index begin at 0

      // t_ret[t_temp[t[i]]] = t[i]; // !!! error array index begin at 0      
      t_temp[t[i]]--;
    }


  delete[] t_temp;
}



void  counting_sort(int* t, int* t_ret, int n, int maxvalue)
{
  int* t_temp = new int[maxvalue+1];
  for(int i=0; i<=maxvalue; i++)
    {
      t_temp[i] = 0;
    }

  std::memset(t_temp, 0, maxvalue+1);

  for(int i=0; i<n; i++)
    {
      t_temp[t[i]]++;
    }

  for(int i=1; i<=maxvalue; i++)
    {
      t_temp[i] = t_temp[i] + t_temp[i-1];
    }

  for(int i=n-1; i>=0; i--)
    {
      t_ret[t_temp[t[i]]-1] = t[i]; // array index begin at 0

      // t_ret[t_temp[t[i]]] = t[i]; // !!! error array index begin at 0      
      t_temp[t[i]]--;
    }


  delete[] t_temp;
}


void radix_sort_test(char** t, char** t_ret, int di, int dj)
{
  for(int i=di-1; i>=0; i--)
    {
      // counting_sort_t(t[i], , dj, 'z');
    }


  // t_temp[t[i][j]]++;
  // t_temp[t[x][j]]++;

  // t_ret

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


#define NLEN 26
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


#define BUBBLE_NLEN 26
  int* randis2bubblesort = new int[BUBBLE_NLEN];
  for(int i=0; i<BUBBLE_NLEN; i++)
    {
      randis2bubblesort[i] = random()%500;
    }

  std::cout << "bubblesort randis2bubblesort" << std::endl;
  printArray(randis2bubblesort, BUBBLE_NLEN);
  bubblesort(randis2bubblesort, BUBBLE_NLEN);
  printArray(randis2bubblesort, BUBBLE_NLEN);
  delete[] randis2bubblesort;



#define HEAP_NLEN 9
  int* randis2heapsort = new int[HEAP_NLEN];
  for(int i=0; i<HEAP_NLEN; i++)
    {
      randis2heapsort[i] = random()%372;
    }

  std::cout << "heapsort randis2heapsort" << std::endl;
  printArray(randis2heapsort, HEAP_NLEN);
  build_max_heapify(randis2heapsort, HEAP_NLEN);
  printArray(randis2heapsort, HEAP_NLEN);
  delete[] randis2heapsort;     


  
  std::cout << "log10(8): " << log10(8) << std::endl;
  std::cout << "log10(2): " << log10(2) << std::endl;
  std::cout << "log10(8)/log10(2): " << log10(8)/log10(2) << std::endl;  

#define ARRAR_LENGTH 10
  int* randis2quick_sort = new int[ARRAR_LENGTH];
  for(int i=0; i<ARRAR_LENGTH; i++)
    {
      randis2quick_sort[i] = random()%372;
    }
  
  std::cout << "quick_sort randis2quick_sort" << std::endl;
  printArray(randis2quick_sort, ARRAR_LENGTH);
  quick_sort(randis2quick_sort, 0, ARRAR_LENGTH-1);
  printArray(randis2quick_sort, ARRAR_LENGTH);
  delete[] randis2quick_sort;



  int* randis2quick_sort_mod_tail_recursion = new int[ARRAR_LENGTH];
  for(int i=0; i<ARRAR_LENGTH; i++)
    {
      randis2quick_sort_mod_tail_recursion[i] = random()%888;
    }
  
  std::cout << "quick_sort randis2quick_sort_mod_tail_recursion" << std::endl;
  printArray(randis2quick_sort_mod_tail_recursion, ARRAR_LENGTH);
  quick_sort_mod_tail_recursion(randis2quick_sort_mod_tail_recursion, 0, ARRAR_LENGTH-1);
  printArray(randis2quick_sort_mod_tail_recursion, ARRAR_LENGTH);
  delete[] randis2quick_sort_mod_tail_recursion;


#define MEM_BUFFER_LEN 1024  
  char* MemBuffer = new char[MEM_BUFFER_LEN];
  char* testbuff = new(MemBuffer) char[200]; 

  std::cout << "MemBuffer Address: " << (int*)MemBuffer << std::endl;
  std::cout << "testbuff Address: " << (int*)testbuff << std::endl;
  testbuff[0] = 'a';

  std::cout << "MemBuffer[0]: " << MemBuffer[0] << std::endl;
  std::cout << "testbuff[0]: " << testbuff[0] << std::endl;



  int* randis2counting_sort = new int[ARRAR_LENGTH];
  int* randis2counting_sort_result = new int[ARRAR_LENGTH];
  int maxvalue = 1024;
  for(int i=0; i<ARRAR_LENGTH; i++)
    {
      randis2counting_sort[i] = random()%(maxvalue+1);
    }
  
  std::cout << "counting_sort randis2counting_sort" << std::endl;
  printArray(randis2counting_sort, ARRAR_LENGTH);
  counting_sort(randis2counting_sort, randis2counting_sort_result, ARRAR_LENGTH, maxvalue);
  printArray(randis2counting_sort_result, ARRAR_LENGTH);
  delete[] randis2counting_sort;

  
  return 0;
}
