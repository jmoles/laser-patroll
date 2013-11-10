CXXFLAGS+=-Wall -std=c++11

.PHONY: all
all: doc/report.pdf bin/laser-patroll

doc/report.pdf: doc/report.tex
	cd doc; pdflatex report.tex

bin/laser-patroll: src/file.cpp src/BasicSort.o
	mkdir -p bin
	cd src; $(CXX) $(CXXFLAGS) -o ../bin/laser-patroll file.cpp BasicSort.o

BasicSort.o: src/BasicSort.cpp src/BasicSort.hpp
	cd src; $(CXX) $(CXXFLAGS) src/BasicSort.cpp src/BasicSort.hpp

clean:
	rm -rf bin/*
	rm -rf src/*.o