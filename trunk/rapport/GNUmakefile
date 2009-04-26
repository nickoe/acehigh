#
# Makefile til projektet
# Kræver latexmk og ca. hele texlive-distributionen
#
# $Id$
#


# Navn på masterfil
TARGET=master.tex

# Alle DIA-diagrammer
FIGS_DIA=../brugere/kjaergaard/hpglparser-ins.dia		\
../brugere/kjaergaard/hpglparser-param.dia			\
./img/egentlig-softwimpl-a.dia ./img/egentlig-softwimpl-b.dia	\
./img/i-motor-design-a.dia ./img/i-motor-design-b.dia

# Alle SVG-filer
FIGS_SVG=../logo/logo.svg ./img/forside.svg				\
../brugere/kjaergaard/datafeeder-handling.svg				\
../brugere/kjaergaard/skaermkoordinater.svg				\
./img/motorstyring-indlagt-forsinkelse.svg				\
../brugere/kjaergaard/motorstyring-afbrudt-afvikling.svg		\
../brugere/kjaergaard/motorstyring-afbrudt-afvikling-hastighed.svg	\
./img/fotogafel-skitse.svg img/forside.svg				\
../brugere/kjaergaard/software-oversigt.svg img/la-behandling.svg	\
../brugere/kjaergaard/datafoeder-uniform-api.svg			\
../brugere/kjaergaard/datafoeder.svg					\
../brugere/kjaergaard/datafoeder-uniform-api.svg			\
./img/afviklingsdiagram-cirkel.svg ./img/relativ-absolut.svg		\
./img/cirkel.svg ./img/fotogaffel.svg					\
./img/sd-kort-adapter-diagram.svg ./img/sd-kort-adapter-kobber.svg	\
./img/l6208n-driver-diagram.svg ./img/Tux-simple.svg			\
./img/matematik-skitse.svg ./img/tegnehoved-skitse.svg			\
./img/tid-hastighed-forhold-indlagt-forsinkelse.svg


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
	rm -f $(FIGS_EPS_GEN)
	rm -f $(FIGS_PDF_GEN)
	cd tex && latexmk -C


# Konvertering mellem forskellige formater

# fx dia -t eps -e target.eps target.dia
.dia.eps:
	dia -t eps -e $@ $<

# fx jpeg2ps target.jpeg > target.eps
.jpeg.eps:
	jpeg2ps $< > $@

# fx inkscape --export-eps=target.eps --export-text-to-path target.svg
.svg.eps:
	inkscape --export-eps=$@ --export-text-to-path $<

# fx inkscape --export-pdf=target.pdf --export-text-to-path target.svg
.svg.pdf:
	inkscape --export-pdf=$@ --export-text-to-path $<

# fx epstopdf target.eps
.eps.pdf:
	epstopdf --outfile=$@ $<

# fx pdftops -eps target.pdf
.pdf.eps:
	pdftops -eps $< $@
