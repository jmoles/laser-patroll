#include "QuickSort.hpp"


QuickSort::QuickSort() {
	
}

QuickSort::~QuickSort() {

}


void QuickSort::Sort(DataType &data_in, int left, int right) {

  int i = left, j = right;
  int tmp;
  int pivot = data_in[(left + right) / 2];
 
  /* partition */
  while (i <= j) 
  {
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
 
  /* recursion */
  if (left < j)
    Sort(data_in, left, j);
  
  if (i < right)
    Sort(data_in, i, right);
}
