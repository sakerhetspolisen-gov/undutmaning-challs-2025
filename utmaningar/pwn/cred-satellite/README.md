# cred-satellite
* pwn
* svår

## Beskrivning
Vid en inhämtning av data lyckades Harriet komma över en systemkopia av en misstänkt
kommunikations-satellit. Inhämtningen visar sig innerhålla halvfärdig kod som verkar köra
i produktion. Samtidigt tipsar GPZ om att minnes-korruption kan leda till
fullständig systemkompromiss. Kan du hjälpa henne att ta över kontrollen av satelliten?

`nc chall.undutmaning.se 31341`

# För granskare
* Lösning finns i `./solution/`
* Utmanaren får beskrivningen ovan samt innehållet i `./download/`


## Köra utmaningen lokalt
```bash
tar -zxf ./download/cred-satellite.tar.gz
./run.sh
```

## Servera och köra utmaningen lokalt
```bash
docker build -t cred-satellite .
docker run -p 31341:31341 -d cred-satellite
nc localhost 31341
```

