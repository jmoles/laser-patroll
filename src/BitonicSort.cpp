#include "BitonicSort.hpp"

BitonicSort::BitonicSort() {

}

BitonicSort::~BitonicSort() {

}

void BitonicSort::Sort(DataType &data_in, const TheadCount num_threads)
{

	if(num_threads > 1)
	{

		MinMaxVect min_max_pairs;
		min_max_pairs = buildPairs(num_threads, 0, data_in.size() - 1);

		std::vector<pthread_t> threads;
		std::vector<DataType> retData;

		for(MinMaxVect::iterator it = min_max_pairs.begin(); it != min_max_pairs.end(); it++)
		{
			pthread_t 	curr_thread;

			ThreadInfo curr_thread_info(it->first, it->second, &data_in);

			pthread_create(&curr_thread, NULL, &PBSort, &curr_thread_info);
			threads.push_back(curr_thread);

			usleep(100);
		}

		for(unsigned int i = 0; i < threads.size(); i++)
		{
			// TODO: Probably don't want to use NULL here. Add some return value to help out.
			pthread_join(threads[i], NULL);
		}

		// TODO: Now, join it all back together. Right now, just doing std::sort to have something working.
		// Need to do a more intelligible way to sort here.
		std::sort(data_in.begin(), data_in.end());

	}
	else
	{
		DataType retVal(BSort(true, data_in));
		data_in.swap(retVal);
	}

}

void* BitonicSort::PBSort(void *arguments)
{
	ThreadInfo* thread_info = (ThreadInfo*)arguments;

	DataType ret_val(BSort(thread_info));

	thread_info->data_->swap(ret_val);

	return NULL;
}

BitonicSort::DataType BitonicSort::BSort(bool up, DataType &data_in, size_t min, size_t max)
{
	if((max - min) <= 1)
	{
		return data_in;
	}
	else
	{
		size_t avg = (min + max) / 2;

		DataType first(BSort(true, data_in, min, avg));
		DataType second(BSort(false, data_in, avg + 1, max));
		DataType joined(first);
	 	joined.insert(first.end(), second.begin(), second.end());
	 	DataType retVal(BMerge(up, joined));
	 	return retVal;
	}
}

BitonicSort::DataType BitonicSort::BSort(ThreadInfo* thread_info) 
{
	return BSort(true, *(thread_info->data_), thread_info->min_, thread_info->max_);
}

BitonicSort::DataType BitonicSort::BSort(bool up, DataType &data_in)
{
	return BSort(true, data_in, 0, data_in.size() - 1);
}

BitonicSort::DataType BitonicSort::BMerge(bool up, DataType &data_in)
{
	const size_t size_of_data_in = data_in.size();

	if(size_of_data_in == 1)
	{
		return data_in;
	}
	else
	{
		BCompare(up, data_in);

		DataType sv1(subVector(data_in, 0, size_of_data_in / 2));
		DataType sv2(subVector(data_in, size_of_data_in / 2, size_of_data_in - 1));

		DataType first(BMerge(up, sv1));
		DataType second(BMerge(up, sv2));

		DataType retVal(first);
		retVal.insert(first.end(), second.begin(), second.end());
		return retVal;
	}
}

void BitonicSort::BCompare(bool up, DataType &data_in)
{
	const size_t size_of_data_in = data_in.size();
	const size_t dist            = size_of_data_in / 2;

	for(size_t i = 0; i < dist; i++)
	{
		if(data_in[i] > data_in[i + dist])
		{
			// Swap the elements
			ContainType d1 = data_in[i];
			ContainType d2 = data_in[i + dist];

			data_in[i + dist] = d1;
			data_in[i]        = d2;

		}
	}
}

