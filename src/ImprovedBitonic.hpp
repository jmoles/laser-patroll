#ifndef IMPROVED_BITONIC_H

#define IMPROVED_BITONIC_H

#include "SortCommon.hpp"

class ImprovedBitonic : public SortCommon {

public:

	typedef std::vector<size_t> KeyType;

	ImprovedBitonic();

	~ImprovedBitonic();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void 		Sort(DataType &data_in);

private:
	DataType	IBRSort(bool up, DataType &data_in);

	DataType	IBRMerge(bool up, DataType &data_in);

	void		IBRCompare(bool up, DataType &data_in);

};

#endif
