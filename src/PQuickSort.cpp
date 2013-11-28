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
  size_t pivot = (left + right) / 2;
  size_t thread_Lside, thread_Rside;
  srand(time(NULL));

  while (i <= j) 
  {
    if(!num_threads)
    {
    // last sort, put in data and merge
    RecursiveSort(&data_in, left, pivot);
    RecursiveSort(&data_in, pivot, right);
    
    Merge(&data_in, left, pivot, right);
    
    }
  
    else
    {
      num_threads -= 1;
      pthread_t thread;
      thread_Lside = thread_Rside = num_threads/2;
      if (num_threads % 2) 
      //if odd # of threads, randomly assign to side
      {
        if ((rand)%2) thread_Lside += 1;
        else thread_Rside += 1;
      }
      //setup dst
      ThreadInfo curr_thread_info(left, pivot, &data_in, &dst, thread_Lside);

      pthread_create(&thread, NULL, &Thread_QSort, &curr_thread_info);
      RecursiveSort(args);
      pthread_join(thread, NULL);

      Merge(&data_in, left, pivot, right);

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
 
  if (left < j)
    RecursiveSort(data_in, left, j);
  
  if (i < right)
    RecursiveSort(data_in, i, right);
}

//Setup Thread info
void * PQuickSort::Thread_Work(void * args)
{
  ThreadInfo* info = (ThreadInfo*)args;

  RecursiveSort(*(info->data_), *(info->dst_), info->remain_threads_, info->min_, info->max_;)

  return NULL;

}


