# Target files
TARGETS=SelectingAccelerationMethodForImpulseGenerator.xml

DEFAULT_FORMAT=html

# Output directories
HTML_OUTPUT=html

# Path to xsltproc
XSLTPROC=xsltproc

# DocBook customization
XSL=acehigh.xsl

.SUFFIXES: .html .xml

%.html: %.xml
	@$(XSLTPROC) -o $(HTML_OUTPUT)/$@ $(XSL) $<

base:	$(DEFAULT_FORMAT)

html:	$(TARGETS:.xml=.html)

clean:
	@rm -f *.html
