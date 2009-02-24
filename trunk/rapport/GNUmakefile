#
# Makefile til projektet
# Kræver latexmk og ca. hele texlive-distributionen
#
# $Id$
#


# Navn på masterfil
TARGET=master.tex

# Mappe til genererede billedfiler, med afsluttende skråstreg
IMGDIR=img/

# Alle DIA-diagrammer
FIGS_DIA=

# Alle SVG-filer
FIGS_SVG=../logo/logo.svg

# Alle EPS-filer (PS-illustrationer angivet i linien nedenunder)
FIGS_EPS=

# Alle PDF-filer
FIGS_PDF=

# Alle JPEG-filer, kun endelsen jpeg genkendes. Kræver jpeg2ps,
# http://www.pdflib.com/download/free-software/jpeg2ps/
FIGS_JPEG=


# Initialisering til figurkonvertering
FIGS_EPS_GEN=$(FIGS_DIA:.dia=.eps) $(FIGS_PDF:.pdf=.eps)	\
$(FIGS_JPEG:.jpeg=.eps) $(FIGS_SVG:.svg=.eps)
FIGS_PDF_GEN=$(FIGS_DIA:.dia=.pdf) $(FIGS_EPS:.eps=.pdf)	\
$(FIGS_SVG:.svg=.pdf)



.SUFFIXES: .dia .eps .pdf .jpeg .svg .ps

all:	pdf

dvi:	$(FIGS_EPS_GEN)
	latexmk $(TARGET)

ps:	$(FIGS_EPS_GEN)
	latexmk -ps $(TARGET)

pdf:	$(FIGS_PDF_GEN)
	latexmk -pdf $(TARGET)

clean:
	latexmk -C
	rm -f $(TARGET:.tex=.lox)
	rm -f $(TARGET:.tex=.out)
	rm -f $(addprefix $(IMGDIR), $(notdir $(FIGS_EPS_GEN)))
	rm -f $(addprefix $(IMGDIR), $(notdir $(FIGS_PDF_GEN)))
	cd tex && latexmk -C


# Konvertering mellem forskellige formater

# fx dia -t eps -e target.eps target.dia
.dia.eps:
	dia -t eps -e $(addprefix $(IMGDIR), $(notdir $@)) $<

# fx jpeg2ps target.jpeg > target.eps
.jpeg.eps:
	jpeg2ps $< > $(addprefix $(IMGDIR), $(notdir $@))

# fx inkscape --export-eps=target.eps --export-text-to-path target.svg
.svg.eps:
	inkscape --export-eps=$(addprefix $(IMGDIR), $(notdir $@)) --export-text-to-path $<

# fx inkscape --export-pdf=target.pdf --export-text-to-path target.svg
.svg.pdf:
	inkscape --export-pdf=$(addprefix $(IMGDIR), $(notdir $@)) --export-text-to-path $<

# fx epstopdf target.eps
.eps.pdf:
	epstopdf --outfile=$(addprefix $(IMGDIR), $(notdir $@)) $<

# fx pdftops -eps target.pdf
.pdf.eps:
	pdftops -eps $< $(addprefix $(IMGDIR), $(notdir $@))