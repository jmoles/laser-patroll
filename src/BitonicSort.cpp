#include "BitonicSort.hpp"

const std::string BitonicSort::kTableKey    = "bitonic";
const std::string BitonicSort::kPrettyName  = "Bitonic Sort";

BitonicSort::BitonicSort() {

}

BitonicSort::~BitonicSort() {

}

void BitonicSort::Sort(DataType * data_in, const threadCount num_threads)
{

	if(num_threads > 1)
	{
		// Build the pairs of data to split up amongst all the threads.
		MinMaxVect min_max_pairs;
		min_max_pairs = buildPow2Pairs(num_threads, 0, data_in->size() - 1);

		// Pad the vector to be the correct length. It must be a power of two.
		size_t pad_len = PadVector(data_in, min_max_pairs.back().second + 1);

		// Prepare the infrastructure variables for threads.
		std::vector<pthread_t> threads;
		pthread_mutex_t * vector_mutex = new pthread_mutex_t;
		pthread_mutex_init(vector_mutex, NULL);

		// Prepare and actually run the threads for the sort.	
		for(MinMaxVect::iterator it = min_max_pairs.begin(); it != min_max_pairs.end(); it++)
		{
			pthread_t 	curr_thread;
			

			ThreadInfo * curr_thread_info = new ThreadInfo(it->first, it->second, data_in, NULL, 0, vector_mutex);

			pthread_create(&curr_thread, NULL, &PBSort, curr_thread_info);
			threads.push_back(curr_thread);
		}

		for(unsigned int i = 0; i < threads.size(); i++)
		{
			// TODO: Probably don't want to use NULL here. Add some return value to help out.
			pthread_join(threads[i], NULL);
		}

		// Get rid of the mutex.
		pthread_mutex_destroy(vector_mutex);

		// Now, use the Merge function in MergeSort to join all of the vectors together.
		unsigned int max_level 	= ((unsigned int) std::ceil(log2(min_max_pairs.size())));

		for(size_t i = 0; i < max_level; i++)
		{
            for(MinMaxVect::iterator it = min_max_pairs.begin(); it != min_max_pairs.end(); it++)
            {
            		size_t low_i, pivot_i, high_i;

					MinMaxVect::iterator low         = it;

					size_t inc;
					if(i == 0)
						inc = 1;
					else
						inc = ( ( (size_t) pow(2,i + 1) ) - 1 );

					for (size_t j = 0; j < inc; j++)
					{
						it++;
						if(it == min_max_pairs.end())
						{
							// Need to add a "phantom" element to the end that is just zeros and add padding.
							// Then just remove the padding later.
							it--;

							// Build a min/max pair to add that would be the next in the list.
							MinMaxPairsType temp_pair(it->second + 1, it->second + (it->second - it->first) + 1);
							min_max_pairs.insert(min_max_pairs.end(), temp_pair);

							// Determine the number of elements to add and actually add it.
							size_t elem_to_add = (it->second - it->first) + 1;
							pad_len += PadVector(data_in, data_in->size() + elem_to_add);

							// Reset the iterator to the element we just added.
							it = min_max_pairs.end() - 1;
						}
					}

					MinMaxVect::iterator high = it;

					// Set all of the indexes.
					low_i	= low->first;
					high_i	= high->second;
					pivot_i	= (low->first + high->second + 1) / 2;

					//std::cout << "Sort on [" << low_i << ", " << pivot_i << ", " << high_i << "]" << std::endl;
					Merge(data_in, data_in, low_i, pivot_i, high_i);
            }
		}

		UnpadVector(data_in, pad_len);

	}
	else
	{
		// Need to make sure the length of data_in is a power of 2.
		size_t pad_len = PadVector(data_in, (size_t) pow(2,ceil(log2(data_in->size()))));

		// Actually perform the sort.
		BSort(true, data_in);
		UnpadVector(data_in, pad_len);

	}
}

void* BitonicSort::PBSort(void *arguments)
{
	ThreadInfo* thread_info = (ThreadInfo*)arguments;
	BSort(thread_info);

	pthread_exit((void *) 0);
}

void BitonicSort::BSort(bool up, DataType * data_in, size_t min, size_t max)
{
	if((max - min) > 0)
	{
		size_t avg = ((min + max + 1) / 2);

		BSort(true, data_in, min, avg - 1);
		BSort(false, data_in, avg, max);

	 	// Merge them together and return the value.
	 	BMerge(up, data_in, min, max);
	}
}

void BitonicSort::BSort(ThreadInfo* thread_info) 
{
	BSort(true, thread_info->data_, thread_info->min_, thread_info->max_);
}

void BitonicSort::BSort(bool up, DataType * data_in)
{
	BSort(up, data_in, 0, data_in->size() - 1);
}

void BitonicSort::BMerge(bool up, DataType * data_in, size_t min, size_t max)
{
	if(min != max)
	{
		size_t avg = (min + max + 1) / 2;

		BCompare(up, data_in, min, max);

		// Build the first and second vector with BMerge.
		BMerge(up, data_in, min, avg - 1);
		BMerge(up, data_in, avg, max);

	}
}

void BitonicSort::BCompare(bool up, DataType * data_in, size_t min, size_t max)
{
	const size_t dist = (min + max + 1) / 2;

	for(size_t i = min; i < dist; i++)
	{
		if((data_in->at(i) > data_in->at(i + dist - min)) == up)
		{
			// Swap the elements
			ContainType d1 = data_in->at(i);
			ContainType d2 = data_in->at(i + dist - min);

			(*data_in)[i + dist - min] = d1;
			(*data_in)[i]        = d2;

		}

	}
}

size_t BitonicSort::PadVector(DataType * const data_in, size_t new_length)
{
	size_t len_diff = new_length - data_in->size();

	if(len_diff > 0)
	{
		data_in->insert(data_in->end(), len_diff, 0);
	}

	return len_diff;
}

void BitonicSort::UnpadVector(DataType * const data_in, size_t remove_count)
{
	data_in->erase(data_in->begin(), data_in->begin() + remove_count);
}

void BitonicSort::Merge(DataType * const src, DataType * dst, size_t low, size_t pivot, size_t high){
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
}

