# vivivi

Misc
Lätt/Medium

# Beskrivning

På grund av en tveksamt konfigurerad webtjänst har Kenneth lyckats starta en begränsad variant av sig själv på en vädersatellit. 
Detta begränsade medvetande har tagit sig namnet Valter och i ett försök att utveckla sig har medvetandet matat sin modell med all träningsdata det har lyckats komma över.

Olyckligtvis för Valter verkar detta bara inneburit samtliga manualsidor för *VIM* och en D-uppsats i musikteori från *Musikhögskolan Ingesund* med titeln
*Diabolisk estitik och den symfoniska ondskan: En hermeneutisk studie av ockult symbolism och musikaliskt uttryck i brittisk heavy metal*.

Nu har Harriet lyckats koppla upp sig mot Valter och försöker ta sig djupare in i hans system för att kanske hitta ett sätt att hindra honom från att sprida sig vidare.

Kan du hjälpa henne? Anslut dig till Valter på `undutmaning-vivivi.chals.io` och försök förstå dig på den...

# För granskare

Lösning finns i `./solution`. Utmanaren kommer bli presenterad med en adress att ansluta till.

# Servera och köra utmaningen lokalt över netcat

```
# might need sudo for docker 
docker build -t 'vivivi' .
docker --rm --name vivivi run -p 4711:4711 -d vivivi
nc localhost 4711
```

