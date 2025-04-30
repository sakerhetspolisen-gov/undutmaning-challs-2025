# Generate an encrypted flag
# Needs to both be saved as flagga.enc and copied into dekryptera.ino

BITS = 512

# Save keys
with open('keys.txt', 'r') as f:
    for line in f.readlines():
        if 'n = ' in line:
            n = int(line.lstrip("n = ").strip(), 16)
        elif 'e = ' in line:
            e = int(line.lstrip("e = ").strip(), 16)

# Encrypt flag
x = b'undut{d3n_s0m_SPAr_h3n_h4r_s4_d3n_spaRSAmm3}'
assert len(x) <= (BITS // 8)
c = pow(int.from_bytes(x), e, n)
print('!!! Copy this to "dekryptera.ino" !!!')
print('BigInt base = { %s }\n' % ', '.join([('0x%04x' % ((c >> i*16) & 0xffff)) for i in range(BITS // 16)]))

# Save encrypted flag
with open('flagga.enc', 'wb') as f:
    f.write(c.to_bytes(BITS // 8))
print('Encrypted flag also saved as "flagga.enc"')
