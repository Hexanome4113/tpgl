<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="racine">
  <html>
    <head>
      <title>Test de fichier HTML</title>
      <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
    </head>
     <body>
       <xsl:apply-templates/>
    </body>
  </html>
</xsl:template>

<xsl:template match="paragraph">
   <p><xsl:apply-templates/></p>
</xsl:template>

<xsl:template match="title">
   <h1><xsl:apply-templates/></h1>
</xsl:template>

<xsl:template match="subtitle">
   <h2><xsl:apply-templates/></h2>
</xsl:template>

<xsl:template match="table">
   <table><xsl:apply-templates/></table>
</xsl:template>

<xsl:template match="table-row">
   <tr>
	    <xsl:apply-templates/>
   </tr>
</xsl:template>

<xsl:template match="table-header">
        <th>
	    <xsl:apply-templates/>
        </th>
</xsl:template>

<xsl:template match="table-cell">
        <td>
	    <xsl:apply-templates/>
        </td>
</xsl:template>

</xsl:stylesheet>
