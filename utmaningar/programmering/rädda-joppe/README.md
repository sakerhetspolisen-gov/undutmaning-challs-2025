# Rädda Joppe

programmering
medel

# Beskrivning

Av rymdskrot och material stulet från Kenneths system har Harriet lyckats konstruera en liten 
farkost hon kallar JOPPE, Jätteliten Opålitlig Platform för Potentiella Exkursioner. Hon har 
tänkt försöka använda den för att utforska rymden utanför satelliten och kanske hitta bättre
möjligheter både att ta sig hem och att bekämpa Kenneth. Men innan hon hinner klart med arbetet 
träffas olyckligtvis JOPPE av en asteroid och slungas ut i rymden.

Frenetisk försöker hon få kontakt med JOPPE via PowerGloven för att styra den tillbaka till 
henne så hon kan avsluta jobbet. Kan du hjälpa henne? Anslut till JOPPE och styr den tillbaka 
till Harriet - innan farkostens batteri tar slut eller den kommer för långt bort för att
PowerGlovens signal ska nå fram.

# För granskare

Lösning finns i `./solution`. Utmanaren kommer bli presenterad med nc <ip/domän> <port>.

## Köra binären

`python3 simulation.py`

## Servera och köra utmaningen lokalt över netcat

```
# might need sudo for docker 
docker build -t 'joppe' .
docker --rm --name joppe run -p 3000:3000 -d joppe
nc localhost 3000
```
