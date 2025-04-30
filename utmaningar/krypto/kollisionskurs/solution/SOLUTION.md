# Teknisk beskrivning

**Kollisionskurs** är en enkel krypto/misc-uppgift som bygger på checksummekollisioner. Utmanaren kan ansluta till ett 
webinterface där man kan ladda upp shellscript. Endast ett antal godkända, fördefinierade godkända shellscript accepteras
dock. Om scriptet är godkänt avgörs med en enkel CRC16-XMODEM checksumma. Genom att känna till ett av de godkända scripten 
kan utmanaren orsaka en checksumme kollison med ett eget script och på så sätt exekvera godtyckligt shellscript.

Att det handlar om att försöka hitta en checksummekollision framgår av namnet på challen och att det är CRC16 med XMODEM polynomet som används hintas genom att namnet Ward Christensen finns med på siten.

# Lösningsförslag

Det är helt enkelt en fråga om att generera ett godtyckligt shellskipt som har samma CRC16 checksumma som ett av de godkända, 
en process som tar några sekunder. Scriptet `solve.py` kan användas för att generera fram godtyckliga skript med en bestämd
checksumma.

Sedan är det bara en fråga om att lokalisera filen `uppdragsparametrar.json` på servern och läsa den för att hitta flaggan
som finns "gömd" i den.


# Flagga
Flaggan finns i `uppdragsparametrar.json` och har värdet:

`undut{Ett steg i taget tar dig till målet, oavsett avstånd. Förutsatt att du inte går åt fel håll.}`

