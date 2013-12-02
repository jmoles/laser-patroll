#ifndef BITONIC_SORT_H

#define BITONIC_SORT_H

#include <cmath>
#include <pthread.h>

#include "SortCommon.hpp"
#include "ThreadInfo.hpp"
#include "MergeSort.hpp"

#include <unistd.h>

class BitonicSort : public SortCommon {

public:
	BitonicSort();

	~BitonicSort();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void 		Sort(DataType *, const threadCount num_threads);

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
	static DataType	*	BSort(bool up, DataType *, size_t min, size_t max);

	//*! Runs Bitonic Sort using a ThreadInfo object passed in.
	/*!
	  \param thread_info the ThreadInfo object of data to sort.
	 */
	static DataType *	BSort(ThreadInfo* thread_info);

	//*! Runs Bitonic Sort directly sorting entire passed argument.
	/*!
	  \param up
	  \param data_in the object getting sorted.
	 */
	static DataType *	BSort(bool up, DataType *);

	static void*		PBSort(void *);

	static DataType	*	BMerge(bool up, DataType *);

	static void			BCompare(bool up, DataType *);

	//*! Pads the end of a vector to the requested size.
	/*!
	  \param data_in pointer to the vector to get padded.
	  \param new_length desired size of the vector for padding.
	  \returns The number of elements that had to get added to meet the requested size.
	 */
	static size_t 		PadVector(DataType * const, size_t);

	//*! Removes the padding of a vector often applied by PadVector.
	/*!
	  \param data_in pointer to the vector to remove padding.
	  \param remove_count number of elements to remove from the front of the vector.
	 */
	static void 		UnpadVector(DataType * const, size_t);

	static void			Merge(DataType * const src, DataType * dst, size_t low, size_t pivot, size_t high);

};

#endif
