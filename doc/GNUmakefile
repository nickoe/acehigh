#
# $Id$
#

# Target files
TARGETS=WhyNotUseHardwareTimersCounterForImpulseGeneration.xml

DEFAULT_FORMAT=html

# Path to xsltproc
XSLTPROC=xsltproc

# DocBook customization
XSL=acehigh.xsl

.SUFFIXES: .html .xml

%.html: %.xml
	@$(XSLTPROC) -o $@ $(XSL) $<

base:	$(DEFAULT_FORMAT)

html:	$(TARGETS:.xml=.html)

clean:
	@rm -f *.html
