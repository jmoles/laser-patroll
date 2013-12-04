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

  while (i <= j) {
    while (data_in->at(i) < pivot)
    {
      i = QuickSort::CheckIncBound(data_in, i);
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
    QSort(data_in, left, j);
  if (i < right)
    QSort(data_in, i, right);
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
