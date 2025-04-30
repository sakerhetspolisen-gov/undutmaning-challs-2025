# Teknisk beskrivning

Utmaningen utgörs av en kryptonyckel och en kryptotext. Utmaningen består i att identifiera att en publika nyckeln
använder en eliptisk kurva som innehåller för få bitar för att vara säker. Detta gör att man kan knäcka den hyffsat
enkelt och få tag i den privata nyckeln. Då man fått fram den privata nyckeln måste man lista ut att lösenordet
"gömmer sig" i den för att sedan dekryptera kryptotexten och få fram flaggan.

# Komponenter

## EC Public Key

    The supplied curve has too few bits to be secure (but is a complete subgroup).

>    $ openssl ec -in challenge.txt -pubin -text
>    pub:   04:22:8d:ef:34:fe:c0:cf:56
>    Prime: 4294964981 (0xfffff6f5)
>    A:     1199244169 (0x477b0389)
>    B:     842874427 (0x323d3e3b)
>    G:     04:6f:c9:72:39:56:b4:b0:74
>    Order: 4294946489 (0xffffaeb9)
>
>    SageMath:
>    sage: p = 0xfffff6f5
>    ....: a = 0x477b0389
>    ....: b = 0x323d3e3b
>    ....: E = EllipticCurve(GF(p), [a, b])
>    ....: G=E([0x6fc97239, 0x56b4b074])
>    ....: priv=0xf11ec0de
>    ....: pub=priv*G
>    ....: factor(E.order())
>    ....: factor(G.order())
>    ....: hex(pub[0]), hex(pub[1])

## AES-256-CBC data

    This is the encrypted flag, encrypted using OpenSSL in AES-256-CBC mode.

>    $ echo U2FsdGVkX1/+1FFQXzvk06+lLUwuPAGTK+05iZN1HuZH0pqsx5QM7v/TmJ3rlT3h2EG15Ff9JFWGYnCfKs7Xzsjfuhi90m2PaJEhXntaRhk= \
>    | base64 -d | tee encrypted.raw | hd
>    00000000  53 61 6c 74 65 64 5f 5f  fe d4 51 50 5f 3b e4 d3  |Salted__..QP_;..|
>    00000010  af a5 2d 4c 2e 3c 01 93  2b ed 39 89 93 75 1e e6  |..-L.<..+.9..u..|
>    00000020  47 d2 9a ac c7 94 0c ee  ff d3 98 9d eb 95 3d e1  |G.............=.|
>    00000030  d8 41 b5 e4 57 fd 24 55  86 62 70 9f 2a ce d7 ce  |.A..W.$U.bp.*...|
>    00000040  c8 df ba 18 bd d2 6d 8f  68 91 21 5e 7b 5a 46 19  |......m.h.!^{ZF.|
>    $ file encrypted.raw
>    encrypted.raw: openssl enc'd data with salted password


# Lösning

## Knäck EC nyckeln

    Write a brute-force private key cracker probably using a fast language
    like C/C++, Rust, or similar. Example in solution/crack.c, cracking takes about
    5-20 minutes to run on a fast PC.

    The private key is revealed to be `0xf11ec0de`

## Dekryptera flaggan

    To decrypt the flag, the participant needs to realize that 0xf11ec0de is
    isomorphic to the word "filecode". This step prevents the participant from 
    just brute-force cracking the flag directly. 

    The file is clearly encrypted using OpenSSL in AES-256-CBC mode. Putting this
    together, you can decrypt the flag using:

    `openssl aes-256-cbc -d -in encrypted.raw -pass pass:filecode`

    Producting the flag.

# Flaggan

    `undut{CurveBall_02abd2b7e068f024a930ff2b6f8ede05}`


