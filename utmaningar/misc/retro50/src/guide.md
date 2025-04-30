Denna challenge måste skapas manuellt.  
Kräver ZX Spectrum emulator (fuse-emulator på linux).  
Kräver tape2wav (fuse-emulator-utils)

I emulatorn, skriv BASIC program som printar 16-bit nummer.  
Dessa 16-bit nummer ska vara DEC Radix50 encoding av flaggan.  
Formatet saknar dock underscore (_) och måsvingar {} så det är bra om både "sträng" och "undut{sträng}" finns som flaggor i CTFd.  

Detta är programmet:
```basic
REM Message to Ken Olsen
REM from Clive Sinclair
REM ********************
PRINT "  Sorry for this BASIC."
PRINT "  Now you had to use my ZX."
PRINT "  But dont worry. I used your"
PRINT "  system to encode this message:"
DATA  1,2,3,4,5
LET R=17312: LET O=45025
RANDOMIZE R
READ W: LET W=W-INT (RND*0)
PRINT W
GO TO 40
```
Ladda helst existerande challenge för att redigera.

Kör skriptet "create_integer_array.py" och skriv in det på rad 10 (skriv över gamla DATA).
I emulatorn tryck `Media -> Tape -> Clear`
Spara med: `SAVE "CHALLENGE"`
Enter två gånger.
I emulatorn tryck `Media -> Tape -> Write` och välj namnet, kommer sluta på .tzx.
kör `tape2wav retro50.tzx retro50.wav` för att konvertera till kassettband.
