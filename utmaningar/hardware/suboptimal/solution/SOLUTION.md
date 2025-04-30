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

Se *solve.py* för specifiks lösningsförslag. Notera att det finns många lösningar på denna uppgift.

# Flagga

Flaggan kan läsas ut om korrekt lösenord matas in eller om lösenordsskyddet kringgås i den firmware som exekveras på servern. I den firmware som kan laddas ned är både flagga och lösenord ändrade.

`undut{t0_x3cUte_oR_n0t_to_Xecut3}`
