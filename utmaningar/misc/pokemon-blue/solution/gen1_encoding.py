#!/usr/bin/python3

import string
import argparse

def ascii2gen1(s: str) -> str:
    r: str = 'db $00, '
    for i, c in enumerate(s.upper()):
        x = f'${hex(encoding[c])[2:]}, '
        if i != 0 and i % 17 == 0:
            r += '$51\ndb ' + x
        else:
            r += x

    r = r[:-2] + ', $57'
    return r

def gen12ascii(s: str) -> str:
    e = {v: k for k, v in encoding.items()}
    return ''.join([e[int(x.strip(', $'), 16)] for x in s.split(',')])

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-e', '--encode', type=str)
    parser.add_argument('-d', '--decode', type=str)

    encoding: dict[str, int] = {'␀': 0, ' ': 0x7f, '1': 0xf7, '-': 0xe3, '(': 0x9A, ')': 0x9b, ':': 0x9c, 'END': 0x57, '▶': 0x51}

    i: int = 0x80
    for c in string.ascii_uppercase:
        encoding[c] = i
        i += 1
    args: list[str] = parser.parse_args()
    print(ascii2gen1(args.encode)) if args.encode else print(gen12ascii(args.decode))
