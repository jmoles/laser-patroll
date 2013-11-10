#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include "BasicSort.hpp"

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
		BasicSort::DataType orig_data;

		// Instaniate a basic sort class.
		BasicSort basic_sort;

		// Use basic sort to build a vector of data.
		orig_data = basic_sort.NewData(vm["size"].as<size_t>());

		std::cout << "Basic Sort Time: " << basic_sort.BenchmarkSort(orig_data) << std::endl;

		return SUCCESS;

	}
	catch(std::exception& e) { 
		std::cerr << "Unhandled Exception reached the top of main: " 
			<< e.what() << ", application will now exit" << std::endl; 
		return ERROR_UNHANDLED_EXCEPTION; 
 	} 



}
