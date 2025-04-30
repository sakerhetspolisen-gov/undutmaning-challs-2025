# Läskeblask
rev
medium

# Beskrivning

Harriet hittar en lösenordskyddad fil och en post-it lapp med vad som verkar vara ett lösenord.
I sin iver att fort knappa in lösenordet, råkar hon spilla läskeblask över satellitens modermodem!

-Nåja, säger hon tyst för sig själv. Det där är Kenneths problem.

Föga anade hon att det strax skulle bli hennes problem också.

Lösenordet visade sig nämligen inte längre fungera.
Ajdå. Det måste ha kommit kolsyra i filsystemet.

-Vad gör jag nu?! tänkte Harriet.

Hjälp Harriet genom att skicka in rätt lösenordet till `undutmaning-exempelutmaning.chals.io:443`.

# För granskare

Lösning finns i `./solution` men försök gärna så gott som möjligt utan att kika.
Utmanaren kommer att få beskrivningen ovan.
Utmanaren kommer få ladda ned innehållet i `./download/`
Utmanaren kommer även att bli presenterad med service på `<ip/domän> <port>`

# Servera och köra utmaningen lokalt
```bash
cd src
# Sätt frivilligt lösenord på max 26 tecken i genrealpassword.py REALPASS
make  # Skapar binären med nya lösenordet
docker build --tag=laskeblask .
docker run --rm -p 80:2048 laskeblask
nc 127.0.0.1 80
```
