#include "QuickSort.hpp"

const std::string QuickSort::kTableKey    = "quick";
const std::string QuickSort::kPrettyName  = "Quick Sort";

QuickSort::QuickSort() {
	
}

QuickSort::~QuickSort() {

}


void QuickSort::Sort(DataType * data_in, const threadCount num_threads) {
  // Call sort on the entire array (0 to size)
  RecursiveSort(data_in, 0, data_in->size());
}

void QuickSort::RecursiveSort(DataType * data_in, size_t left, size_t right) {

  size_t i = left, j = right;
  size_t tmp;
  size_t pivot = (*data_in)[(left + right) / 2];
 
  /* partition */
  while (i <= j) 
  {
    while ((*data_in)[i] < pivot)
      i++;
      
    while ((*data_in)[j] > pivot)
      j--;   
    
    if (i <= j) 
    {
      tmp = (*data_in)[i];
      (*data_in)[i] = (*data_in)[j];
      (*data_in)[j] = tmp;
      i++;
      j--;
    }
  }
 
  /* recursion */
  if (left < j)
    RecursiveSort(data_in, left, j);
  
  if (i < right)
    RecursiveSort(data_in, i, right);
}
