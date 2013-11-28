#ifndef THREAD_INFO_H

#define THREAD_INFO_H

#include <iostream>
#include <vector>

#include "SortCommon.hpp"

/*! Basic sorting class providing the framework for benchmarking the sorting algorithms.
 */
class ThreadInfo {

public:

	typedef unsigned int ContainType;
	typedef std::vector<ContainType> DataType;

	//*! Default constructor.
	/*!
	  This default constuctor sets the number of threads to a safe value (one)	 
        */
	ThreadInfo();

	ThreadInfo(size_t min, size_t max, DataType * data);

	ThreadInfo(size_t min, size_t max, DataType * data,
		DataType * dst, unsigned int remain_threads);

	//*! Default destructor.
	virtual ~ThreadInfo();

	//*! Print outs statistics about the contained data.
	void PrintInfo();

	const size_t 			min_;
	const size_t 			max_;
	DataType * const		data_;
	DataType * const		dst_;
	const unsigned int		remain_threads_;


protected:

private:



};

#endif
