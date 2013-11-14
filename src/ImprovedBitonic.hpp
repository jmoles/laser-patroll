#ifndef IMPROVED_BIOTONIC_H

#define IMPROVED_BIOTONIC_H

#include "SortCommon.hpp"

class ImprovedBiotonic : public SortCommon {

public:
	ImprovedBiotonic();

	~ImprovedBiotonic();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void 		Sort(DataType &data_in);

private:

};

#endif
