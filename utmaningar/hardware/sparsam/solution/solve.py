import numpy as np
import matplotlib.pyplot as plt

"""
Med hjälp av Simple Power Analysis (SPA), en timing-attack,
kan bitarna i nyckel-exponenten läsas ut ur effekförbrukningen.
Varje varv i loopen görs en utskrift som syns tydligt som en
dipp. Avståndet mellan dippar beror starkt på om den nuvarande
exponentbiten är en nolla eller etta eftersom antingen en respektive
två multiplikationer utförs. Med andra ord, ett kort avstånd mellan
dippar ger en nolla och ett långt avstånd ger en etta av
nyckel-exponenten, från MSB till LSB.

Paul Kocher var först med att presentera den här attacken redan 1996:
https://paulkocher.com/doc/TimingAttacks.pdf
"""

# Läs in data från effektmätningen
with open('effektmätning.csv', 'r') as f:
    lines = f.readlines()[1:]
trace = np.zeros((len(lines),))
for i in range(len(lines)):
    trace[i] = float(lines[i].split(',')[1])

# Visa en graf över vår efterbehandlade signal
plt.plot(trace)

# Gå igenom hela signalen och mät avståndet mellan alla dippar
offsets = []
i = 42000 # Den mätpunkt där algoritmen tycks börja
threshold = 0.11
last_dipp = i
while i < 576600: # Till den mätpunkt där algoritmen slutar
    if trace[i] < threshold: # Dipp identifierad
        offsets.append(i-last_dipp)
        last_dipp = i
        plt.axvline(x=i, color='red') # Rita ut var en dipp identifierades
        i += 400 # Gör ett hopp
    else:
        i += 1

# Visa vår graf och skriv ut de identifierade avstånden
plt.show()
print(offsets)
print(len(offsets)) # 512bitar - antal_indledande_nollor - den_inledande_ettan

# Konvertera avstånden till bitar av exponenten
#   Kort: bit = 0 (bara kvadrering)
#   Lång: bit = 1 (kvadrering och multiplicering)
# Här måste vi ta hänsyn till att första biten av exponenten är en etta. De
# inledande nollorna kommer inte att synas då varken kvadrering eller
# multiplicering utförs. Den första ettan kommer att vara jättekort då
# ingen kvadrering utförs och multipliceringen blir mycket snabb då den ena
# faktorn är 1.
# Utförande:
#   Inledande nollor        : ingenting
#   Första ettan            : kort multiplicering
#   Alla efterföljande bitar:
#                   Nolla   : kvadrering (kort)
#                   Etta    : kvadrering och multiplicering (lång)
exponent = 1 # Första biten är en etta
for offset in offsets:
    if offset >= 1000: # Kvadrering och multiplicering
        exponent = (exponent << 1) | 1 # Skifta in en etta
    else: # Kvadrering
        exponent <<= 1 # Skifta in en nolla

print(bin(exponent))
print(hex(exponent))

# Dekryptera flaggan
enc_flag = open('flagga.enc', 'rb').read()
modulus = 0x83398ec472e8b8716c244db4836bbd5c66895bfd1088e1bd97b64c7c162bfab57c99cac03e1b47a67b20de364d75330e2badb5727081cd254666d6eec782b41b
flag = pow(int.from_bytes(enc_flag), exponent, modulus).to_bytes(64, 'big').decode()
print(flag)
