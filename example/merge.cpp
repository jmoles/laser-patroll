#include <iostream>
#include <vector> 
#include <iomanip>
using namespace std;
 

void merge(std::vector<int> &a, std::vector<int> &b, int low, int pivot, int high)
{
    int h,i,j,k;
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

void mergesort(std::vector<int> &a, std::vector<int> &b, int low, int high)
{
    int pivot;
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
    int length = (argc>1) ? atoi(argv[1]) : 10;

    // create the arrays
    std::vector<int> inputarray (length);
    std::vector<int> outputarray (length);

    // seed the random
    srand(time(NULL));

    // fill up input array with randoms, echo back unsorted input
    cout<<"input:\t[";
    for (int i = 0; i < length; i++) {
        inputarray[i] = rand()%100;
        cout<<setw(2)<< inputarray[i]<<" ";
    }
    cout<<"]\n";

    // run the mergesort
    mergesort(inputarray,outputarray,0,length-1);

    // display output array
    cout<<"output:\t[";
    for(int i=0; i<length; i++)
       cout<<setw(2)<<outputarray[i]<<" ";
    cout<<"]\n";
    
    // basic accuracy check
    int prev = 0;
    int unsorted = 0;
    for (int i = 0; i<length; i++){
        if (outputarray[i]<prev) unsorted = 1;
        prev = outputarray[i];
    }
    string o = (unsorted) ? "no" : "yes";
    cout<<"sorted:\t"<< o<<"\n";
    return 0;
}