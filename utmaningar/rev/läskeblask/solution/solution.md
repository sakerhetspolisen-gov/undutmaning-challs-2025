Med statisk analys (dekompilering) av binären ser det först ut som att det är en enkel jämförelse av input mot en konstant sträng i `main`  
Man upptäcker snabbt att detta lösenord är faktiskt fel.  

Innan `main` körs har `start` kört kort som skriver om sträng jämförelsen till ett annat hemligt lösenord.  
Enklast att lösa med debugger. Sätt då breakpoint innan jämförelsen (på main) eftersom jämförelsen raderas och ersätts.
