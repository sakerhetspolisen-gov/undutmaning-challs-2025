# suboptimal

* Hårdvara
* Lätt

# Beskrivning

Harriet snubblar över ett gäng ytte-pytte-små satelliter som swooshar omkring i omloppsbana. Vid en närmare titt verkar det som att Kenneth använder dessa som något slags mesh-nät för att styra sina kontrollerade satelliter. För att sakta ned Kenneths ondskefulla planer vill hon ta tillbaka kontrollen över dom. Tyvärr är mikrokontrollern som hanterar satellit-interfacet låst och kräver ett lösenord... 

Efter lite skrollande hittar Harriet en glitcher-modul i sin PowerGlove. Den kan jacka in i mini-satellitens debug-port, läsa viss debug-information, och göra en voltage-glitch på mikrokontrollern. Parametrarna för glitchen är kalibrerade för att mikrokontrollern felaktigt ska hoppa över en instruktion. När felinjiceringen sker läser den också ut från debug-porten på vilken adress som detta skedde.

Anslut på `undutmaning-suboptimal.chals.io:443` och hjälp Harriet att ta över mesh-nätet!

# För granskare

Lösning finns i `./solution` men försök gärna så gott som möjligt utan att kika.
Utmanaren kommer att få beskrivningen ovan.
Utmanaren kommer få ladda ned innehållet i `./download/`
Utmanaren kommer även att bli presenterad med nc `<ip/domän> <port>`

# Servera och köra utmaningen lokalt
```
podman build --tag=glitch-emulator .
podman run --rm -p 3000:3000 glitch-emulator
nc 127.0.0.1 3000
```

Obeservera att *src/glitch-emulator/serve-internal.sh* begränsar max antal simultana körningar.
