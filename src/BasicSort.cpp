#include "BasicSort.hpp"


BasicSort::BasicSort() {
	
}

BasicSort::~BasicSort() {

}


void BasicSort::Sort(DataType &data_in, const TheadCount num_threads) {
	std::sort(data_in.begin(), data_in.end());
}
