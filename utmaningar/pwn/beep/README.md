# beep
* pwn
* uppvärmning/lätt

## Beskrivning

Kenneth verkar ha problem med kommunikationen till andra system han tagit över. 
Harriet har hittat något slags litet testprogram vars syfte verkar vara att testa att en anslutning fungerar.

Testprogrammet verkar vara ganska minimalt, men även små program kan innehålla buggar... 

Använd `snicat` eller liknande till `undutmaning-beep.chals.io` för att ansluta till testa anslutningen du också. 

Gratis hint: Harriet tror att det finns en buffer overflow i koden. Pröva att undersöka programmet 
med t.ex. `Ghidra` och `gdb` för att se ifall du kan knäcka buggen!

Gratis hint: `setup()`-funktionen kan ignoreras då den endast sätter en timer på utmaningen samt stänger av buffering på
`stdin`/`stdout`/`stderr`.

# För granskare
* Utmanaren kommer att få beskrivningen ovan
* Utmanaren kommer få ladda ned innehållet i `./download/`
* Utmanaren kommer även att bli presenterad med `nc <ip/domän> <port>`

## Köra binären 
```
./download/beep
```

## Servera och köra utmaningen lokalt över netcat
```
# might need sudo for docker 
docker build -t 'beep' .
docker run -p31339:31339 -d beep
nc localhost 31339
```

