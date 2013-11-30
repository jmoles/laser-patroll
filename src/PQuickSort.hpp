#ifndef QUICK_SORT_H

#define QUICK_SORT_H

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

#include "SortCommon.hpp"

/*! Basic sorting class providing the framework for benchmarking the sorting algorithms
 *  as well as the basic histogram sort.
 */
class PQuickSort : public SortCommon {

public:

	PQuickSort();

	~PQuickSort();

	//*! Runs a basic quicksort, directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void  Sort(DataType &data_in, const unsigned int num_threads, size_t left);

private:
	//*! Recursive algorithm called by "Sort".
	/*!
	  \param data_in the object getting sorted
	  \param left leftmost index of the region to sort.
	  \param right rightmost index of the region to sort.
	 */
	void QRSort(DataType &data_in, DataType &dst, const unsigned int num_threads, size_t left, size_t right);
      void * Thread_Work(void * args);

};

#endif
