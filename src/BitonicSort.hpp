#ifndef BIOTONIC_SORT_H

#define BIOTONIC_SORT_H

#include "SortCommon.hpp"

class BiotonicSort : public SortCommon {

public:
	BiotonicSort();

	~BiotonicSort();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void 		Sort(DataType &data_in);

private:

};

#endif
