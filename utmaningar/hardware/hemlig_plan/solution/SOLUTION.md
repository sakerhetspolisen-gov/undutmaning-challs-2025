# Lösning

Utmaningen består av att lista ut att ett UART-meddelande är det som har snappats upp av Hariettes verktyg (en logikanalysator) och att dekoda detta för att i sin tur hitta en säkerhetsmiss i loggningen hos CM-500, där AES-nyckeln skrivs ut. Med AES-nyckeln kan man då dekryptera det demodulerade radiomeddelandet som Harald fångade tidigare, eftersom det var den nyckeln som användes. Det finns några fallgropar på vägen som klurar till det lite, samt lite kod som behövs för att lösa det. 

Databladet innehåller all information som behövs för att dekoda meddelandet men man behöver sålla ut den relevanta informationen ur databladet (finns överflödig information), vilket görs genom att läsa beskrivningen till utmaningen och jämföra med vad som står i databladet. Skärmdumpen kan också hjälpa en att komma på rätt väg, sample rate och baud behövs också för att göra en rimlig dekodning. 

Man behöver också skriva ett program som avkodar UART-meddelandet, scriptet i sig är relativt lätt att göra (speciellt om man tar hjälp av valfritt AI-verktyg), men att lista ut att detta är vad som krävs kan vara lite knepigare för personer utan förkunskap i HW. Man kan fastna i saker som att missa att LSB skickas först och att meddelandet inte skickas i klartext utan med ett XOR-chiffer. XOR-nyckeln ges i databladet då tillverkaren har råkat skriva ut nyckeln i ändringshistoriken av databladet, att LSB skickas först är dels vanligt för UART, men ges också specifikt i databladet. Det kan också gå att fastna i att lista ut hur många bitar som samplas per "UART-bit", men all info för att få detta ges, det gäller bara att sålla ut rätt information (det kan även möjligen gå att helt enkelt kolla på hur datan ser ut och göra en kvalificerad gissning utifrån mönster i datan, om man vet att det är UART som samplas). 

När man lyckas avkoda UART-meddelandet så hittar man då att en AES-nyckel skrivs ut i loggen. Med info om att det är AES128-CBC från databladet kan man då också inse att ett IV behövs, vilket man hittar genom att se i det krypterade meddelandet att det första blocket är IVt i klartext (pga val av IV kan detta hittas enkelt med ``hexdump -C encrypted_radio_msg`` men även exempelvis ``strings encrypted_radio_msg`` kan ge en hint om detta, annars ger ett antagande om att första blocket är ett IV samma resultat). Dekrypterar man detta, samt även dekrypterar med tidigare använd XOR-nyckel på resulatet.  

## Steg-för-steg

Börja med informationsinsamling, följande info ges:
- Beskrivningen och filerna: En demodulerad kryptotext som ska dekrypteras (dvs det är ingen ren radiosignal). En okänd insamlad fil. Den okända filen är digitala signaler som har spelats in på en kontakt med fyra pinnar mellan kryptomodulen och gränssnittsmodulen på ett kretskort. Spelade in meddelandet när enheten startades om (denna vetskap är dock mer eller mindre irrelevant för själva utmaningen, den skapar bara ett sammanhang). 
- Databladet: Databladet innehåller följande relevant info:
    1. Från radiomodulen skickas krypterad data med AES-128 CBC med ett underliggande XOR-chiffer, detta är då vad vårt inspelade meddelande är. Databladet ger även hints om att det finns en standardnyckel lagrad i enheten.
    2. Det finns en kontakt mellan kryptomodulen och gränssnittsmoodulen som kan används för en UART-debug port -> inspelade signalen är UART-data. Extra hints om detta ges av att enheten startar om när någon närmar sig samt att debugginfo skickas över UART. Hinten i beskrivningen om att det är fyra pinnar är alltså kontakten som då är TX/RX+GND/3.3V för att debugga över UART. 
    3. UART-debuggen är samma signaler och samma typ som de som går till gränssnittsmodulen, denna data är krypterad med XOR-chiffer och har parametrarna 115200 baud, 8 databitar, 1 stopbit och ingen paritetsbit. Datan skickas med LSB först. 
    4. XOR-nyckeln är 0x67, ges av en miss i ändringshistoriken. 
- Screenshot: Kan ge en tydlig hint om att det är UART även här (googling på logic analyzer kan ge rätt spår), men ger främst info om vilken samplingsfrekvens som används, detta behövs för att avtolka data korrekt (ger samples/bit). 

UART-meddelandet behöver då avkodas enligt ovanstående info, detta kan exempelvis göras med ett script motsvarande ``uart_decode.py`` i denna katalog. 

När man kör detta script ges då en klartext med logginfo från uppstarten av kryptomodulen. Här hittar vi:

`` [00:00:01.023] [INFO] AES key loaded from secure storage: <NYCKEL> ``

Det loggas alltså vilken AES-nyckel som läses in, detta är standardnyckeln som användes även tidigare för det inspelade meddelandet. 

Med infon om att det är AES-128 CBC förstår vi också att det behövs ett IV, detta ges som det första blocket i radiomeddelandet. Detta kan man antingen förstå genom att göra en kvalificerad gissning eller kolla ``hexdump -C encrypted_radio_msg`` som ger en tydlig hint. 

Den hemliga planen (med tillhörande flagga) ges då av motsvarande script: ``decrypt_data.py``. Man kan även tänkas använda ``openssl`` eller liknande för dekrypteringen. 

Fullständig lösning ges i ``solution.py``. 

