#ifndef SORT_COMMON_H

#define SORT_COMMON_H

#include <algorithm>
#include <complex>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <pthread.h>

#include <cstdlib>
#include <sys/time.h>
#include <sys/resource.h>

#include "NumGen.cpp"

/*! Basic sorting class providing the framework for benchmarking the sorting algorithms.
 */
class SortCommon {

public:

	typedef unsigned int ContainType;
	typedef std::vector<ContainType> DataType;

	typedef std::pair<size_t, size_t>		MinMaxPairsType;
	typedef std::vector<MinMaxPairsType> 	MinMaxVect;

	typedef size_t							threadCount;

	//*! Default constructor.
	/*!
	  This default constuctor sets the number of threads to a safe value (one)	 
        */
	SortCommon();

	//*! Default destructor.
	virtual ~SortCommon();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	virtual void		Sort(DataType * , const threadCount ) = 0;

	//*! Benchmarks the sort returning the number of seconds required to run.
	/*!
	  \param data_in the object getting sorted. Is passed in as constant.
	  \returns The number of seconds necessary to run sort. Returns negative value if sort failed.
	 */
	double		BenchmarkSort(const DataType *, const threadCount );

	//*! Creates new data object
	/*!
	  Creates a DataType object with size elments in a random order going from 0
	  up to size.
	  \param size the number of elements to get created in the ranom data object.
	  \returns A DataType object.
	 */
	static DataType	*	NewData(size_t size);

	//*! Confirms that a DataType object is sorted and returns true or false.
	/*!
	  \param data_in the DataType object to confirm it is sorted.
	  \retval true If DataType object is sorted.
	  \retval false If DataType object is not sorted.
	 */
	bool		CheckSort(const DataType * , const size_t);

	static void			PrintDataType(const DataType *, std::string, bool = false);

protected:
	static MinMaxVect	buildPairs(size_t num_threads, size_t min, size_t max);

	static MinMaxVect	buildPow2Pairs(size_t num_threads, size_t min, size_t max);

private:
	double 				GetTime();


};

#endif
