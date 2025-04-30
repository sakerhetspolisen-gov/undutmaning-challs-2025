# The N3tw0rk

Misc
Medium (Inte så svår, men ganska lång)

## Beskrivning

Harriet misstänker att Kenneth har hittat medlöpare bland fanatiska AI anhängare på jorden och
att han skickat någon form av medelande till dem. Ett meddelande som kan vara av vikt att fånga upp. 
Hon har lyckats förmedla varningen till Harald, som i sin tur har lyckats avgränsa misstanken 
till ett mindre företagsnätverk i utkanten av internet.

Men sin laptop och en exprimentell, nyutvecklad programvara i högsta hugg förbereder han sig på 
att ta sig in i nätverket på jakt efter Kenneths meddelande. Hjälp till genom att ansluta dig 
till hans laptop på `X.X.X.X:3011`, där kör en tjänst som av rent nostalgiska skäl pratar telnet...

# För granskare

Mer information finns i `./solution/solution.md`

## Köra utmaningen lokalt

```
# might need sudo for docker 
docker build -t n3tw0rk .
docker run --rm -d --name n3tw0rk -p 3011:3011 n3tw0rk
telnet localhost 31337
```

## Flagga

Flaggan finns i `./lib/game/files/flag.txt` 
