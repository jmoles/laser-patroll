#include "SortCommon.hpp"


SortCommon::SortCommon() {
}

SortCommon::~SortCommon() {
}

double SortCommon::BenchmarkSort(const DataType &data_in, const size_t num_threads) {
	time_t start, stop;
	double seconds;

	// Create a copy of object to sort here.
	DataType my_data (data_in);

	// Get current time and run the sort.
	time(&start);
	Sort(my_data, num_threads);
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

SortCommon::MinMaxVect SortCommon::buildPairs(size_t num_threads, size_t min, size_t max)
{
	unsigned int step_size = (max - min) / num_threads;
	unsigned int curr_count = min;
	unsigned int items_built = 0;

	size_t curr_max;

	MinMaxVect 	retVal;

	// If the step size is 0, means we have more threads than data to sort.
	if(step_size == 0)
	{
		// No need to parallelize so just return a single pair
		MinMaxPairsType temp_pair(min, max);
		retVal.push_back(temp_pair);

		return retVal;
	}

	while(items_built < num_threads)
	{
		if(items_built == num_threads) 
		{
			curr_max = max;
		}
		else
		{
			curr_max = curr_count + step_size - 1;
		}

		MinMaxPairsType temp_pair(curr_count, curr_max);

		retVal.push_back(temp_pair);
		curr_count += step_size;
		items_built++;

	}

	return retVal;

}


