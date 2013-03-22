<xsl:stylesheet>
  <xsl:template match="papa">
    < root>
      rajoute du texte ici
      <xsl:apply-templates/>
    </root>
  </xsl:template>
  <xsl:template match="fils">
    < demi-fils>
      <xsl:apply-templates/>
    </demi-fils>
  </xsl:template>
</xsl:stylesheet>
