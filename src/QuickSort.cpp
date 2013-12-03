#include "QuickSort.hpp"

const std::string QuickSort::kTableKey    = "quick";
const std::string QuickSort::kPrettyName  = "Quick Sort";

QuickSort::QuickSort() {

}

QuickSort::~QuickSort() {

}


void QuickSort::Sort(DataType * data_in, const threadCount num_threads ) {
  DataType * dst = new DataType(data_in->size(),0);
  QSort(data_in, 0, data_in->size() - 1); 
  free(dst);
}

void QuickSort::QSort(DataType * data_in, size_t left, size_t right) {
  size_t i = left, j = right;
  size_t tmp;
  size_t pivot_point = (left + right)/2;
  size_t pivot = data_in->at(pivot_point);

  /* partition */
  while (i <= j) {
    while (data_in->at(i) < pivot)
      i++;
    while (data_in->at(j) > pivot)
      j--;
    if (i <= j) {
      tmp = data_in->at(i);
      data_in->at(i) = data_in->at(j);
      data_in->at(j) = tmp;
      i++;
      j--;
    }
  }
  /* recursion */
  if (left < j)
    QSort(data_in, left, j);
  if (i < right)
    QSort(data_in, i, right);
}

