CXXFLAGS+=-Wall -std=c++11

.PHONY: all
all: doc/report.pdf bin/laser-patroll

doc/report.pdf: doc/report.tex
	cd doc; pdflatex report.tex

bin/laser-patroll: src/laser-patroll.cpp src/BasicSort.o
	mkdir -p bin
	cd src; $(CXX) $(CXXFLAGS) -o ../bin/laser-patroll laser-patroll.cpp BasicSort.o

BasicSort.o: src/BasicSort.cpp src/BasicSort.hpp
	cd src; $(CXX) $(CXXFLAGS) src/BasicSort.cpp src/BasicSort.hpp

clean:
	rm -rf bin/*
	rm -rf src/*.o