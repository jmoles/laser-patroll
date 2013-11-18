#include <iostream>
#include <vector>

using namespace std;

typedef struct Region {
  int min;
  int max;
};
 
int main(int argc, char* argv[])
{
    int length, threads;
    
    if (argc != 3){
      threads = 10;
      length = 1000;  
    }
    else {
      length = atoi(argv[1]);
      threads = atoi(argv[2]);  
    }

    cout << "array length:\t" << length << "\n";
    cout << "workers:\t" << threads << "\n";
   
    // catch the dumb case
    if (length <= 1){
      cout << "u dumb\n";
      return 0;
    }

    // only allow length/2 threads
    if (threads > length/2)
    {
      cout << "\nwill only use " << length/2 << " threads !!\n";
      threads = length/2;
    }

    // determine and echo step size (thread_domain length)
    int step = length/threads;
    cout << "step length:\t" << step << "\n";
    
    // track thread_domains that all threads are responsible for
    Region * thread_domain = new Region[threads];

    for (int i = 0; i<threads; i++){
      thread_domain[i].min = i*step;
      thread_domain[i].max = (i == threads-1) ? length-1 : ((i+1)*step)-1;
      cout << "thread "<< i << ":\t" << thread_domain[i].min << " to " << thread_domain[i].max << "\n";
     }


}
