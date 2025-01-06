<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<?xml-stylesheet type="text/css" href="./css/one.css"?>
    <xsl:template match="/">
        <html>
		<style>
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
                    th {
                        background-color: red;
                        color: white;
                    }
			</style>
            <head>
                <title>Покупки</title>
            </head>
            <body>
                <h2 style="text-align: center;">Покупки</h2>
                <table>
                    <tr>
                        <th>Название товара</th>
                        <th>Описание</th>
                        <th>Цена ($)</th>
                    </tr>
                    <xsl:for-each select="one/tovar">
                        <xsl:sort select="price" data-type="number" order="ascending"/>
                        <tr>
                            <td><xsl:value-of select="name"/></td>
                            <td><xsl:value-of select="description"/></td>
                            <td><xsl:value-of select="price"/></td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>
