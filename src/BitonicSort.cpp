#include "BitonicSort.hpp"

BitonicSort::BitonicSort() {

}

BitonicSort::~BitonicSort() {

}

void BitonicSort::Sort(DataType &data_in)
{
	DataType retVal(BSort(true, data_in));
	data_in.swap(retVal);
}

BitonicSort::DataType BitonicSort::BSort(bool up, DataType &data_in)
{
	const size_t size_of_data_in = data_in.size();

	if(size_of_data_in <= 1)
	{
		return data_in;
	}
	else
	{
		DataType sv1(subVector(data_in, 0, size_of_data_in / 2));
		DataType sv2(subVector(data_in, size_of_data_in / 2, size_of_data_in - 1));

		DataType first(BSort(true, sv1));
		DataType second(BSort(false, sv2));
		DataType joined(first);
	 	joined.insert(first.end(), second.begin(), second.end());
	 	DataType retVal(BMerge(up, joined));
	 	return retVal;
	}
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