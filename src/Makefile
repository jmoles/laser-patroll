CXXFLAGS+=-Wall 

.PHONY: all
all: QuickSort.o BasicSort.o SortCommon.o BitonicSort.o ImprovedBitonic.o NumGen.o

QuickSort.o: QuickSort.cpp QuickSort.hpp
	$(CXX) $(CXXFLAGS) -c QuickSort.cpp

BasicSort.o: BasicSort.cpp BasicSort.hpp
	$(CXX) $(CXXFLAGS) -c BasicSort.cpp

SortCommon.o: SortCommon.cpp SortCommon.hpp
	$(CXX) $(CXXFLAGS) -c SortCommon.cpp

BitonicSort.o: BitonicSort.hpp BitonicSort.cpp
	$(CXX) $(CXXFLAGS) -c BitonicSort.cpp 

ImprovedBitonic.o: ImprovedBitonic.hpp ImprovedBitonic.cpp
	$(CXX) $(CXXFLAGS) -c ImprovedBitonic.cpp

NumGen.o:
	$(CXX) $(CXXFLAGS) -c NumGen.cpp


clean:
	rm -rf *.o
	rm -rf *.gch
