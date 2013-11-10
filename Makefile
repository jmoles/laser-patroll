CXXFLAGS+=-Wall 
LDLIBS = -lboost_program_options

.PHONY: all
all: doc/report.pdf bin/laser-patroll

doc/report.pdf: doc/report.tex
	cd doc; pdflatex report.tex

bin/laser-patroll: src/laser-patroll.cpp src/BasicSort.o
	mkdir -p bin
	cd src; $(CXX) $(CXXFLAGS) $(LDLIBS) -o ../bin/laser-patroll laser-patroll.cpp BasicSort.o

BasicSort.o: src/BasicSort.cpp src/BasicSort.hpp src/NumGen.cpp
	cd src; $(CXX) $(CXXFLAGS) $(LDLIBS) src/BasicSort.cpp src/BasicSort.hpp src/NumGen.cpp

clean:
	rm -rf bin/*
	rm -rf src/*.o