LATEX = pdflatex
TARGETS = presentation.pdf

all: ${TARGETS}

%.pdf: %.tex %.aux
	${LATEX} $<

%.aux: %.tex
	${LATEX} $<

mpp.pdf: presentation.tex

clean:
	rm -f *.aux *.log *.toc *.lof
	rm -f *.bbl *.blg
	rm -f *.nav *.out *.snm
	rm -f *.vrb

mrproper: clean
	rm -f ${TARGETS}

remake: clean all
