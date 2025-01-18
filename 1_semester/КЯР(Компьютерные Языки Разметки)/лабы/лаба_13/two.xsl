<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
<html>
	<head>
        <title>Аттестация 10ПИ</title>
    </head>
	<style>
		h1{
			text-align:center;
		}
        table {
			width: 80%;
            margin: 0 auto;
            border-collapse: collapse;
            }
        th, td {
            border: 1px solid black;
            padding: 8px;
            text-align: center;
            }
		.four{ 
			background-color: red; 
			color: white; 
			}
		.eight{
			background-color: green; 
			color: white; 
			}
    </style>
	<body>
		<h1>Аттестация 10ПИ</h1>
		 <table>
          <tr>
            <th>Фамилия</th>
            <th>ОПИ</th>
            <th>БЕЛЯЗ</th>
            <th>АНГЛ</th>
          </tr>
          <xsl:for-each select="atestat/info">
            <tr>
              <td><xsl:value-of select="surname"/></td>

              <!--опи-->
              <xsl:choose>
                <xsl:when test="opi &lt; 4">
                  <td class="four"><xsl:value-of select="opi"/></td>
                </xsl:when>
                <xsl:when test="opi &gt; 8">
                  <td class="eight"><xsl:value-of select="opi"/></td>
                </xsl:when>
                <xsl:otherwise>
                  <td><xsl:value-of select="opi"/></td>
                </xsl:otherwise>
              </xsl:choose>

              <!--беляз-->
              <xsl:choose>
                <xsl:when test="belaz &lt; 4">
                  <td class="four"><xsl:value-of select="belaz"/></td>
                </xsl:when>
                <xsl:when test="belaz &gt; 8">
                  <td class="eight"><xsl:value-of select="belaz"/></td>
                </xsl:when>
                <xsl:otherwise>
                  <td><xsl:value-of select="belaz"/></td>
                </xsl:otherwise>
              </xsl:choose>

              <!--англ-->
              <xsl:choose>
                <xsl:when test="angl &lt; 4">
                  <td class="four"><xsl:value-of select="angl"/></td>
                </xsl:when>
                <xsl:when test="angl &gt; 8">
                  <td class="eight"><xsl:value-of select="angl"/></td>
                </xsl:when>
                <xsl:otherwise>
                  <td><xsl:value-of select="angl"/></td>
                </xsl:otherwise>
              </xsl:choose>
            </tr>
          </xsl:for-each>
        </table>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>