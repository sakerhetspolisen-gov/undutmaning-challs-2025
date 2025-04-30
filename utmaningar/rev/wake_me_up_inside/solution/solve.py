#!/usr/bin/python3
import hashlib
from string import printable

# The array found in the binary
terms=[
    0xb0de2cb4,
    0x4cec9c5f,
    0xe91f6e53,
    0xb0de2cb4,
    0x949a9b62,
    0xca9bbafa,
    0x6fb0cba3,
    0x6fb0cba3,
    0x6fb0cba3,
    0x9688d99f,
    0xb319ffce,
    0xd3cf0fcc,
    0x4cec9c5f,
    0x06789b26,
    0x06789b26,
    0xf7bae229,
    0x17be13ce,
    0xb319ffce,
    0x6fb0cba3,
    0x9688d99f,
    0xb319ffce,
    0x4dfec4cd,
    0x06789b26,
    0xf7bae229,
    0x0d58450d,
    0x55fb6a31]

targets=[]

flag=""
for t in terms:
    for c in printable:
        h = int(hashlib.md5(str(c).encode()).hexdigest(),16)
        if (h+t)&0xffffffff == 0x0:
            flag+=c
            print(flag)
