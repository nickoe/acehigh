#
# Makefile til projektet
# Kræver latexmk og ca. hele texlive-distributionen
#
# $Id: Makefile 26 2008-11-24 15:28:34Z kkjaergaard $
#

TARGET=rapport.tex

all: dvi ps pdf

dvi:
	latexmk $(TARGET)

ps:
	latexmk -ps $(TARGET)

pdf:
	latexmk -pdf $(TARGET)

clean:
	latexmk -C
	rm $(TARGET:.tex=.out)
