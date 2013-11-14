CXXFLAGS+=-Wall 

.PHONY: all
all: QuickSort.o BasicSort.o SortCommon.o BiotonicSort.o ImprovedBiotonic.o NumGen.o

QuickSort.o: QuickSort.cpp QuickSort.hpp
	$(CXX) $(CXXFLAGS) -c QuickSort.cpp

BasicSort.o: BasicSort.cpp BasicSort.hpp
	$(CXX) $(CXXFLAGS) -c BasicSort.cpp

SortCommon.o: SortCommon.cpp SortCommon.hpp
	$(CXX) $(CXXFLAGS) -c SortCommon.cpp

BiotonicSort.o: BiotonicSort.hpp BiotonicSort.cpp
	$(CXX) $(CXXFLAGS) -c BiotonicSort.cpp 

ImprovedBiotonic.o: ImprovedBiotonic.hpp ImprovedBiotonic.cpp
	$(CXX) $(CXXFLAGS) -c ImprovedBiotonic.cpp

NumGen.o:
	$(CXX) $(CXXFLAGS) -c NumGen.cpp


clean:
	rm -rf *.o
	rm -rf *.gch
