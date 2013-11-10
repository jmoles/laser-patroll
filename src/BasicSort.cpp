#include "BasicSort.hpp"


BasicSort::BasicSort() {
	
}

BasicSort::~BasicSort() {

}


void BasicSort::Sort(DataType &data_in) {
	std::sort(data_in.begin(), data_in.end());
}
