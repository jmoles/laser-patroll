#include "MergeSort.hpp"
#include <math.h>       /* floor */

MergeSort::MergeSort() {
	
}

MergeSort::~MergeSort() {

}

void* MergeSort::Thread_MSort(void * args){
  thread_args * a = (thread_args *) args;

  MSort(a->threads_remaining, a->low, a->high);

}


void MergeSort::MSort(size_t threads_remaining, size_t low, size_t high){
    
    
    if(low<high)
    {
        size_t pivot= (low+high)/2;
        
        if (threads_remaining == 0)
        {
            if(low<high)
            {
                MSort(0,low,pivot);
                MSort(0,pivot+1,high);
              
                Merge(low,pivot,high);
            }
        }

        else // threads_remaining > 1
        {
            // set up pthreads stuff
            pthread_attr_t attr;
            pthread_t thread;
            pthread_attr_init (&attr);
            pthread_attr_setscope (&attr,PTHREAD_SCOPE_SYSTEM);
           
            // subtract 1 from threads left (one will be allocated now)
            // then divide the remainder between "children"
            size_t lt, rt; // (left threads, right threads)
            lt = rt = (threads_remaining -1)/2;
            rt += (threads_remaining-1)%2; // remainder has to go somewhere!
            
            // set up args struct to pass to new thread
            thread_args a;
            a.threads_remaining = lt;
            a.low = low;
            a.high = pivot;
            
            // new thread does left, current thread does right, current waits on left, then merges
            pthread_create(&thread, &attr, &MergeSort::Thread_MSort, (void *) &a);
            MSort(rt, pivot+1, high); 
            pthread_join(thread, NULL);
            Merge(low,pivot,high);
        }
    }
}

void MergeSort::Merge(size_t low, size_t pivot, size_t high){
    
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

void MergeSort::Sort(DataType &data_in){
    src = data_in;
    MSort(kNumThreads, src[0], src.end());
    data_in.swap(dst);    
}


