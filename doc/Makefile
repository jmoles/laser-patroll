TEXINPUTSPATHS=.:$(TEXINPUTS):include/IEEEtran:../src/:data/
UNAME:=$(shell uname -s)

ifeq ($(UNAME), Darwin)
	VIEWER=open
else
	VIEWER=evince
endif

SOURCES=$(wildcard ../src/*.cpp)
HEADERS=$(wildcard ../src/*.hpp)
DATA=valgrind.out data/basic.csv data/bitonic.csv data/merge.csv data/quick.csv
INCLUDES=$(SOURCES) $(HEADERS) $(DATA)

report.pdf: include/IEEEtran report.tex manualsources.bib mendeleysources.bib $(INCLUDES)
	TEXINPUTS=$(TEXINPUTSPATHS) pdflatex report
	TEXINPUTS=$(TEXINPUTSPATHS) bibtex report
	TEXINPUTS=$(TEXINPUTSPATHS) pdflatex report
	TEXINPUTS=$(TEXINPUTSPATHS) pdflatex report

include/IEEEtran:
	$(MAKE) -C include

doxygen/html/index.html: Doxyfile
	mkdir -p doxygen
	doxygen Doxyfile

.PHONY: show
show: report.pdf
	$(VIEWER) report.pdf



clean:
	rm -rf *.log
	rm -rf *.pdf
	rm -rf *.aux

really_clean: clean
	$MAKE -C include $@

