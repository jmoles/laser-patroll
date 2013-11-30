UNAME:=$(shell uname -s)

ifeq ($(UNAME), Darwin)
	INC=-I/usr/local/include/ 
	LDFLAGS=-L/usr/local/Cellar/boost/1.54.0/lib
else
	INC= 
endif

CXXFLAGS=-Wall -g
LDLIBS=-lboost_program_options -lpthread

OBJS=src/BasicSort.o src/ThreadInfo.o src/BitonicSort.o src/NumGen.o src/SortCommon.o src/QuickSort.o src/MergeSort.o
SOURCES=$(wildcard src/*.cpp)
HEADERS=$(wildcard src/*.hpp)
DOC=doc/report.tex

.PHONY: all
all: laser-patroll doc/report.pdf 

doc/report.pdf: $(DOC)
	$(MAKE) -C doc

laser-patroll: src/laser-patroll.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $(LDFLAGS) $(LDLIBS) -o laser-patroll src/laser-patroll.cpp $(OBJS)

$(OBJS): $(SOURCES) $(HEADERS)
	$(MAKE) -C src CXXFLAGS='$(CXXFLAGS)' CXX='$(CXX)' INC='$(INC)' LDFLAGS='$(LDFLAGS)' LDLIBS='$(LDLIBS)' all

clean:
	rm -rf laser-patroll
	$(MAKE) -C doc $@
	$(MAKE) -C src $@
