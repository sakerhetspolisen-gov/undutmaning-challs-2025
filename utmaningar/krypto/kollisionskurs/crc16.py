def crc16_xmodem(data: bytes, poly: int = 0x1021) -> int:
    """
    Beräkna CRC16 med XMODEM-polynomet (0x1021).
    
    :param data: Data som en bytes-sträng.
    :param poly: Polynomet att använda för CRC16 (standard är 0x1021 för XMODEM).
    :return: CRC16-checksumman som ett heltal.
    """
    crc = 0x0000
    for byte in data:
        crc ^= (byte << 8)
        for _ in range(8):
            if crc & 0x8000:
                crc = (crc << 1) ^ poly
            else:
                crc = crc << 1
            crc &= 0xFFFF  # Mask för att hålla CRC inom 16 bitar
    return crc

def calculate_crc16(data) -> str:
    # Kontrollera om data är en sträng
    if isinstance(data, str):
        bytes_data = data.encode('utf-8')
    elif isinstance(data, (bytes, bytearray)):
        bytes_data = data
    else:
        raise TypeError("Input data must be a string or bytes")

    crc16_hash = crc16_xmodem(bytes_data)

    # Returnera CRC32 som hexadecimal sträng
    return f'{crc16_hash:04x}'