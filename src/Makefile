CXXFLAGS+=-Wall

.PHONY: all
all: MergeSort.o QuickSort.o BasicSort.o ThreadInfo.o SortCommon.o BitonicSort.o NumGen.o

MergeSort.o: MergeSort.cpp MergeSort.hpp
	$(CXX) $(CXXFLAGS) -c MergeSort.cpp

QuickSort.o: QuickSort.cpp QuickSort.hpp
	$(CXX) $(CXXFLAGS) -c QuickSort.cpp

BasicSort.o: BasicSort.cpp BasicSort.hpp
	$(CXX) $(CXXFLAGS) -c BasicSort.cpp

SortCommon.o: SortCommon.cpp SortCommon.hpp
	$(CXX) $(CXXFLAGS) -c SortCommon.cpp

BitonicSort.o: BitonicSort.hpp BitonicSort.cpp
	$(CXX) $(CXXFLAGS) -c BitonicSort.cpp 

ThreadInfo.o: ThreadInfo.hpp ThreadInfo.cpp
	$(CXX) $(CXXFLAGS) -c ThreadInfo.cpp


NumGen.o:
	$(CXX) $(CXXFLAGS) -c NumGen.cpp


clean:
	rm -rf *.o
	rm -rf *.gch
