#include "ThreadInfo.hpp"

ThreadInfo::ThreadInfo() : min_(0), max_(1), data_(0), dst_(0), remain_threads_(1)
{


}

ThreadInfo::ThreadInfo(size_t min, size_t max, DataType * data) :
	min_(min), max_(max), data_(data), dst_(0), remain_threads_(1)
{

}

ThreadInfo::ThreadInfo(size_t min, size_t max, DataType * data,
	DataType * dst, unsigned int remain_threads) :
		min_(min), max_(max), data_(data) , dst_(dst),
			remain_threads_(remain_threads)
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

