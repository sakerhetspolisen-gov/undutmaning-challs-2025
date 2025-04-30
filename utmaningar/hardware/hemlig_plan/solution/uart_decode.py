# Funktioner för UART-dekodningen

def convert_raw_uart_to_data(filename: str, samples_per_sec, baudrate):
    samples_per_bit = samples_per_sec // baudrate
    mid_sample_offset = samples_per_bit // 2

    with open(filename, "rb") as data_file:
        raw_data = data_file.read()

    bitstream = ''.join('1' if byte !=0 else '0' for byte in raw_data)
    bit_length = len(bitstream)

    decoded_bytes = []  
    i = 0
    while i < bit_length:
        # Look for start bit (0)
        if bitstream[i] == '0':
            # Extract data bits, sampling in the middle
            data_bits = ''
            for j in range(1, 9): # 8 data bits
                sample_index = i + (j * samples_per_bit) + mid_sample_offset
                if sample_index < bit_length:
                    data_bits += bitstream[sample_index]
                else:
                    break

            stop_bit_index = i + int(9 * samples_per_bit) + mid_sample_offset
            if stop_bit_index < bit_length and bitstream[stop_bit_index] == '1':
                decoded_byte = int(data_bits[::-1], 2) # NOTE: LSB first!
                decoded_bytes.append(decoded_byte)

            i += int(10 * samples_per_bit)
        else:
            # Search for start bit
            i += 1
    decoded_text_b = bytes(decoded_bytes)

    return decoded_text_b

def decrypt_xor_cipher(text, key):
    # calculate length of input string 
    length = len(text); 
    # perform XOR operation of key 
    # with every character in string 
    for i in range(length): 
        text = (text[:i] + 
             chr(ord(text[i]) ^ key) +
                     text[i + 1:]);  
    return text 