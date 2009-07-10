<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:import href="/usr/share/xml/docbook/stylesheet/nwalsh/xhtml/docbook.xsl"/>
  <xsl:param name="toc.max.depth">1</xsl:param>
  <xsl:param name="html.stylesheet" select="'acehigh.css'"/>
  <!-- relative path to html files -->
  <xsl:param name="html.base" select="html"/>
</xsl:stylesheet>
