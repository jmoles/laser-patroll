TEXINPUTSPATHS=.:$(TEXINPUTS):include/IEEEtran

report.pdf: include/IEEEtran report.tex
	TEXINPUTS=$(TEXINPUTSPATHS) pdflatex report.tex
	TEXINPUTS=$(TEXINPUTSPATHS) pdflatex report.tex

include/IEEEtran:
	$(MAKE) -C include

doxygen/html/index.html: Doxyfile
	mkdir -p doxygen
	doxygen Doxyfile



clean:
	rm -rf *.log
	rm -rf *.pdf
	rm -rf *.aux

really_clean: clean
	$MAKE -C include $@
