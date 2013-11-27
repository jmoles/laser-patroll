#include "ThreadInfo.hpp"

ThreadInfo::ThreadInfo() : min_(0), max_(1), data_(0)
{


}

ThreadInfo::ThreadInfo(size_t min, size_t max, DataType * data) : min_(min), max_(max), data_(data)
{

}

ThreadInfo::~ThreadInfo()
{

}

void ThreadInfo::PrintInfo()
{
	std::cout << "Minimum: " << min_ << std::endl;
	std::cout << "Maximum: " << max_ << std::endl;
}
