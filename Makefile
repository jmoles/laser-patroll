UNAME:=$(shell uname -s)

ifeq ($(UNAME), Darwin)
	INC=-I/usr/local/include/ 
	LDFLAGS=-L/usr/local/Cellar/boost/1.54.0/lib
else
	INC= 
endif

CXXFLAGS+=-Wall 
LDLIBS = -lboost_program_options

OBJS=src/BasicSort.o src/BiotonicSort.o src/ImprovedBiotonic.o src/NumGen.o src/SortCommon.o src/QuickSort.o
SOURCES=$(wildcard src/*.cpp)
HEADERS=$(wildcard src/*.hpp)
DOC=doc/report.tex

.PHONY: all
all: doc/report.pdf laser-patroll

doc/report.pdf: $(DOC)
	$(MAKE) -C doc

laser-patroll: src/laser-patroll.cpp $(OBJS) $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INC) $(LDFLAGS) $(LDLIBS) -o laser-patroll src/laser-patroll.cpp $(OBJS)

src/BasicSort.o src/SortCommon.o src/BiotonicSort.o src/ImprovedBiotonic.o src/NumGen.o:
	$(MAKE) -C src CXX=$(CXX) INC=$(INC) LDFLAGS=$(LDFLAGS) LDLIBS=$(LDLIBS)

clean:
	rm -rf laser-patroll
	$(MAKE) -C doc $@
	$(MAKE) -C src $@
