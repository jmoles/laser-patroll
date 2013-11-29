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


SortCommon::DataType SortCommon::Merge(DataType &data1, DataType &data2)
{

DataType ret_data;
size_t i,j,k;
i = j = k = 0;
				
	while ( i < data1.size() && j < data2.size() ) 
	{
		if ( data1[i] > data2[j])
		{
			ret_data[k++] = data2[j++];
		}
		else
		{
			ret_data[k++] = data2[i++];
		}
	}	
	while ( i < data1.size() )
	{
		ret_data[k++] = data2[i++];
	}
	while ( j < data2.size() )
	{
		ret_data[k++] = data1[j++];
	}	
	
	return  ret_data;
	
}

SortCommon::DataType SortCommon::Merge(DataType &src, size_t low, size_t pivot, size_t high)
{
size_t i,j,k;
i = j = 0;
k = pivot + 1;
DataType ret_data, data1, data2;

	while (i <= pivot)
	{
		data1[i] = src[i];
		i++;
	}
	while (k <= src.size())
	{
		data2[j] = src[k];
		k++;
	}

	ret_data = SortCommon::Merge(data1, data2);
	return ret_data;

}

