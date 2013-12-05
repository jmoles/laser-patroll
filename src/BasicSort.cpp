#include "BasicSort.hpp"

const std::string BasicSort::kTableKey    = "basic";
const std::string BasicSort::kPrettyName  = "Basic Sort";

BasicSort::BasicSort()
{

}

BasicSort::~BasicSort()
{

}


void BasicSort::Sort(DataType *data_in, const threadCount num_threads)
{
    std::sort(data_in->begin(), data_in->end());
}
