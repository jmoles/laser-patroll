
.PHONY: all
all: doc/report.pdf

doc/report.pdf: doc/report.tex
	cd doc; pdflatex report.tex
