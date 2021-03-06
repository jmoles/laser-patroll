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


class MergeSort : public SortCommon
{

public:

    MergeSort();

    ~MergeSort();

    //*! Runs std::sort directly modifying the passed argument.
    /*!
      \param data_in the object getting sorted.
      \param num_threads the number of threads to do the sort on.
     */
    void        Sort(DataType *data_in, const threadCount num_threads);

    static void  Merge(DataType *src, DataType *dst, size_t low, size_t pivot, size_t high);

    //*! Unique table key to identify items from this class.
    static const std::string kTableKey;

    //*! Unique pretty name to print information related to this class
    static const std::string kPrettyName;

private:
    static void  *Thread_MSort(void *);

    static void  MSort(DataType *data_in, DataType *dst, const unsigned int threads_remaining, size_t low, size_t high);
};

#endif
