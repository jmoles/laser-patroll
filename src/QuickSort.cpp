#include "QuickSort.hpp"

const std::string QuickSort::kTableKey    = "quick";
const std::string QuickSort::kPrettyName  = "Quick Sort";

QuickSort::QuickSort() {

}

QuickSort::~QuickSort() {

}


void QuickSort::Sort(DataType * data_in, const threadCount num_threads ) {

  if(num_threads > 1)
  {
    // Build the pairs of data to split up amongst all the threads.
    MinMaxVect min_max_pairs;
    min_max_pairs = buildPairs(num_threads, 0, data_in->size() - 1);

    // Pad the vector to be the correct length. It must be a power of two.
    size_t pad_len = 0;

    // Vector to hold all of the threads that are running.
    std::vector<pthread_t> threads;

    // Prepare and actually run the threads for the sort. 
    for(MinMaxVect::iterator it = min_max_pairs.begin(); it != min_max_pairs.end(); it++)
    {
      pthread_t   curr_thread;
      
      ThreadInfo * curr_thread_info = new ThreadInfo(it->first, it->second, data_in);

      pthread_create(&curr_thread, NULL, &PQSort, curr_thread_info);
      threads.push_back(curr_thread);
    }

    for(unsigned int i = 0; i < threads.size(); i++)
    {
      // Join each of the threads.
      pthread_join(threads[i], NULL);
    }

    // Now, use the Merge function in MergeSort to join all of the vectors together.
    unsigned int max_level  = ((unsigned int) std::ceil(log2(min_max_pairs.size())));

    for(size_t i = 0; i < max_level; i++)
    {
            for(MinMaxVect::iterator it = min_max_pairs.begin(); it != min_max_pairs.end(); it++)
            {
                size_t low_i, pivot_i, high_i;

          MinMaxVect::iterator low         = it;

          size_t inc;
          if(i == 0)
            inc = 1;
          else
            inc = ( ( (size_t) pow(2,i + 1) ) - 1 );

          for (size_t j = 0; j < inc; j++)
          {
            it++;
            if(it == min_max_pairs.end())
            {
              // Need to add a "phantom" element to the end that is just zeros and add padding.
              // Then just remove the padding later.
              it--;

              // Build a min/max pair to add that would be the next in the list.
              MinMaxPairsType temp_pair(it->second + 1, it->second + (it->second - it->first) + 1);
              min_max_pairs.insert(min_max_pairs.end(), temp_pair);

              // Determine the number of elements to add and actually add it.
              size_t elem_to_add = (it->second - it->first) + 1;
              pad_len += PadVector(data_in, data_in->size() + elem_to_add);

              // Reset the iterator to the element we just added.
              it = min_max_pairs.end() - 1;
            }
          }

          MinMaxVect::iterator high = it;

          // Set all of the indexes.
          low_i = low->first;
          high_i  = high->second;
          pivot_i = (low->first + high->second + 1) / 2;

          //std::cout << "Sort on [" << low_i << ", " << pivot_i << ", " << high_i << "]" << std::endl;
          Merge(data_in, data_in, low_i, pivot_i, high_i);
            }
    }

    UnpadVector(data_in, pad_len);

  }
  else
  {
    // Actually perform the sort.
    QSort(data_in, 0, data_in->size() - 1);
  }


  DataType * dst = new DataType(data_in->size(),0);
  QSort(data_in, 0, data_in->size() - 1); 
  free(dst);
}

void* QuickSort::PQSort(void * arguments)
{
  ThreadInfo* thread_info = (ThreadInfo*) arguments;
  QSort(thread_info->data_, thread_info->min_, thread_info->max_);
  delete thread_info;
  pthread_exit((void *) NULL);
}

void QuickSort::QSort(DataType * data_in, size_t left, size_t right) {
  size_t i = left, j = right;
  ContainType tmp;
  ContainType pivot_point = (left + right)/2;

  // If there is only one element, simply return.
  if(left == right)
    return;

  while (i <= j) {
    while (data_in->at(i) < data_in->at(pivot_point))
    {
      i = CheckIncBound(right, i, left);
    }
    while (data_in->at(j) > data_in->at(pivot_point))
    {
      j = CheckDecBound(right, j, left);
    }
    if (i <= j) {
      tmp = data_in->at(i);
      (*data_in)[i] = data_in->at(j);
      (*data_in)[j] = tmp;
      i = CheckIncBound(right, i, left);
      j = CheckDecBound(right, j, left);
    }
  }
  if (left < j)
    QSort(data_in, left, j);
  if (i < right)
    QSort(data_in, i, right);
}

  size_t QuickSort::CheckIncBound(size_t max, size_t i, size_t min){
    if (i >= max)
    {
      return min; 
    }
    else
    {
      return ++i;
    }
  }

  size_t QuickSort::CheckDecBound(size_t max, size_t j, size_t min){
    if (j <= min)
    {
      return  max;
    }
    else
    {
      return --j;
    }
  }
