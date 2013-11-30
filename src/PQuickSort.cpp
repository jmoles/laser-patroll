#include "PQuickSort.hpp"


PQuickSort::PQuickSort() {
	
}

PQuickSort::~PQuickSort() {

}


void PQuickSort::Sort(DataType &data_in, const TheadCount  num_threads) {
  DataType dst(data_in.size(), 0);
  QRSort(data_in, dst, (size_t) num_threads, 0, data_in.size()-1);
  data_in.swap(dst);

}
void PQuickSort::QRSort(DataType &data_in, DataType &dst, const unsigned int num_threads, size_t left, size_t right) {

  size_t i = left, j = right;
  size_t thread_amount, tmp;
  size_t pivot = (left + right) / 2;
  size_t thread_Lside, thread_Rside;
  srand(time(NULL));
  thread_amount = num_threads;
  while (i <= j) 
  {
    if(!thread_amount)
    {
          // last sort, put in data and merge
    QRSort(data_in, dst, thread_amount, left, pivot);
    QRSort(data_in, dst, thread_amount, pivot + 1, right);
    
    Merge(data_in, dst, left, pivot, right);
    
    }
  
    else
    {
      thread_amount -= 1;
      pthread_t thread;
      thread_Lside = thread_Rside = thread_amount/2;
      if (thread_amount % 2) 
          //if odd # of threads, randomly assign to side
      {
        if (rand() % 2) thread_Lside += 1;
        else thread_Rside += 1;
      }
      ThreadInfo curr_thread_info(left, pivot, &data_in, &dst, thread_Lside);

      pthread_create(&thread, NULL, &PQuickSort::Thread_Work, &curr_thread_info);
      QRSort(data_in, dst, thread_amount, left, j);
      pthread_join(thread, NULL);

      Merge(data_in, dst, left, pivot, right);

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
    QRSort(data_in, dst, thread_amount, left, j);
  
  if (i < right)
    QRSort(data_in, dst, thread_amount, i, right);
}

void PQuickSort::Merge(DataType &src, DataType &dst, size_t low, size_t pivot, size_t high){

    
    size_t h,i,j,k;
    h=low;
    i=low;
    j=pivot+1;
      
    while((h<=pivot)&&(j<=high))
    {
        if(src[h]<=src[j])
        {
            dst[i]=src[h];
            h++;
        }
      
        else
        {
            dst[i]=src[j];
            j++;
        }
      
        i++;
    }

    if(h>pivot)
    {
        for(k=j; k<=high; k++)
        {
            dst[i]=src[k];
            i++;
        }
    }
    
    else
    {
        for(k=h; k<=pivot; k++)
        {
            dst[i]=src[k];
            i++;
        }
    }

    for(k=low; k<=high; k++) 
        src[k]=dst[k];
}

//Setup Thread info
void * PQuickSort::Thread_Work(void * args)
{
  ThreadInfo* info = (ThreadInfo*)args;

  QRSort(*(info->data_), *(info->dst_), info->remain_threads_, info->min_, info->max_);

  return NULL;

}


