#include "BitonicSort.hpp"

BitonicSort::BitonicSort() {

}

BitonicSort::~BitonicSort() {

}

void BitonicSort::Sort(DataType * data_in, const threadCount num_threads)
{

	if(num_threads > 1)
	{

		MinMaxVect min_max_pairs;
		min_max_pairs = buildPairs(num_threads, 0, data_in->size() - 1);

		std::vector<pthread_t> threads;
		std::vector<DataType> retData;

		for(MinMaxVect::iterator it = min_max_pairs.begin(); it != min_max_pairs.end(); it++)
		{
			pthread_t 	curr_thread;

			ThreadInfo curr_thread_info(it->first, it->second, data_in);

			pthread_create(&curr_thread, NULL, &PBSort, &curr_thread_info);
			threads.push_back(curr_thread);
		}

		for(unsigned int i = 0; i < threads.size(); i++)
		{
			// TODO: Probably don't want to use NULL here. Add some return value to help out.
			pthread_join(threads[i], NULL);
		}

		unsigned int max_level 	= ((unsigned int) std::ceil(log2(min_max_pairs.size())));
		std::cout << max_level << std::endl;

		DataType retVal(data_in->size(), 0);

		for(unsigned int i = 0; i < max_level; i++)
		{
			std::cout << "I IS " << i << std::endl;
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
				std::cout << "Sort on [" << low->first << ", " << (low->first + high->second + 1) / 2 << ", " << high->second << "]" << std::endl;
				//MergeSort::Merge(data_in, data_in, low->first, (low->first + high->second + 1) / 2, high->second);
				//BMerge(true, data_in, low->first, high->second);
			}
		}

		// TODO: Now, join it all back together. Right now, just doing std::sort to have something working.
		// Need to do a more intelligible way to sort here.
		//std::sort(data_in.begin(), data_in.end());

		//MergeSort::Merge(data_in, data_in, <low>, <pivot - mid low/high>, <high>);

	}
	else
	{
		DataType * retVal = new DataType();
		retVal = BSort(true, data_in);
		data_in->swap(*retVal);
	}

}

void* BitonicSort::PBSort(void *arguments)
{
	ThreadInfo* thread_info = (ThreadInfo*)arguments;

	DataType * ret_val = new DataType();
	ret_val = BSort(thread_info);

	thread_info->data_->swap(*ret_val);

	return NULL;
}

BitonicSort::DataType * BitonicSort::BSort(bool up, DataType * data_in, size_t min, size_t max)
{
	if((max - min) <= 1)
	{
		DataType * retVal = new DataType();
		retVal->insert(retVal->begin(), data_in->begin(), data_in->end());
		return retVal;
	}
	else
	{
		size_t avg = (min + max) / 2;

		DataType first(*BSort(true, data_in, min, avg));
		DataType second(*BSort(false, data_in, avg + 1, max));

		// Concatenate the two vectors together.
		DataType *joined = new DataType();
		joined->reserve(first.size() + second.size());
		joined->insert(joined->end(), first.begin(), first.end());
	 	joined->insert(joined->end(), second.begin(), second.end());

	 	// Merge them together and return the value.
	 	DataType * retVal = new DataType();
	 	retVal = BMerge(up, joined);
	 	return retVal;
	}
}

BitonicSort::DataType * BitonicSort::BSort(ThreadInfo* thread_info) 
{
	return BSort(true, thread_info->data_, thread_info->min_, thread_info->max_);
}

BitonicSort::DataType * BitonicSort::BSort(bool up, DataType * data_in)
{
	return BSort(true, data_in, 0, data_in->size() - 1);
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

		DataType * sv1 = new DataType();
		sv1->insert(sv1->begin(), data_in->begin(), data_in->begin() + size_of_data_in / 2);
		DataType * sv2 = new DataType();
		sv2->insert(sv2->begin(), data_in->begin() + size_of_data_in / 2, data_in->end());

		DataType * first = BMerge(up, sv1);
		DataType * second = BMerge(up, sv2);

		// Join the two Vectors together
		DataType * retVal = new DataType();
		retVal->reserve(first->size() + second->size());
		retVal->insert(retVal->end(), first->begin(), first->end());
		retVal->insert(retVal->end(), second->begin(), second->end());
		free (first);
		free (second);
		return retVal;
	}
}

void BitonicSort::BCompare(bool up, DataType * data_in)
{
	const size_t dist = data_in->size() / 2;

	for(size_t i = 0; i < dist; i++)
	{
		if(data_in->at(i) > data_in->at(i + dist))
		{
			// Swap the elements
			ContainType d1 = data_in->at(i);
			ContainType d2 = data_in->at(i + dist);

			(*data_in)[i + dist] = d1;
			(*data_in)[i]        = d2;

		}
	}
}

