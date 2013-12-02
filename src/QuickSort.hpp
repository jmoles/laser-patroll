#ifndef QUICK_SORT_H

#define QUICK_SORT_H

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include <cstdlib>

#include "SortCommon.hpp"

/*! Basic sorting class providing the framework for benchmarking the sorting algorithms
 *  as well as the basic histogram sort.
 */
class QuickSort : public SortCommon {

public:

	QuickSort();

	~QuickSort();

	//*! Runs a basic quicksort, directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void  Sort(DataType * data_in, const threadCount num_threads);

	//*! Unique table key to identify items from this class.
	static const std::string kTableKey;

	//*! Unique pretty name to print information related to this class
	static const std::string kPrettyName;

private:
	//*! Recursive algorithm called by "Sort".
	/*!
	  \param data_in the object getting sorted
	  \param left leftmost index of the region to sort.
	  \param right rightmost index of the region to sort.
	 */
	void RecursiveSort(DataType * data_in, size_t left, size_t right);



};

#endif
