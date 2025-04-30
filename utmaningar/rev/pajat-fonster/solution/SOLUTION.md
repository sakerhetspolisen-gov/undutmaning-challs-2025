# Solution
Detta är en utmaning som går ut på att analysera en BSoD dump som Windows har genererat. Tillvägagångssättet är genom att ladda ner WinDBG och kika på det data som sparats i dumpen.
När man fått upp en WinDBG-miljö och kört till exempel `!analyze -v` kommer man snabbt till slutsatsen att `Driver1` är den drivare som orsakat bluescreenen. I samband med detta kommer man även komma fram till vilken instruktion som gjort det. 
Ifall man då disassemblar `Driver1` fr.o.m basen (dvs `Driver+0x1000`), kommer man att hitta en massa data som XOR:as med varandra och sedan töms. Lösningen är då att extrahera detta data och utföra XOR:en själv.
# Flagga
Flaggan har värder `undut{w0w_1_l0v3_blu35cr33n5}`
