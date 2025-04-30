# Kollisionskurs

krypto (med inslag av misc och web)
Lätt

## Beskrivning
Kenneth verkar stressad av att Harriet är honom i hasorna och har kännt sig tvungen att skynda på sina planer.
Brådstörtat har Kenneth därför skickat iväg sin sond *OPS* (*Oplanerat Påskyndad Solsond*) mot solen för att börja undersöka förutsättningarna för sin Dyson-sfär (eller Dyson-bälte, för Kenneth vill fortfarande kunna framstå som ödmjuk). Sonden var egentligen inte alls färdig än och interfacet för kommunikation slängdes ihop av en underbetald IT-konsult i sista stund innan sonden sköts iväg.

Hastverk är sällan en bra förutsättning för kvalité och stabilitet.

Harriet lyckas lokalisera systemet precis efter uppskjutningen, men hittar åtminstone lite kvarglömd data;
två små shell-skript och en URL (`undutmaning-kollisionskurs.chals.io`). Hjälp Harriet att komma åt systemet!

## För granskare
Mer information finns i `./solution/solution.md`

## Köra utmaningen lokalt
```
# might need sudo for docker 
docker build -t kollisionskurs .
docker run --rm -d --name kollisionskurs -p 8222:8222 kollisionskurs
# browse to http://127.0.0.1:8222
```
