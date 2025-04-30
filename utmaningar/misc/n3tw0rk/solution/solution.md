# Story

Kenneth har skickat viktig information/uppgifter till en av sina nyttiga idioter nere på jorden 
som han hoppas ska gå hans ärenden. Harald har utvecklat ett inovativt nytt program för att 
leta efter informationen.

# Teknisk beskrivning

*The N3tw0rk* är en MUD - *Multi User Dungeon*, dvs ett textäventyr för flera spelare samtidigt.
I *The N3tw0rk* tar spelarna rollen av en självmedveten byte data, skapad av *FlagDiscovery* processen
som exekverar på en dator alldeles utanför ett nätverk (n3tw0rk.ex). Genom att ta reda på information 
och skaffa sig samt manipulera olika nätverksheadrar kan spelarna röra sig genom nätverket och ta sig 
förbi olika hinder, i form av till exempel brandväggar och IDS system.

Genom all leta sig fram längre och längre in i nätverket kan spelarna så småningom hitta flaggan.
Eftersom utmaningen är baserad på ett gamalt MUDLib så kör utmaningen över telnet.

# Flagga

Flaggan finns i `./lib/game/files/flag.txt` 
och har världet `undut{The truth may be out there, but the lies might be inside your head!}`

# Lösningsförslag 

En nätverkskarta ligger i filen `./network-map.graphml`.

## Walkthrough

För en mer detaljerad förklaring av lösningen se `./n3tw0rk-writeup.pdf` eller titta på walkthrough 
videon `./n3tw0rk-walkthrough.mp4`.

Det finns många olika sätt att ta sig igenom nätverket, men nedan är **en** väg som man kan följa.
På vissa ställen finns det ledtrådar och på vissa ställen finns det information som är tänkt
att vara förvirrande eller missledande.

Börja med att ansluta och välja innehåll. Sen följer utför du följande kommandon. Vissa 
av dem är inte nödvändiga för att klara av utmaningen, men de finns med för att du ska kunna
klara av utmaningen utan att sitta på hela listan av kommandon.

```
la terminal
d
request udp
manipulate udp header src:50000
manipulate udp header dst:53
la me
d
request ip
manipulate ip header dst:198.51.100.25
manipulate ip header src:128.32.137.251
request checksum
d
request ethernet
manipulate ethernet header src-address:E0:2C:B2:01:C0:A2
manipulate ethernet header dst-address:00:03:32:F2:33:21
us
us
port2
ds
u
gi0/1
la me
manipulate ip header src:127.0.0.1
manipulate ip header dst:127.0.0.1
request checksum
u
la switchboard
la display
d
manipulate ip header src:128.32.137.251
manipulate ip header dst:198.51.100.25
manipulate ip header
manipulate ip header checksum:0x85CB
request checksum
la me
manipulate ethernet header src-address:00:03:32:F2:33:22
manipulate ethernet header dst-address:00:14:22:FE:61:12
d
ds
ds
port4
ds
u
u
53
la list
read list
d
d
manipulate ip header src:127.0.0.1
manipulate ip header dst:127.0.0.1
request checksum
u
drop udp header
request tcp
manipulate tcp header dst:110
manipulate tcp header src:43242
request checksum
110
la units
la open mailbox
la Wait until inter is distracted then <investigate inside mailbox>
d
la information
manipulate ip header src:198.51.100.25
manipulate ip header dst:198.51.100.199
manipulate tcp header src:34887
manipulate tcp header dst:34887
manipulate tcp header src:110
request checksum
d
request checksum
d
manipulate ethernet header src-address:00:14:22:FE:61:12
manipulate ethernet header dst-address:00:03:32:F2:33:22
us
us
port0
us
u
gi0/2
la me
manipulate ip header src:127.0.0.1
manipulate ip header dst:127.0.0.1
request checksum
u
la screen
d
manipulate ip header src:198.51.100.25
manipulate ip header dst:198.51.100.199
manipulate ip header checksum:0xA6AB
manipulate ethernet header src-address:00:03:32:F2:33:23
manipulate ethernet header dst-address:60:5B:30:FE:0B:98
d
ds
ds
port1
ds
u
u
34887
la text
d
la numbers
manipulate tcp header src:55643
manipulate tcp header dst:631
manipulate ip header src:198.51.100.199
manipulate ip header dst:198.51.100.182
manipulate ethernet header dst-address:c0:fb:f9:0b:72:9e
manipulate ethernet header src-address:60:5B:30:FE:0B:98
request checksum
d
request checksum
d
us
us
port3
ds
u
u
631
push boxes
la Wait until the art director starts tidying up then <inspect blobs>
```
