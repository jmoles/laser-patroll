#ifndef BASIC_SORT_H

#define BASIC_SORT_H

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include <cstdlib>

//#include <boost/mpi.hpp>

#include "SortCommon.hpp"

/*! Basic sorting class providing the framework for benchmarking the sorting algorithms
 *  as well as the basic histogram sort.
 */
class BasicSort : public SortCommon {

public:

	BasicSort();

	~BasicSort();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void		Sort(DataType * , const threadCount );

	//*! Unique table key to identify items from this class.
	static const std::string kTableKey;

	//*! Unique pretty name to print information related to this class
	static const std::string kPrettyName;

private:



};

#endif
