CXXFLAGS+=-Wall

.PHONY: all
all: MergeSort.o QuickSort.o BasicSort.o ThreadInfo.o SortCommon.o BitonicSort.o NumGen.o CSVTools.o ThreadInfo.o

MergeSort.o: MergeSort.hpp
QuickSort.o: QuickSort.hpp
BasicSort.o: BasicSort.hpp
SortCommon.o: SortCommon.hpp
BitonicSort.o: BitonicSort.hpp
ThreadInfo.o: ThreadInfo.hpp
CSVTools.o: CSVTools.hpp

clean:
	rm -rf *.o
	rm -rf *.gch
