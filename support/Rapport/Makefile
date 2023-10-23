LATEX = pdflatex
TARGETS = EMBARKI_GAUTHIER_HUMBERT.pdf

all: ${TARGETS}

%.pdf: %.tex %.aux
	${LATEX} $<

%.aux: %.tex
	${LATEX} $<

mpp.pdf: EMBARKI_GAUTHIER_HUMBERT.tex

clean:
	rm -f *.aux *.log *.toc *.lof
	rm -f *.bbl *.blg
	rm -f *.nav *.out *.snm
	rm -f *.vrb

mrproper: clean
	rm -f ${TARGETS}

remake: clean all
