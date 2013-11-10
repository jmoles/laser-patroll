#include "BasicSort.hpp"


BasicSort::BasicSort() {
	nextNumVal = 0;
}


void BasicSort::Sort(DataType &data_in) {
	std::sort(data_in.begin(), data_in.end());
}


BasicSort::DataType BasicSort::NewData(size_t size) {
	DataType retdata(size);

	std::generate(retdata.begin(), retdata.end(), [&] { return nextNumVal++; });
	std::random_shuffle(retdata.begin(), retdata.end());

	return retdata;
}


bool BasicSort::CheckSort(const DataType &data_in) {

	ContainType prevValue = 0;

	for(DataType::const_iterator it = data_in.begin(); it != data_in.end(); ++it) {
		if(prevValue > *it) {
			return false;
			std::cout << "CheckSort is returning true because " <<  prevValue << 
				" is greater than " << *it << "." << std::endl;

		}
		prevValue = *it;
	}

	return true;

}
