# Solution
Detta är en utmaning som går ut på att "revva" två rader GBZ80 assembly i sammanhanget av Pokemon Blue. Koden i detta fall laddar in en mängd data i ett register och anropar därefter en funktion. 
Funktionen den kallar på är DisplayText (som man skall komma fram till genom att googla på resurser relaterat till gen 1 pokemon) vilket innebär att man kan dra slutsatsen att den 
displayar det data:t. Vid detta lag kan man antingen välja att avkoda data:t, vilket är det enkla alternativet, eller köra koden rakt upp och ner genom ACE vilket är väldigt jobbigt. 
Ifall man väljer att avkoda data:t kommer man fram till att data:t ej är kodat i ASCII utan i en egen kodning. När man insett detta faktum gäller det endast att avkoda enligt dess egna kodning för att få ut flaggan.
# Flagga
Flaggan har värdet `UNDUT▶(JAG-ALSKAR-GEN1)END` men även `UNDUT{JAG-ALSKAR-GEN1}` och `UNDUT{(JAG-ALSKAR-GEN1)}` accepteras och flaggan är *inte* case-sensitive.

