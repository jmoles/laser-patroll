#include <algorithm>
#include <iostream>
#include <vector>

//#include <boost/mpi.hpp>


class BasicSort {


public:

	typedef unsigned int ContainType;
	typedef std::vector<ContainType> DataType;


	BasicSort();

	void 		Sort(DataType &);
	DataType	NewData(size_t);
	bool		CheckSort(const DataType &);


private:
	unsigned int	nextNumVal;



};
