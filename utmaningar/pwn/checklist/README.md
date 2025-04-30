# Checklist
* pwn
* medel

## Beskrivning

Man behöver kryssa i en lång lista med att-göra saker innan man kan skjuta upp en raket. Om vi missar något så kan vi krascha! Att krascha är inte ett acceptabelt alternativ!

Vänligen konstruera en lista och invänta godkännande från administratör innan uppskjutning.

List-tjänsten har adressen undutmaning-checklist.chals.io:443.

Om du behöver hjälp med att ansluta finns information om hur du gör för att ansluta till utmaningstjänster på informationssidan.

# För granskare
* Utmanaren kommer att få beskrivningen ovan
* Utmanaren kommer få ladda ned innehållet i `./download/`
* Utmanaren kommer även att bli presenterad med `nc <ip/domän> <port>`

## Köra binären 
```
./download/checklist
```

## Servera och köra utmaningen lokalt över netcat
```
# might need sudo for docker 
docker build -t 'checklist' .
docker run -p31340:31340 -d checklist
nc localhost 31340
```
