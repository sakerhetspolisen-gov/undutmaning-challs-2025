#!/usr/bin/python3
from pwn import *
from binascii import hexlify, unhexlify
import hashlib

flag = 'undut{yyya_sn00ze_ya_l0z3}'
hashes=[]

print("md5(flag[i]):")
for idx,b in enumerate(flag):
    h = hashlib.md5(str(b).encode()).hexdigest()
    hashes.append(int(h,16))
    print(hex(int(h,16)))

print("\n\n// 0 - md5(flag[i]) & 0xffffffff :")
print('uint32_t thing[26] = {')
for h in hashes:
    print("    0x%08x," % ((0-h) & 0xffffffff))
print('}')
