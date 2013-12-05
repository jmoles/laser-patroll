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

		// Vector to hold all of the threads that are running.
		std::vector<pthread_t> threads;

		// Prepare and actually run the threads for the sort.	
		for(MinMaxVect::iterator it = min_max_pairs.begin(); it != min_max_pairs.end(); it++)
		{
			pthread_t 	curr_thread;
			
			ThreadInfo * curr_thread_info = new ThreadInfo(it->first, it->second, data_in);

			pthread_create(&curr_thread, NULL, &PBSort, curr_thread_info);
			threads.push_back(curr_thread);
		}

		for(unsigned int i = 0; i < threads.size(); i++)
		{
			// Join each of the threads.
			pthread_join(threads[i], NULL);
		}

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

	delete thread_info;

	pthread_exit((void *) NULL);
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
