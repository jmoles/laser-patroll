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

		std::cout << "[";
		for(DataType::iterator it = data_in->begin(); it != data_in->end(); it++){
			std::cout << *it << ",";
		}
		std::cout << "]" << std::endl;

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
				MergeSort::Merge(data_in, data_in, low->first, (low->first + high->second + 1) / 2, high->second);
				//BMerge(true, data_in, low->first, high->second);
				std::cout << "[";
				for(DataType::iterator it = data_in->begin(); it != data_in->end(); it++){
					std::cout << *it << ",";
				}
				std::cout << "]" << std::endl;
			}
		}

		// TODO: Now, join it all back together. Right now, just doing std::sort to have something working.
		// Need to do a more intelligible way to sort here.
		//std::sort(data_in.begin(), data_in.end());

		//MergeSort::Merge(data_in, data_in, <low>, <pivot - mid low/high>, <high>);

	}
	else
	{
		DataType * ret_val = new DataType();

		ret_val = BSort(true, data_in);
		data_in->swap(*ret_val);

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

