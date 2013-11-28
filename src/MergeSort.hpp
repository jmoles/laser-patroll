#ifndef MERGE_SORT_H

#define MERGE_SORT_H

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include <cstdlib>

#include "SortCommon.hpp"
#include "ThreadInfo.hpp"

/*! Basic sorting class providing the framework for benchmarking the sorting algorithms
 *  as well as the basic histogram sort.
 */


class MergeSort : public SortCommon {

public:

	MergeSort();

	~MergeSort();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	  \param num_threads the number of threads to do the sort on.
	 */
	void		Sort(DataType &data_in, const TheadCount num_threads);

private:
        struct thread_args { thread_args(); DataType &data_in; DataType &dst; size_t threads_remaining; size_t low; size_t high; };
        static void*  Thread_MSort(void*);
        static void  Merge(DataType &src, DataType &dst, size_t low, size_t pivot, size_t high);
        static void  MSort(DataType &data_in, DataType &dst, const size_t threads_remaining, size_t low, size_t high);
};

#endif
