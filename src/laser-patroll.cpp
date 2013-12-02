#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "BasicSort.hpp"
#include "BitonicSort.hpp"
// #include "QuickSort.hpp"
#include "MergeSort.hpp"


#define THREAD_START		1
#define	SIZE_START			10
#define	DEFAULT_ELEMENTS	100
#define DEFAULT_THREADS		4
#define DEFAULT_GAP			10
#define DEFAULT_SAVE_FILE	"results.csv"

#define FIELD_WIDTH			10

#define PROG_NAME			"Laser Patroll Sorting Benchmark Application"
#define VERSION_STRING		"Version: Alpha"

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
		bool sweep;

		// Add options here
		po::options_description generic("Program Options");
		generic.add_options()
			("help,h", "Prints out help information.")
			("version,v", "Prints out version information.");

		po::options_description configuration("Configuration Options");
		configuration.add_options()
			("size,s", po::value<size_t>()->default_value(DEFAULT_ELEMENTS), 
				"Number of elements to sort.")
			("threads,t", po::value<size_t>()->default_value(DEFAULT_THREADS), 
				"Number of threads to use for sorting.")
			("sweep,z", po::value(&sweep)->zero_tokens(), 
				"Runs sweep mode. Increment threads by 1 to <threads> and "
				"multiple size from 10 by <gap>.");

		po::options_description sweep_po("Sweep Options (Used only if <sweep> is set)");
		sweep_po.add_options()
			("gap,g", po::value<size_t>()->default_value(DEFAULT_GAP),
				"Specifies the multiple factor to multiply vector size by"
				" in sweep mode.")
			("init_size,w", 
				po::value<size_t>()->default_value(SIZE_START),
				"The initial data size to use in sweep mode.");

		po::options_description cmd_line_options;
		cmd_line_options.add(generic).add(configuration).add(sweep_po);

		// Try to parse the input parameters.
		try {
			po::store(po::parse_command_line(argc, argv, cmd_line_options),
				vm);

			// --help option
			if( vm.count("help") ) {
				std::cout << std::endl << PROG_NAME << std::endl << 
					VERSION_STRING << std::endl <<
					cmd_line_options << std::endl;
				return SUCCESS;
			}

			// --version options
			if( vm.count("version") ) {
				std::cout << std::endl << PROG_NAME << std::endl <<
					VERSION_STRING << std::endl;
			}

			po::notify(vm);
		}
		catch(po::error& e) {
			std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
			std::cerr << cmd_line_options << std::endl;
			return ERROR_ON_COMMAND_LINE;
		}

		// Input parameters were good. Now actually run the program.

		// First, get the parameters from the argument parser.
		const size_t num_threads = vm["threads"].as<size_t>();
		const size_t max_data_size	= vm["size"].as<size_t>();
		const size_t desired_gap	= vm["gap"].as<size_t>();

		// Variables used for loops below.
		size_t thread_init, size_init;

		if(sweep) {
			thread_init = THREAD_START;
			size_init	= vm["init_size"].as<size_t>();
		} else {
			thread_init	= num_threads;
			size_init	= max_data_size;
		}

		// Instantiate the sort classes.
		//QuickSort					quick_sort;
		MergeSort					merge_sort;
		BasicSort					basic_sort;
		BitonicSort					bio_sort;

		// User has requested that data is swept.
		for(size_t curr_thread = thread_init; curr_thread <= num_threads; curr_thread++)
		{
			for(size_t curr_size = size_init; curr_size <= max_data_size; curr_size *= desired_gap)
			{
				std::cout << "Threads:             " << 
					std::setw(FIELD_WIDTH) << curr_thread << std::endl;
				std::cout << "Data Size:           " << 
					std::setw(FIELD_WIDTH) <<  curr_size << std::endl;

				SortCommon::DataType const * input_data = new SortCommon::DataType();
				input_data = SortCommon::NewData(curr_size);
				std::cout << "Basic Sort Time:     " << std::fixed  <<
					std::setw(FIELD_WIDTH) <<
					basic_sort.BenchmarkSort(input_data, curr_thread) << std::endl;
				std::cout << "Bitonic Sort Time:   " << std::fixed <<
					std::setw(FIELD_WIDTH) <<
					bio_sort.BenchmarkSort(input_data, curr_thread) << std::endl;
				std::cout << "MergeSort Sort Time: " << std::fixed <<
					std::setw(FIELD_WIDTH) <<
					merge_sort.BenchmarkSort(input_data, curr_thread) << std::endl;

				std::cout << std::endl;

				delete input_data;
			}
		}
		return SUCCESS;

	}
	catch(std::exception& e) { 
		std::cerr << "Unhandled Exception reached the top of main: " 
			<< e.what() << ", application will now exit" << std::endl; 
		return ERROR_UNHANDLED_EXCEPTION; 
 	} 



}
