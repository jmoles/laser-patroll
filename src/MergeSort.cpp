#include "MergeSort.hpp"
#include <math.h>       /* floor */

MergeSort::MergeSort() {
	
}

MergeSort::~MergeSort() {

}

void * MergeSort::Thread_MSort(void * args){
    ThreadInfo* a = (ThreadInfo*)args;

  MSort(*(a->data_), *(a->dst_), a->remain_threads_, a->min_, a->max_);

  return NULL;

}


void MergeSort::MSort(DataType &data_in, DataType &dst, const unsigned int threads_remaining, size_t low, size_t high){
    
    if(low<high)
    {
        size_t pivot= (low+high)/2;
        
        if (threads_remaining == 0)
        {
            if(low<high)
            {
                MSort(data_in, dst, 0, low, pivot);
                MSort(data_in, dst, 0, pivot + 1, high);
              
                Merge(data_in, dst, low, pivot, high);
            }
        }

        // will never run... 
        else // threads_remaining > 1
        {
            // set up pthreads stuff
            pthread_t thread;
           
            // subtract 1 from threads left (one will be allocated now)
            // then divide the remainder between "children"
            size_t lt, rt; // (left threads, right threads)
            lt = rt = (threads_remaining -1)/2;
            rt += (threads_remaining-1)%2; // remainder has to go somewhere!
            
            // set up args struct to pass to new thread
            ThreadInfo curr_thread_info(low, pivot, &data_in, &dst, lt);
            
            // new thread does left, current thread does right, current waits on left, then merges
            pthread_create(&thread, NULL, &Thread_MSort, &curr_thread_info);
            MSort(data_in, dst, rt, pivot+1, high); 
            pthread_join(thread, NULL);
            Merge(data_in, dst, low, pivot, high);
        }
    }
}

void MergeSort::Merge(DataType &src, DataType &dst, size_t low, size_t pivot, size_t high){

    
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

void MergeSort::Sort(DataType &data_in, const TheadCount num_threads){
    DataType dst(data_in.size(), 0);
    MSort(data_in, dst, (size_t) num_threads, 0, data_in.size() - 1);
    data_in.swap(dst);    
}


