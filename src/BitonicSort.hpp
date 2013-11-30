#ifndef BITONIC_SORT_H

#define BITONIC_SORT_H

#include <pthread.h>

#include "SortCommon.hpp"
#include "ThreadInfo.hpp"

#include <unistd.h>

class BitonicSort : public SortCommon {

public:
	BitonicSort();

	~BitonicSort();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void 		Sort(DataType &data_in, const threadCount num_threads);

private:
	//*! Runs Bitonic Sort by directly modifying passed argument.
	/*!
	  \param up
	  \param data_in the object getting sorted.
	  \param min the lowest index to start sort at.
	  \param max the highest index to start sort at.
	 */
	static DataType		BSort(bool up, DataType &data_in, size_t min, size_t max);

	//*! Runs Bitonic Sort using a ThreadInfo object passed in.
	/*!
	  \param thread_info the ThreadInfo object of data to sort.
	 */
	static DataType 	BSort(ThreadInfo* thread_info);

	//*! Runs Bitonic Sort directly sorting entire passed argument.
	/*!
	  \param up
	  \param data_in the object getting sorted.
	 */
	static DataType 	BSort(bool up, DataType &data_in);

	static void*		PBSort(void *);

	static DataType		BMerge(bool up, DataType &data_in);

	static void			BCompare(bool up, DataType &data_in);

	struct arg_struct {
		DataType data_in;
	};

};

#endif
