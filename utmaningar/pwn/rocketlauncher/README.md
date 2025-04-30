# rocketlauncher
* pwn
* medel

## Beskrivning

Harriet har lyckats lokalisera en terminal via vilken hon kommer åt delar av Kenneths system. 
Där har hon inte bara kommit över källkod utan även listat ut att Kenneth använder systemet 
som terminalen styr till att bygga och skjuta upp rymdraketer.

Kan du få systemet att skjuta iväg en privilegierad raket?

`nc chall.undutmaning.se 31338`

# För granskare
* Lösning finns i `./solution` men försök gärna så gott som möjligt utan att kika
* Utmanaren kommer att få beskrivningen ovan
* Utmanaren kommer få ladda ned innehållet i `./download/`
* Utmanaren kommer även att bli presenterad med `nc <ip/domän> <port>`

## Köra binären 
```
tar -xzvf ./download/rocketlauncher.tgz
./rocketlauncher
```

## Servera och köra utmaningen lokalt över netcat
```
# might need sudo for docker 
docker build -t 'rocketlauncher' .
docker run -p31338:31338 -d rocketlauncher
nc localhost 31338
```

