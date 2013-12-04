#include "QuickSort.hpp"

const std::string QuickSort::kTableKey    = "quick";
const std::string QuickSort::kPrettyName  = "Quick Sort";

QuickSort::QuickSort() {

}

QuickSort::~QuickSort() {

}


void QuickSort::Sort(DataType * data_in, const threadCount num_threads ) {
  DataType * dst = new DataType(data_in->size(),0);
  QSort(data_in, dst, (size_t) num_threads,  0, data_in->size() - 1); 
  free(dst);
}

void QuickSort::QSort(DataType * data_in, DataType * dst, const unsigned int num_threads, size_t left, size_t right)
{
  size_t i = left, j = right;
  size_t thread_amount, tmp;
  size_t pivot_point = (left + right)/2;
  size_t pivot = data_in->at(pivot_point);
  size_t thread_Lside, thread_Rside;
  thread_amount = num_threads;

  if (num_threads > 0)
  {
   //if we still have threads available, split them
    pthread_t thread;
    thread_Lside = thread_Rside = (thread_amount-1)/2;
    //if there's a remaining thread assign it to left side
    thread_Lside += ((thread_amount-1)%2);
    

  //  std::cout<<"In num_threads > 0, = "<<num_threads<<std::endl;
    ThreadInfo curr_thread_info(left, pivot, data_in, dst, thread_Lside);
    pthread_create(&thread, NULL, Thread_work, &curr_thread_info);
    QSort(data_in, dst, thread_Rside, pivot+1, right);

    pthread_join(thread, NULL);

    //Call eric's merge from his class
    MergeSort::Merge(data_in, dst, left, pivot, right);
  }
  while (i <= j) 
  {
    while (data_in->at(i) < pivot)
    {
      i = QuickSort::CheckIncBound(data_in, i);
  //  std::cout<<"In while data_in(i) < pivot),i  = "<<i<<std::endl;
    }
    while (data_in->at(j) > pivot)
    {
      j = QuickSort::CheckDecBound(data_in, j);
    }
    if (i <= j) {
      tmp = data_in->at(i);
      (*data_in)[i] = data_in->at(j);
      (*data_in)[j] = tmp;
      i = QuickSort::CheckIncBound(data_in, i);
      j = QuickSort::CheckDecBound(data_in, j);
    }
  }

  if (left < j)
    QSort(data_in, dst, 0, left, j);
  if (i < right)
    QSort(data_in, dst, 0, i, right);
}
void * QuickSort::Thread_work(void * args)
{
  ThreadInfo * info = (ThreadInfo*)args;
  QSort(info->data_, info->dst_, info->remain_threads_, info->min_, info->max_);
  return NULL;
}

  size_t QuickSort::CheckIncBound(DataType * data_in, size_t i){
    if (i == data_in->size()-1)
    {
      return 0; 
    }
    else
    {
      return ++i;
    }
  }

  size_t QuickSort::CheckDecBound(DataType * data_in, size_t j){
    if (j == 0)
    {
      return  data_in->size() - 1;
    }
    else
    {
      return --j;
    }
  }
