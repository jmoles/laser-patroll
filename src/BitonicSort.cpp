#include "BitonicSort.hpp"

BitonicSort::BitonicSort() {

}

BitonicSort::~BitonicSort() {

}

void BitonicSort::Sort(DataType * data_in, const threadCount num_threads)
{

	DataType * ret_val  = new DataType();

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
			

			ThreadInfo * curr_thread_info = new ThreadInfo(it->first, it->second, data_in, ret_val, 0, vector_mutex);

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
							pad_len += PadVector(ret_val, ret_val->size() + elem_to_add);

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
					Merge(ret_val, ret_val, low_i, pivot_i, high_i);
            }
		}

		UnpadVector(ret_val, pad_len);

		data_in->swap(*ret_val);
	}
	else
	{
		// Need to make sure the length of data_in is a power of 2.
		size_t pad_len = PadVector(data_in, (size_t) pow(2,ceil(log2(data_in->size()))));

		// Actually perform the sort.
		ret_val = BSort(true, data_in);
		UnpadVector(ret_val, pad_len);

		data_in->swap(*ret_val);
	}

	delete ret_val;


}

void* BitonicSort::PBSort(void *arguments)
{
	ThreadInfo* thread_info = (ThreadInfo*)arguments;
	DataType * ret_val = BSort(thread_info);

	// Swap the returned data in
	pthread_mutex_lock(thread_info->mutex_);
	thread_info->dst_->insert(thread_info->dst_->end(), ret_val->begin(), ret_val->end());
	pthread_mutex_unlock(thread_info->mutex_);

	delete ret_val;

	pthread_exit((void *) 0);
}

BitonicSort::DataType * BitonicSort::BSort(bool up, DataType * data_in, size_t min, size_t max)
{
	if((max - min) <= 0)
	{
		DataType * ret_val = new DataType(1, data_in->at(min));
		return ret_val;
	}
	else
	{
		size_t avg = ((min + max + 1) / 2);

		DataType * first  = BSort(true, data_in, min, avg - 1);
		DataType * second = BSort(false, data_in, avg, max);

		// Concatenate the two vectors together.
		DataType * joined = new DataType();
		joined->reserve(first->size() + second->size());
		joined->insert(joined->end(), first->begin(), first->end());
	 	joined->insert(joined->end(), second->begin(), second->end());

	 	// Merge them together and return the value.
	 	DataType * ret_val = BMerge(up, joined);

	 	// Clean up data
	 	delete first;
	 	delete second;
	 	delete joined;

	 	return ret_val;
	}
}

BitonicSort::DataType * BitonicSort::BSort(ThreadInfo* thread_info) 
{
	return BSort(true, thread_info->data_, thread_info->min_, thread_info->max_);
}

BitonicSort::DataType * BitonicSort::BSort(bool up, DataType * data_in)
{
	return BSort(up, data_in, 0, data_in->size() - 1);
}

BitonicSort::DataType * BitonicSort::BMerge(bool up, DataType * data_in)
{
	const size_t size_of_data_in = data_in->size();

	if(size_of_data_in == 1)
	{
		return data_in;
	}
	else
	{
		BCompare(up, data_in);

		// Create two sub-vectors to store the data temporarily.
		DataType * sv1 = new DataType();
		DataType * sv2 = new DataType();
		sv1->insert(sv1->begin(), data_in->begin(), data_in->begin() + size_of_data_in / 2);
		sv2->insert(sv2->begin(), data_in->begin() + size_of_data_in / 2, data_in->end());

		// Build the first and second vector with BMerge.
		DataType * first = BMerge(up, sv1);
		DataType * second = BMerge(up, sv2);

		// Join the two Vectors together
		DataType * ret_val = new DataType();
		ret_val->reserve(first->size() + second->size());
		ret_val->insert(ret_val->end(), first->begin(), first->end());
		ret_val->insert(ret_val->end(), second->begin(), second->end());

		// Clean up everything that is no longer needed.
		delete first;
		delete second;

		return ret_val;
	}
}

void BitonicSort::BCompare(bool up, DataType * data_in)
{
	const size_t dist = data_in->size() / 2;

	for(size_t i = 0; i < dist; i++)
	{

		if((data_in->at(i) > data_in->at(i + dist)) == up)
		{
			// Swap the elements
			ContainType d1 = data_in->at(i);
			ContainType d2 = data_in->at(i + dist);

			(*data_in)[i + dist] = d1;
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

