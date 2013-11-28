#include <iostream>
#include <vector> 
#include <iomanip>
using namespace std;
 

void merge(std::vector<size_t> &a, std::vector<size_t> &b, size_t low, size_t pivot, size_t high)
{
    size_t h,i,j,k;
    h=low;
    i=low;
    j=pivot+1;
 
    while((h<=pivot)&&(j<=high))
    {
        if(a[h]<=a[j])
        {
            b[i]=a[h];
            h++;
        }
        else
        {
            b[i]=a[j];
            j++;
        }
        i++;
    }
    if(h>pivot)
    {
        for(k=j; k<=high; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    else
    {
        for(k=h; k<=pivot; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    for(k=low; k<=high; k++) a[k]=b[k];
}

void mergesort(std::vector<size_t> &a, std::vector<size_t> &b, size_t low, size_t high)
{
    size_t pivot;
    if(low<high)
    {
        pivot=(low+high)/2;
        mergesort(a,b,low,pivot);
        mergesort(a,b,pivot+1,high);
        merge(a,b,low,pivot,high);
    }
}
 
int main(int argc, char* argv[])
{    
    // get length of array to generate from command line
    size_t length = (argc>1) ? atoi(argv[1]) : 10;

    // create the arrays
    std::vector<size_t> inputarray (length);
    std::vector<size_t> outputarray (length);

    // seed the random
    srand(time(NULL));

    // fill up input array with randoms, echo back unsorted input
    cout<<"input:\t[";
    for (size_t i = 0; i < length; i++) {
        inputarray[i] = rand()%100;
        cout<<setw(2)<< inputarray[i]<<" ";
    }
    cout<<"]\n";

    // run the mergesort
    mergesort(inputarray,outputarray,0,length-1);

    // display output array
    cout<<"output:\t[";
    for(size_t i=0; i<length; i++)
       cout<<setw(2)<<outputarray[i]<<" ";
    cout<<"]\n";
    
    // basic accuracy check
    size_t prev = 0;
    size_t unsorted = 0;
    for (size_t i = 0; i<length; i++){
        if (outputarray[i]<prev) unsorted = 1;
        prev = outputarray[i];
    }
    string o = (unsorted) ? "no" : "yes";
    cout<<"sorted:\t"<< o<<"\n";
    return 0;
}