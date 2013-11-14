#ifndef IMPROVED_BITONIC_H

#define IMPROVED_BITONIC_H

#include "SortCommon.hpp"

class ImprovedBitonic : public SortCommon {

public:
	ImprovedBitonic();

	~ImprovedBitonic();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void 		Sort(DataType &data_in);

private:

};

#endif
