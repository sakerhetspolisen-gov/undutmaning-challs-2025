# Teknisk beskrivning

"Optimal"-utmaningarna simulerar hur säkerhetsmekanismer som lösenordsskydd kan kringås med hjälp av felinjicering. I uppgifternas beskrivning står att det i det här fallet är en spännings-glitch men det hade lika gärna kunnat vara en klock-glitch. Antaget är att verktyget för att utföra glitchen redan är finjusterat så att det deterministiskt påverkar mikrokontrollern på så sätt att den hoppar över att exekvera en instruktion, dvs att programräknaren inkrementerar dubbelt så mycket som den borde. Detta är ett väldigt förenklat scenario då felet i verkligheten kan anta många olika former. Verktyget ger också, genom begränsad debug-funktionalitet, värdet av programräknaren i det ögonblick som glitchen sker. Detta, tillsammans med den firmware som kan laddas ned, är tillräckligt för att med reversing och metodisk sökning hitta fram till en instruktion, en punkt i exekveringen, som är sårbar och låter lösenordet eller flaggan läsas ut.

# Story förslag (frivilligt)

Se *README.md*.

# Lösningsförslag

En metodik för att lösa uppgiften är följande:
1. Reversa firmware och identifiera en sårbarhet, dvs en instruktion som, i det fall den inte exekveras, kommer att läcka flaggan eller lösenordet.
2. Uppskatta en *delay*, ungefär hur många instruktioner som måste exekveras för att nå till sårbarheten.
3. Testa den uppskattade *delay* och se vilken adress som programräknaren innehåller när glitchen utförs.
4. Referera tillbaka till disassemblyn och gör en ny kvalificerad uppskattning om vilken *delay* som ger korrekt tidpunkt. Återgå till punkt **3** tills dess att rätt tidpunkt hittats.
5. Antingen läs av flaggan direkt eller läs av lösenordet och använd det för att läsa ut flaggan.

## Superoptimal

Då det sker kontinuerliga kontroller av lösenorden och det bara finns möjligthet att utföra en glitch (ett realistiskt scenario) är det inte längre möjligt att kringgå lösenordsskyddet. Den optimering som kompilatorn gör introducerar dock helt nya sårbarheter. I tidigare utmaningen fanns loopar enligt följande:

```c
  for (i = 0; i < 66; i++) {
    usart_send_blocking(USART1, welcome_msg[i]);
  }
```

Kompilatorns optimering ändrar kriteriet `i < 66` till `i != 66` vilket är funktionellt ekvivalent men introducerar en ny sårbarhet om felinjicering finns med i hotmodellen. Detta eftersom slutkriteriet ändrats till något väldigt mycket mer specifikt. Om slutkriteriet skippas då loopen är i sin sista iteration kommer vi få en situation då `i > 66` och därmed kommer den att fortsätta iterera. Den kommer som konsekvens att fortsätta skriva ut minne som ligger efter *welcome_msg* i programmet.

Se *solve.py* för specifiks lösningsförslag. Notera att det finns flera lösningar på denna uppgift.

# Flagga

Flaggan kan läsas ut om korrekt lösenord matas in eller om lösenordsskyddet kringgås i den firmware som exekveras på servern. I den firmware som kan laddas ned är både flagga och lösenord ändrade.

`undut{th3Y_c_m3_unr0llin}`
