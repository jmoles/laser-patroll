#include "BitonicSort.hpp"

BitonicSort::BitonicSort() {

}

BitonicSort::~BitonicSort() {

}

void BitonicSort::Sort(DataType * data_in, const threadCount num_threads)
{

	DataType * ret_val = new DataType();

	if(num_threads > 1)
	{

		// Build the pairs of data to split up amongst all the threads.
		MinMaxVect min_max_pairs;
		min_max_pairs = buildPairs(num_threads, 0, data_in->size() - 1);

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

		for(unsigned int i = 0; i < max_level; i++)
		{
			for(MinMaxVect::iterator it = min_max_pairs.begin(); it != min_max_pairs.end(); it++)
			{
				MinMaxVect::iterator low 	= it;

				size_t inc;
				if(i == 0)
					inc = 1;
				else
					inc = ( ( (size_t) pow(2,i + 1) ) - 1 );

				for (size_t j = 0; j < inc; j++)
				{
					it++;
					if(it == min_max_pairs.end())
						it--;
				}

				MinMaxVect::iterator high 	= it;
				//std::cout << "Sort on [" << low->first << ", " << (low->first + high->second + 1) / 2 << ", " << high->second << "]" << std::endl;
				MergeSort::Merge(ret_val, ret_val, low->first, (low->first + high->second + 1) / 2, high->second);
			}
		}
	}
	else
	{
		ret_val = BSort(true, data_in);


	}

	data_in->swap(*ret_val);

	delete ret_val;

}

void* BitonicSort::PBSort(void *arguments)
{
	ThreadInfo* thread_info = (ThreadInfo*)arguments;
	DataType * ret_val = new DataType();
	ret_val = BSort(thread_info);

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
	 	DataType * ret_val = new DataType();
	 	ret_val = BMerge(up, joined);

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
		delete sv1;
		delete sv2;

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

