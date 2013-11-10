#include <iostream>
#include <vector>

#include "BasicSort.hpp"

int main(int argc, char * argv[])
{
	BasicSort::DataType orig_data;

	// Instaniate a basic sort class.
	BasicSort basic_sort;

	// Use basic sort to build a vector of data.
	orig_data = basic_sort.NewData(10);

	// Print out all of the values
	for(BasicSort::DataType::iterator it = orig_data.begin(); 
		it != orig_data.end();
		++it) {
			std::cout << *it << std::endl;

	}

	// Print if sorted (should not be at this point)
	if(basic_sort.CheckSort(orig_data))
		std::cout << "Vector is showing sorted, but is not!" << std::endl;
	else
		std::cout << "Vector is not showing sorted!" << std::endl;

	basic_sort.Sort(orig_data);

	// Should be sorted now.
	if(basic_sort.CheckSort(orig_data))
		std::cout << "Vector is now sorted! All is good!" << std::endl;
	else
		std::cout << "Vector is NOT sorted and SHOULD be!" << std::endl;

	return 0;
}
