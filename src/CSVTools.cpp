#include "CSVTools.hpp"

CSVTools::CSVTools() : file_name_(DEFAULT_FILE_NAME)
{
	header_wrote_ = false;
}

CSVTools::CSVTools(std::string file_name) : file_name_(file_name)
{
	CSVTools();
}

CSVTools::~CSVTools()
{
	CloseFile();
}

void CSVTools::WriteResult(std::string name, size_t threads, size_t size, double runtime)
{
	OpenFile();

	os_ << std::fixed <<  	name 	<< "," << 
							threads << "," <<
							size 	<< "," <<
							runtime << std::endl;

	CloseFile();
}

void CSVTools::OpenFile()
{
	if(!os_.is_open())
		os_.open(file_name_.c_str(), DEFAULT_OUTPUT_MODE);

	if(!header_wrote_ && os_.good())
	{
		os_ << "Algorithm,Threads,Size,Time" << std::endl;
		header_wrote_ = true;
	}

}

void CSVTools::CloseFile()
{
	if(os_.is_open())
		os_.close();
}
