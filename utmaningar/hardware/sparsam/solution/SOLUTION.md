# Teknisk beskrivning

Den här challen handlar om att genomföra en sidokanalsattack, Simple Power Analysis (SPA), på en osäker implementation av RSA. Därav namnet SPA + RSA = SPARSAm. Attacken är densamma som Paul Kocher demonstrerade i sin artikel *https://paulkocher.com/doc/TimingAttacks.pdf* redan 1996. Deltagaren får en faktisk energimätning från när en dekryptering sker på en Arduino UNO och ska utifrån den extrahera nyckel-exponenten.

# Story förslag (frivilligt)

Harriet stöter på en trasig satellit i omloppsbana. Det är en gammal forskingssatellit som samlat in data om klimatförändringar på jorden men av okänd anledning blev tyst innan den hann skicka hem datan. Efter en snabb analys visar det sig att den värdefulla forskingsdatan finns kvar på en disk men att den gamla datorn som kan dekryptera datan har försvunnit efter en kollision med rymdskrot. Tråkigt. Det finns dock en effektmätare på satelliten som tycks vara intakt. Kan en mätning från senaste gången datorn dekrypterade datan räcka för att göra det igen?

# Lösningsförslag

Se *solve.py*.

# Flagga

`undut{d3n_s0m_SPAr_h3n_h4r_s4_d3n_spaRSAmm3}`

Flaggan kan bytas ut genom att generera en ny skiffertext med *encrypt-flag.py* och *keys.txt*. Sedan måste *flagga.enc* bytas ut och en rad i *dekryptera.ino*.

