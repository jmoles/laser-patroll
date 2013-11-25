#ifndef BITONIC_SORT_H

#define BITONIC_SORT_H

#include "SortCommon.hpp"

class BitonicSort : public SortCommon {

public:
	BitonicSort();

	~BitonicSort();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void 		Sort(DataType &data_in);

private:
	DataType	BSort(bool up, DataType &data_in);

	DataType	BMerge(bool up, DataType &data_in);

	void		BCompare(bool up, DataType &data_in);

};

#endif
