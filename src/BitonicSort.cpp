#include "BitonicSort.hpp"

BitonicSort::BitonicSort() {

}

BitonicSort::~BitonicSort() {

}



void BitonicSort::Sort(DataType &data_in) {
	std::sort(data_in.begin(), data_in.end());
}
