### Story-element

*Utkast till story. Utöka eller omformulera vid behov.*

Hariett tog ett varv runt den metalliska satellitkonstruktion som  utgjorde Kenneth och hennes blick synade utrustningen. Antenner, kameror, spektrometer, solceller, radarer. Allt väl sammansatt. Tusan också tänkte Hariett. Men det var något som fångade hennes uppmärksamhet. Det fanns en halvöppen skyddsplåt på baksidan av Kenneth som hon tänkte måste ha öppnats under hans tidigare uppskjutning. Hariett öppnade luckan helt och fann både en hårddisk och ett USB-minne väl tillgängliga. 
"Ni följer med mig..."

### Teknisk beskrivning 

Utmanaren får möjlighet att ladda ned två zip-arkiv `KennethHDD.zip` och `KennethUSB.zip` som innehåller
ett antal olika mappar och filer. Genom att gå igenom och analysera innehållet i filerna skall utmanaren
lista ut hur informationen ska extraheras ur filerna och använda den för att nysta sig fram till flaggan.

### Lösningsförslag 

Nedan följer en redogörelse för innehållet i de båda nedladdningsbara zip-filerna och hur det är tänkt
att man ska hantera innehållet för att komma åt flaggan.

____________________________________________________________________

#### WIN10HDD.zip

``` 
>\Users\KennethSpaceKingX\Desktop\

->Passwords.zip (AES256 krypterad)
Innehåller "passwords.txt" (som innehåller olika lösenord som syftar till att skapa förståelse för Kenneths lösenordsstruktur).

-->passwords.txt 
Lösenordsstrukturen i filen är: ett ord, följt av ett årtal som ibland är följt av ett utropstecken.

->NotesForMyself.odt
Undersök dokumentmetadatan. "Password to zip is the user password". "Don't forget to Dive into the -r ules" Få fram Windows-lösenordet.
	
-----------------

>\Users\KennethSpaceKingX\Pictures\

-> 173046437433896801.jpg 
Det finns inget mer än vad du ser i bilden. I verkligheten är man ofta väldigt nära lösningen men samtidigt också väldigt långt ifrån den. 

->OIP (5) - kopia.jfif
Bilden innehåller en text som visar Windows-lösenordet.

-----------------

>\Windows\System32\config\
->SAM och SYSTEM (två filer)

Använd impacket-secretsdump eller Mimikatz. 
Resultatet är Windows-användaren "KennethSpaceKingX":s NTLM-hash. Knäck med Hashcat. 
Det går inte att knäcka med bara Rockyou direkt. Hinten i NotesToMyself ger förslag att använda Hashcat-regeln dive.rule som är en defaultregel.
Detta går fort eftersom NTLM är en snabb hash. Det går även att hashen utan regel om Hashes.Org-listan används. Alternativt kombinera rockyou+rockyou (mode -a1).

Password: space1337 

Windows-lösenordet kan användas för att låsa upp ZIP-filen.

-----------------

>\Users\KennethSpaceKingX\Documents\ (sex stycken ods-filer)
Information om olika satelliter där satelliternas namn är intressanta. Lösenord i "Passwords.txt" är skapta utifrån namn på satelliter som finns med i ods-filerna. 

-----------------

>\Users\KennethSpaceKingX\AppData\Roaming\Mozilla\Firefox\Profiles\a0hmrg2h.default-release
Undersök Kenneths Firefox-användande.
Kenneth har googlat på satelliter och olika privacy-åtgärder samt laddat ner VeraCrypt.
Kenneth har även sparat tre stycken konton för login på olika tjänster i Firefox. Använd exempelvis Firefox_decrypt för att dekryptera logins.json. 
I det här fallet har Kenneth skyddat lösenorden med ett "Primary/Master Password". Lösenordet är av Kenneth satt till Windowslösenordet space1337.

Lösenorden till kontona visar ytterligare lösenordsstruktur i form av satellitnamn(1:a versal) <årtal> ev. följt av "!".

--------------------

Generella iakttagelser såhär långt: 
De påträffade lösenorden (förutom win pw) börjar alltid med stor bokstav, är i majoritet namn på satelliter, följt av ett årtal mellan 2019-2023 och följs ibland ett utropstecken.

Mål:
- Skapa en ordlista utifrån dessa iakttagelser och angrip filen på USB-minnet.

____________________________________________________________________
```


#### USB.zip

```
> EvilPlans 
-> Yttre volumen, Encryption: AES, hash: SHA-512.
Extrahera yttre volymens hash, det finns två sätt:
Legacy: "dd if=EvilPlans of=<filnamn> bs=512 count=1"
alternativt med hashcatverktyget: "veracrypt2hashcat.py <filnamn>"
Angrip yttre volymen med ordlistan du skapat vid undersökning av Win10HDD. Skapa en egen regel som skapar mönstret att första bokstaven 
blir versal och att man "appendar" 2019-2023 samt !  (Exempelvis: c$2$0$1$9$!) 
Angrip hashen med: hashcat -m 29421 (motsvarande default) <filnamn> -a0 <wordlist> -r <dinregel>.rule"
Vid legacymode: "hashcat -m 13721 <filnamn> -a0 <wordlist> -r <dinregel>.rule" (Mode 13721 är "default"-inställning för vc).

PW: Viking2023!

Yttre volymen innehåller en textfil med en youtube-länk (som leder till Rick Roll) men som också är själva lösenordet till den inre volymen. 

"https://www.youtube.com/watch?v=dQw4w9WgXcQ
My secrets are hidden deeper. Pw above." (URL:en är lösenordet till den inre volymen)

--------------------

-Inre/dolda volymen, Encryption: AES, hash: SHA-512.
Montera exempelvis EvilPlans i Veracrypt.exe/GUI/CLI och ange lösenordet.
Volymen innehåller en textfil som heter "Congratulations.txt" med undut{c1b835029a6129f932323c428d0c46fd5a70f41f} (som passande är SHA1-hash av strängen "RickAstley").
```

### Hints

**Hint**: This is not a stego challenge
**Hint 2**: Finns det något mönster i Kenneths lösenord? Kenneth älskar satelliter. Har Kenneth något särskilt intresse? Lägg ihop allt du har.

## Flaggan

Flaggan finns i `KennethUSB.zip` arkivet, filen `EvilPlans`, i `Inner partition`, textfilen `Congratulations.txt`.
Flaggan har värdet: `undut{c1b835029a6129f932323c428d0c46fd5a70f41f}`


