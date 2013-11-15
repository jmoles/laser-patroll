#include "MergeSort.hpp"


MergeSort::MergeSort() {
	
}

MergeSort::~MergeSort() {

}


void MergeSort::Sort(DataType &data_in) {
	std::sort(data_in.begin(), data_in.end());
}
