#include "SortCommon.hpp"


SortCommon::SortCommon() {
}

SortCommon::~SortCommon() {
}

double SortCommon::BenchmarkSort(const DataType *data_in, const size_t num_threads) {
	double start, stop;
	double usec;

	// Create a copy of object to sort here.
	DataType * my_data = new DataType();
	my_data->insert(my_data->begin(), data_in->begin(), data_in->end());

	// Get current time and run the sort.
	start	= GetTime();
	Sort(my_data, num_threads);
	stop	= GetTime();
	usec 	= stop - start; 

	bool result = CheckSort(my_data, data_in->size());
	delete my_data;

	if(result)
		return usec;
	else
		return (-1.0) * usec;
}

SortCommon::DataType * SortCommon::NewData(size_t size, bool ordered, bool reverse) {
	DataType * retdata = new DataType(size);

	std::generate(retdata->begin(), retdata->end(), NumGen(0));

	if(ordered)
		return retdata;

	std::reverse(retdata->begin(), retdata->end());

	if(reverse)
		return retdata;

	std::random_shuffle(retdata->begin(), retdata->end());

	return retdata;
}

void SortCommon::PrintDataType(const DataType * data_in, std::string title, bool line_before) {
	if(line_before)
		std::cout << std::endl;
	std::cout << "Printing <" << title << "> : [";
	for(DataType::const_iterator it = data_in->begin(); it != data_in->end(); ++it) {
		std::cout << *it << ",";
	}
	std::cout << "]" << std::endl;
}


bool SortCommon::CheckSort(const DataType * data_in, const size_t orig_size) {

	ContainType prevValue = 0;

	if(orig_size != data_in->size())
	{
		std::cout << std::endl << 
		"Checksort is returning false because result is length " <<
		data_in->size() << " and should be length " << orig_size << "." <<
		std::endl;

		return false;
	}

	for(DataType::const_iterator it = data_in->begin(); it != data_in->end(); ++it) {
		if(prevValue > *it) {
			std::cout << "CheckSort failed. FYI, data_in is [";
			for(DataType::const_iterator it_fail = data_in->begin(); it_fail != data_in->end(); ++it_fail) {
				std::cout << *it_fail << ",";
			}
			std::cout << "]" << std::endl;
			std::cout << std::endl << "CheckSort is returning false because " <<  prevValue << 
				" is greater than " << *it << "." << std::endl;
			return false;


		}
		prevValue = *it;
	}

	return true;

}

SortCommon::MinMaxVect SortCommon::buildPairs(size_t num_threads, size_t min, size_t max)
{
	unsigned int step_size;

	if (min <= 0)
		step_size = (max - min + 1) / num_threads;
	else
		step_size = (max - min) / num_threads;

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
		if(items_built == num_threads - 1) 
		{
			curr_max = max;
		}
		else
		{
			curr_max = curr_count + step_size - 1;
		}

		//std::cout << "Items Built: " << items_built << " Pair Min: " << curr_count << " Pair Max: " << curr_max << std::endl;

		MinMaxPairsType temp_pair(curr_count, curr_max);

		retVal.push_back(temp_pair);
		curr_count += step_size;
		items_built++;

	}

	return retVal;

}

SortCommon::MinMaxVect SortCommon::buildPow2Pairs(size_t num_threads, size_t min, size_t max)
{
	// First, determine how to get everything in a nice to split size.
	double step_size;
	size_t new_max = max;

	step_size = ((double) (new_max - min + 1) ) / num_threads;

	while(floor(log2(step_size)) != log2(step_size))
	{
		new_max++;

		step_size = ((double) (new_max - min + 1) )/ num_threads;
	}

	return buildPairs(num_threads, min, new_max);

}

size_t SortCommon::PadVector(DataType * const data_in, size_t new_length)
{
	size_t len_diff = new_length - data_in->size();

	if(len_diff > 0)
	{
		data_in->insert(data_in->end(), len_diff, 0);
	}

	return len_diff;
}

void SortCommon::UnpadVector(DataType * const data_in, size_t remove_count)
{
	data_in->erase(data_in->begin(), data_in->begin() + remove_count);
}

void SortCommon::Merge(DataType * const src, DataType * dst, size_t low, size_t pivot, size_t high){
    // Make a copy of source
    DataType * const src_cpy = new DataType(*src);

    // Create the iterators 
    DataType::iterator i       = dst->begin() + low;
    DataType::const_iterator h = src_cpy->begin() + low;
    DataType::const_iterator j = src_cpy->begin() + pivot;

    // Traverse through both areas until we get to the pivot point or the end.
    while( h != src_cpy->begin() + pivot && j != src_cpy->begin() + high + 1 )
    {
    	if((*h) <= (*j))
    	{
    		(*i) = (*h);
    		h++;
    	}
    	else
    	{
    		(*i) = (*j);
    		j++;
    	}

    	i++;

    }

    // Have reached the pivot point or the end. Determine which we are at.
    // If at pivot point on h, start where j left off and just grab other elements.
    // Else, means h has leftovers and j finished. So start at h and grab
    //   elements up to pivot.
    if(h == src_cpy->begin() + pivot)
    {
    	for(DataType::const_iterator k = j; k != src_cpy->begin() + high + 1; k++ )
    	{
    		(*i) = (*k);
    		i++;
    	}

    }
    else
    {
    	for(DataType::const_iterator k = h; k != src_cpy->begin() + pivot; k++ )
    	{
    		(*i) = (*k);
    		i++;
    	}
    }

    delete src_cpy;
}


double SortCommon::GetTime()
{
	struct timeval t;
	struct timezone tzp;
	gettimeofday(&t, &tzp);
	return t.tv_sec + t.tv_usec*1e-6;
}


