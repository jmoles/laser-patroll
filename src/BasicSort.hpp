#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include <cstdlib>

#include "NumGen.cpp"

//#include <boost/mpi.hpp>

/*! Basic sorting class providing the framework for benchmarking the sorting algorithms
 *  as well as the basic histogram sort.
 */
class BasicSort {

public:

	typedef unsigned int ContainType;
	typedef std::vector<ContainType> DataType;

	//*! Default constructor.
	/*!
	  This constuctor is generally the one used and prepares the necessary initial values
	  for the class.
	 */
	BasicSort();

	//*! Runs std::sort directly modifying the passed argument.
	/*!
	  \param data_in the object getting sorted.
	 */
	void 		Sort(DataType &data_in);

	//*! Benchmarks the sort returning the number of seconds required to run.
	/*!
	  \param data_in the object getting sorted. Is passed in as constant.
	  \returns The number of seconds necessary to run sort. Returns negative value if sort failed.
	 */
	double		BenchmarkSort(const DataType &data_in);

	//*! Creates new data object
	/*!
	  Creates a DataType object with size elments in a random order going from 0
	  up to size.
	  \param size the number of elements to get created in the ranom data object.
	  \returns A DataType object.
	 */
	DataType	NewData(size_t size);

	//*! Confirms that a DataType object is sorted and returns true or false.
	/*!
	  \param data_in the DataType object to confirm it is sorted.
	  \retval true If DataType object is sorted.
	  \retval false If DataType object is not sorted.
	 */
	bool		CheckSort(const DataType &data_in);


private:



};
