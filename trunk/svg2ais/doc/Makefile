#
# Makefile til projektet
# Kræver latexmk og ca. hele texlive-distributionen
#
# $Id: Makefile 26 2008-11-24 15:28:34Z kkjaergaard $
#

TARGET=manual.tex

all: dvi ps pdf

figs-eps:
	dia -e obj-oversigt.eps -t eps obj-oversigt.dia

figs-pdf-from-eps:	figs-eps
	epstopdf obj-oversigt.eps

dvi:	figs-eps
	latexmk $(TARGET)

ps:	figs-eps
	latexmk -ps $(TARGET)

pdf:	figs-pdf-from-eps
	latexmk -pdf $(TARGET)

clean:
	latexmk -C
	rm -f obj-oversigt.eps
	rm -f obj-oversigt.pdf
	rm $(TARGET:.tex=.out)