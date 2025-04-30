#!/usr/bin/env python3

# Change this
REALPASS = "SanguineBrother"
PASSFILE = "realpassword.h"

realpass = []
reallen = len(REALPASS)

for i in range(reallen):
    tmp = (ord(REALPASS[i]) + (2 << (i%3))) % 0x100
    tmp ^= 0x80
    realpass.append(tmp)

file = open(PASSFILE, "w")
file.write("#define REALPASSWORD {")
file.write( ", ".join([f"0x{x:02x}" for x in realpass]) )
file.write("}\n")
file.write(f"#define REALPASSLEN {reallen}\n")
file.close()