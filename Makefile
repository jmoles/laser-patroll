UNAME:=$(shell uname -s)

ifeq ($(UNAME), Darwin)
	INC=-I/usr/local/include/ 
	LDFLAGS=-L/usr/local/Cellar/boost/1.54.0/lib
else
	INC= 
endif

CXXFLAGS=-Wall
LDLIBS=-lboost_program_options -lpthread

CXX_DEBUG_FLAGS=-g3 -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3

OBJS=src/BasicSort.o src/ThreadInfo.o src/BitonicSort.o src/NumGen.o src/SortCommon.o src/QuickSort.o src/MergeSort.o src/CSVTools.o
SOURCES=$(wildcard src/*.cpp)
HEADERS=$(wildcard src/*.hpp)
DOC=doc/report.tex

.PHONY: release
release: CXXFLAGS+=$(CXX_RELEASE_FLAGS)
release: laser-patroll

.PHONY: debug
debug: CXXFLAGS+=$(CXX_DEBUG_FLAGS)
debug: laser-patroll

doc/report.pdf: $(DOC)
	$(MAKE) -C doc

laser-patroll: src/laser-patroll.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $(LDFLAGS) $(LDLIBS) -o $@ src/laser-patroll.cpp $(OBJS)

$(OBJS): $(SOURCES) $(HEADERS)
	$(MAKE) -C src CXXFLAGS='$(CXXFLAGS)' CXX='$(CXX)' INC='$(INC)' LDFLAGS='$(LDFLAGS)' LDLIBS='$(LDLIBS)' all

clean:
	rm -rf laser-patroll
	$(MAKE) -C doc $@
	$(MAKE) -C src $@
