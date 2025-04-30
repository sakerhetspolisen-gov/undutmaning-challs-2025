# Teknisk beskrivning
Du kan telnet:a in till en server. Servern vill ha ett lösenord. Ger du rätt löseord får du flaggan.

Du får källkoden till servern som är skriven i det lite udda språket Smalltalk.
Den gör massa kollar på kombinationer av bytes i lösenordet och du måste ge ett som uppfyller alla.
 
# Flagga
Finns i flag.txt
 
# Hints
Z3?
 
# Lösningsförslag
Se `solver.py`. Den tänkta lösningen är att extrahera alla krav från Smalltalk programmet
och använda en sat-solver som till exempel Z3 för att hitta en sträng som uppfyller alla krav.
Det finns endast *en* sådan sträng.
