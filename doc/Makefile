TEXINPUTSPATHS=.:$(TEXINPUTS):include/IEEEtran
UNAME:=$(shell uname -s)

ifeq ($(UNAME), Darwin)
	VIEWER=open
else
	VIEWER=evince
endif

report.pdf: include/IEEEtran report.tex manualsources.bib mendeleysources.bib
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

