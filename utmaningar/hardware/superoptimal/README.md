# superoptimal

* Hårdvara
* Medium

# Beskrivning

Denna utmaning är en fristående fortsättning på *suboptimal*.

Medan Harriet undersöker möjligheterna att ta över mesh-satelliterna i utmaningen *suboptimal* (<- länk till denna utmaning), stöter hon på en annan uppsättning satelliter, väldigt lika den första uppsättningen på de flesta sätt, men något är definitivt annorlunda - och värre!

Här ser det ut som om Kenneth har identifierat misstag från tidigare, lärt sig av dem och gjort det omöjligt att ta sig förbi lösenordsskyddet. Han verkar dessutom ha passat på att aktivera optimering när han kompilerade den nya firmwaren.

Anslut på `undutmaning-superoptimal.chals.io:443` och hjälp Harriet att möta detta nya, illavarslande hot!

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
