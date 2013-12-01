#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include "BasicSort.hpp"
#include "BitonicSort.hpp"
// #include "QuickSort.hpp"
#include "MergeSort.hpp"

// Potential return values.
const int SUCCESS                   = 0;
const int ERROR_ON_COMMAND_LINE     = 1;
const int ERROR_UNHANDLED_EXCEPTION = 2;

int main(int argc, char * argv[])
{
	
	try {
		// Setup and configure the input parser.
		namespace po = boost::program_options;
		po::variables_map vm;

		// Add options here
		po::options_description desc("Options");
		desc.add_options()
			("help,h", "Prints out help information.")
			("size,s", po::value<size_t>()->default_value(10), "Number of elements to sort.")
			("threads,t", po::value<size_t>()->default_value(4), "Number of threads to use for sorting.");

		// Try to parse the input parameters.
		try {
			po::store(po::parse_command_line(argc, argv, desc),
				vm);

			// --help option
			if( vm.count("help") ) {
				std::cout << "Laser Patroll Sorting Benchmark Application" << std::endl <<
					desc << std::endl;
				return SUCCESS;
			}

			po::notify(vm);
		}
		catch(po::error& e) {
			std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
			std::cerr << desc << std::endl;
			return ERROR_ON_COMMAND_LINE;
		}

		// Input parameters were good. Now actually run the program.
		size_t num_threads = vm["threads"].as<size_t>();

		// The original data that should not get touched.
		SortCommon::DataType *	orig_data = new SortCommon::DataType();

		// Instaniate the three sort classes.
    //	QuickSort                   quick_sort;
    	MergeSort					merge_sort;
		BasicSort 		    basic_sort;
		BitonicSort 			bio_sort;

		// Use basic sort to build a vector of data.
		orig_data = SortCommon::NewData(vm["size"].as<size_t>());
                
	  //std::cout << "QuickSort Sort Time:         " << quick_sort.BenchmarkSort(orig_data, num_threads) << std::endl;
		std::cout << "Basic Sort Time:             " << basic_sort.BenchmarkSort(orig_data, num_threads) << std::endl;
		std::cout << "Bitonic Sort Time:           " << bio_sort.BenchmarkSort(orig_data, num_threads) << std::endl;
		std::cout << "MergeSort Sort Time:         " << merge_sort.BenchmarkSort(orig_data, num_threads) << std::endl;
                
        delete orig_data;
		return SUCCESS;

	}
	catch(std::exception& e) { 
		std::cerr << "Unhandled Exception reached the top of main: " 
			<< e.what() << ", application will now exit" << std::endl; 
		return ERROR_UNHANDLED_EXCEPTION; 
 	} 



}
