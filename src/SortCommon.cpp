#include "SortCommon.hpp"


SortCommon::SortCommon() {
  kNumThreads = 1;
}

SortCommon::SortCommon(unsigned int NumThreads) {
  kNumThreads = NumThreads;
}

SortCommon::~SortCommon() {
}

double SortCommon::BenchmarkSort(const DataType &data_in) {
	time_t start, stop;
	double seconds;

	// Create a copy of object to sort here.
	DataType my_data (data_in);

	// Get current time and run the sort.
	time(&start);
	Sort(my_data);
	time(&stop);
	seconds = difftime(stop, start);

	if(CheckSort(my_data))
		return seconds;
	else
		return (-1.0) * seconds;
}

SortCommon::DataType SortCommon::NewData(size_t size) {
	DataType retdata(size);

	std::generate(retdata.begin(), retdata.end(), NumGen(0));
	std::random_shuffle(retdata.begin(), retdata.end());

	return retdata;
}


bool SortCommon::CheckSort(const DataType &data_in) {

	ContainType prevValue = 0;

	for(DataType::const_iterator it = data_in.begin(); it != data_in.end(); ++it) {
		if(prevValue > *it) {
			std::cout << "CheckSort is returning true because " <<  prevValue << 
				" is greater than " << *it << "." << std::endl;
			return false;


		}
		prevValue = *it;
	}

	return true;

}
