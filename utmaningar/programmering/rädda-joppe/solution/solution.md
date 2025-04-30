# Teknisk beskrivning

Utmaningen är att styra tillbaka en rymdfarkost till utgångspunkten. Farkosten rör sig i en tredimensionell
rymd rätlinjigt bort från origo. När man ansluter till tjänsten får man först en kort beskrivning av vad man
kan skicka för kommandon och sedan löpande en uppdatering av farkostens koordinater. Genom att skicka kommandon
för att köra farkostens motorer så kan man ändra farkostens riktning och styra den tillbaka till origo.

Farkosten har sex motorer i ortigonala riktningar, tyvärr har axelarna förskjutits jämtemot den omgivande rymdens 
axlar, så att styra farkosten har blivit klart kepigare. Man har dessutom en begränsad tid på sig och om farkosten
kommer för långt bort tappar man kontakten med den, bränslet i motorerna är begränsat och om man återkommer till
origo med för hög hastighet så krashar man farkosten.

# Lösningsförslag

Man löser fördelaktligen utmaningen med hjälp av ett program som läser av koordinaterna och utgående från 
deras förändring räknar fram hur man ska styra tillbaka farkosten. Förslag på lösning finns i `solution/solve.py`

# Flagga

Flaggan finns i `src/flag.txt` och har värdet:
`undut{In a world of infinite possibilities, we are but explorers navigating the cosmos, calculating our trajectory through the stars.}`