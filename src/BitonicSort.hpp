#ifndef BITONIC_SORT_H

#define BITONIC_SORT_H

#include <cmath>
#include <pthread.h>

#include "SortCommon.hpp"
#include "ThreadInfo.hpp"
#include "MergeSort.hpp"

#include <unistd.h>

class BitonicSort : public SortCommon
{

public:
    BitonicSort();

    ~BitonicSort();

    //*! Runs std::sort directly modifying the passed argument.
    /*!
      \param data_in the object getting sorted.
     */
    void        Sort(DataType *, const threadCount num_threads);

    //*! Unique table key to identify items from this class.
    static const std::string kTableKey;

    //*! Unique pretty name to print information related to this class
    static const std::string kPrettyName;

private:
    //*! Runs Bitonic Sort by directly modifying passed argument.
    /*!
      \param up
      \param data_in the object getting sorted.
      \param min the lowest index to start sort at.
      \param max the highest index to start sort at.
     */
    static void         BSort(bool up, DataType *, size_t min, size_t max);

    //*! Runs Bitonic Sort using a ThreadInfo object passed in.
    /*!
      \param thread_info the ThreadInfo object of data to sort.
     */
    static void         BSort(ThreadInfo *thread_info);

    //*! Runs Bitonic Sort directly sorting entire passed argument.
    /*!
      \param up
      \param data_in the object getting sorted.
     */
    static void         BSort(bool up, DataType *);

    static void        *PBSort(void *);

    static void         BMerge(bool up, DataType *data_in, size_t min, size_t max);

    static void         BCompare(bool up, DataType *, size_t min, size_t max);





};

#endif
