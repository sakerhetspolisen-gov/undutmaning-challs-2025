#!/usr/bin/python3
# python3 -m pip install z3-solver
from z3 import Solver, BitVec, Or, sat

s = Solver()
cs = [BitVec(f'n{i}', 8) for i in range(16)]
for c in cs:
    s.add(Or(*(c == ord(x) for x in 'abcdefghijklmnopqrstuvwxyz0123456789')))
s.add(cs[5]  - cs[3]  <  -4)
s.add(cs[11] - cs[0]  == -5)
s.add(cs[4]  ^ cs[12] == 2)
s.add(cs[13] ^ cs[1]  == 19)
s.add(cs[10] | cs[1]  == 126)
s.add(cs[7]  | cs[4]  == 108)
s.add(cs[15] ^ cs[6]  == 16)
s.add(cs[8]  ^ cs[9]  == 9)
s.add(cs[2]  + cs[11] == 226)
s.add(cs[14] - cs[3]  == -5)
s.add(cs[8]  | cs[7]  == 125)
s.add(cs[3]  + cs[11] <  226)
s.add(cs[5]  ^ cs[9]  == 8)
s.add(cs[11] | cs[10] == 111)
s.add(cs[1]  ^ cs[3]  == 2)
s.add(cs[12] ^ cs[2]  == 25)
s.add(cs[9]  ^ cs[15] == 26)

assert s.check() == sat
m = s.model()
print(''.join(chr(m[c].as_long()) for c in cs))

# only one valid solution
s.add(Or(*(c != m[c].as_long() for c in cs)))
assert s.check() != sat