CXXFLAGS+=-Wall 
LDLIBS = -lboost_program_options

SOURCES=$(wildcard src/*.cpp)
HEADERS=$(wildcard src/*.hpp)
DOC=doc/report.tex

.PHONY: all
all: doc/report.pdf laser-patroll

doc/report.pdf: $(DOC)
	$(MAKE) -C doc

laser-patroll: src/laser-patroll.cpp src/BasicSort.o src/BiotonicSort.o src/ImprovedBiotonic.o src/NumGen.o src/SortCommon.o $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o laser-patroll src/laser-patroll.cpp src/SortCommon.o src/BasicSort.o src/BiotonicSort.o src/ImprovedBiotonic.o src/NumGen.o

src/BasicSort.o src/SortCommon.o src/BiotonicSort.o src/ImprovedBiotonic.o src/NumGen.o:
	$(MAKE) -C src

clean:
	rm -rf laser-patroll
	$(MAKE) -C doc $@
	$(MAKE) -C src $@