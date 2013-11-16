#include "ImprovedBitonic.hpp"

ImprovedBitonic::ImprovedBitonic()
{

}

ImprovedBitonic::~ImprovedBitonic()
{

}

void ImprovedBitonic::Sort(DataType &data_in)
{
	DataType retVal(IBRSort(true, data_in));
	data_in.swap(retVal);
}

ImprovedBitonic::DataType ImprovedBitonic::IBRSort(bool up, DataType &data_in)
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

		DataType first(IBRSort(true, sv1));
		DataType second(IBRSort(false, sv2));
		DataType joined(first);
	 	joined.insert(first.end(), second.begin(), second.end());
	 	DataType retVal(IBRMerge(up, joined));
	 	return retVal;
	}
}

ImprovedBitonic::DataType ImprovedBitonic::IBRMerge(bool up, DataType &data_in)
{
	const size_t size_of_data_in = data_in.size();

	if(size_of_data_in == 1)
	{
		return data_in;
	}
	else
	{
		IBRCompare(up, data_in);

		DataType sv1(subVector(data_in, 0, size_of_data_in / 2));
		DataType sv2(subVector(data_in, size_of_data_in / 2, size_of_data_in - 1));

		DataType first(IBRMerge(up, sv1));
		DataType second(IBRMerge(up, sv2));

		DataType retVal(first);
		retVal.insert(first.end(), second.begin(), second.end());
		return retVal;
	}
}

void ImprovedBitonic::IBRCompare(bool up, DataType &data_in)
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
