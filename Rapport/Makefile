PDFLATEX = pdflatex

SOURCE = main.tex

OUTPUT = main.pdf

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
    pdflatex

.PHONY: clean

clean:
    rm -f *.aux *.log *.toc *.out *.synctex.gz
