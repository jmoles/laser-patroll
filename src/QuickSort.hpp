#ifndef QUICK_SORT_H

#define QUICK_SORT_H

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
class QuickSort : public SortCommon {

public:

	QuickSort();

	~QuickSort();

	//*! Runs a basic quicksort, directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
          \param left leftmost index of region to sort (0 on first call)
          \param right rightmost index of region to sort (ARRAYSIZE on first call)
	 */
	void  Sort(DataType &data_in, int left, int right);

private:



};

#endif
