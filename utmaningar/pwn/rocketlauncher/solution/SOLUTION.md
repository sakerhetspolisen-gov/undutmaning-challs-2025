### Teknisk beskrivning

Utmanaren får källkoden för att spara tid.

Utmaningen låter användaren skapa små eller stora "raketer", objekt som hamnar på heapen. 
`SmallRocket` och `BigRocket` ärver båda från basklassen `BaseRocket`. Även `PrivilegedRocket`
ärver från samma basklass.

Programmet glömmer validera en sak som leder till en type confusion följt av heap overflow.

Utmanaren ska hitta buggen och använda denna för att skriva en exploit som 
leder till att `PrivilegedRocket::LaunchRocket` anropas.

### Lösningsförslag

`Rebuild`-alternativet i menyn låter en välja om man ska redigera en av sina stora eller små raketer.
Man kan välja att titta på `BigRocket`s men ändå välja indexet för en `SmallRocket`. Då 
cast:as en `SmallRocket`-pekare till en `BigRocket`-pekare vilket leder till en heap overflow.

Om man ser till att det finns en till "offer"-raket på heapen precis efter den som man utnyttjar buggen på, så kan 
man skriva över denna offer-raketens vtable-pekare.

Det behövs ingen extra bugg eller något extra exploaterande för att få en infoläcka eftersom
`edit`-funktionen skriver ut föregående värde för varje raketdel som man ändrar mått på.

När man (med heap-setup:en som används i `exploit.py`) redigerar måtten på "Vertical Tail height" och "Payload width" 
så läcker ena respektive andra hälften av adressen för offer-raketens vtable.
Man får då även skriva över dessa med vtable:et för PrivilegedRocket, vilken man kan räkna ut från läckan.

Kör man slutligen `Launch` på offer-raketen så kommer `PrivilegedRocket::LaunchRocket` anropas, och
flaggan spottas ut till stdout.
