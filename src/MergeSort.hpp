#ifndef MERGE_SORT_H

#define MERGE_SORT_H

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

typedef struct { size_t threads_remaining; size_t low; size_t high; } thread_args;

class MergeSort : public SortCommon {

public:

	MergeSort();

	~MergeSort();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void  Sort(DataType &data_in);

private:
        DataType * src;
        DataType dst;
        void  *Thread_MSort(void * args);
        void  Merge(size_t low, size_t pivot, size_t high);
        void  MSort(size_t threads_remaining, size_t low, size_t high);
};

#endif
