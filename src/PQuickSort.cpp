#include "PQuickSort.hpp"


PQuickSort::PQuickSort() {
	
}

PQuickSort::~PQuickSort() {

}


void PQuickSort::Sort(DataType &data_in) {
  // Call sort on the entire array (0 to size)
  RecursiveSort(data_in, 0, data_in.size());
}

void PQuickSort::RecursiveSort(DataType &data_in, size_t left, size_t right) {

  size_t i = left, j = right;
  size_t tmp;
  size_t pivot = data_in[(left + right) / 2];
  size_t thread_Lside, thread_Rside;


  /* partition */
  while (i <= j) 
  {
    if(!kNumThreads)
    {
    // last sort, put in data and merge
    //merge();)
    
    }
  
    else
    {
      kNumThreads -= 1;
      pthread_t thread;
      thread_Lside = thread_Rside = kNumThreads/2;
      if (knumthreads % 2)  //if odd # of threads, randomly assign to side
      {
      //do srand()
        if (rand) thread_Lside += 1;
        else thread_Rside += 1;
      }
      //call sort again, with what args?
      
      //get necessary thread info for create
      //put correct args in the following:
      pthread_create(args);
      RecursiveSort(args);
      pthread_join(args);
      Merge(vector1, vector2);

      //actual work, put in function
      while (data_in[i] < pivot)
        i++;
      
      while (data_in[j] > pivot)
        j--;   
    
      if (i <= j) 
      {
        tmp = data_in[i];
        data_in[i] = data_in[j];
        data_in[j] = tmp;
        i++;
        j--;
      }
    }
  }
 
  /* recursion */
  if (left < j)
    RecursiveSort(data_in, left, j);
  
  if (i < right)
    RecursiveSort(data_in, i, right);
}
