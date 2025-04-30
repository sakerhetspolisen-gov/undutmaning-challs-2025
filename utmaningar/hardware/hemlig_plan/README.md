# Hemlig plan 

* Kategori: HW/Krypto/Programmering (främst HW)
* Troligen inom svårighetsgraden "Svår" (?) pga flera steg som möjligen kan vara kluriga för personer utan förkunskaper inom HW

# Beskrivning
Kenneth skickar hemliga meddelanden över en radiolänk till de andra övertagna satelliterna. 

Harald tror att det är viktigt att förstå vad som sägs i dessa meddelanden och har lyckas snappa upp ett av dessa krypterade meddelanden. 
Han avkodar det, men inser att den demodulerade informationen är krypterad. Attans! 

Som tur är har Harriet, på plats uppe i Kenneths satellit, grävt runt i verktygslådan och hittat ett verktyg för att spela in digitala signaler. Hon inser att satellitantennen måste vara kopplad till någon slags enhet i satelliten med ett exponerat kretskort. På denna enhet verkar det bland annat sitta en kryptomodul, en radiomodul och en gränssnittsmodul som används för att Kenneth ska kunna ge sina order i klartext till de andra satelliterna. 

Det hemliga meddelandet som Harald snappade upp har redan skickats, utan att Harriet kunde uppfatta vad som sades. Typiskt! Men bredvid enheten ligger lyckligtvis ett datablad som beskriver hur enheten fungerar. Harriets engelska är inte så bra, men hon ser att det finns en exponerad kontakt med fyra pinnar mellan kryptomodulen och gränssnittsmodulen som hon testar att koppla upp sitt mätverktyg på. Ingenting verkar hända, tills enheten plötsligt startar om och det dyker upp några digitala signaler från hennes verktyg som hon spelar in.

Kan du hjälpa Harriet att tolka vad som har spelats in för att i sin tur dekryptera det hemliga meddelandet? 
Till din hjälp får du databladet som Harriet lyckades hitta samt en skärmdump från hennes verktyg.

# För granskare
Denna chall kan ses som en mix av kategorierna HW, Krypto och Programmering. Både flagga och det krypterade meddelandet går att ändra på (tex för att bättre passa in i storyn). 

Flaggan sätts i 
```
src/flagspoilers/flag.txt
```

Klartextvarianten av det krypterade meddelandet sätts i 
```
src/flagspoilers/radio_msg.txt
```

För att bygga utmaningen och skapa filerna som krävs, sätt ett lämpligt värde på flaggan och kör sedan 

```
make
```

För att kunna bygga behöver du rätt paket osv, kör 

```
pip install -r requirements.txt
```

Om du vill bygga allt behövs även ``texlive``, ``exiftool`` och ``openssl``. 

# Övrigt
Denna utmaning består enbart av tolkning och dekryptering av nedladdade filer. Lösning finns under mappen solution.
