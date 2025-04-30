import sys
import os
from pathlib import Path

def text_to_bytes(string_txt):
    return string_txt.encode("utf-8")

def encrypt_XOR(data_s: str, key: bytes):
    # calculate length of input string 
    length = len(data_s); 
  
    # perform XOR operation of key with
    # every character in string 
    for i in range(length): 
        data_s = (data_s[:i] + 
             chr(ord(data_s[i]) ^ key) +
                     data_s[i + 1:]);  
    return data_s; 

def byte_to_bits(value: bytes):
    '''
    Convert a byte to a list of 8 bits (LSB first)
    '''
    return [((value >> i) & 0x1) for i in range(8)]

def print_progress(current, total):
    '''
    Prints a simple progress bar
    '''
    percent = (current / total) * 100
    bar_length = 50 # Len in chars
    filled_len = int(bar_length * current // total)
    bar = '=' * filled_len + '-' * (bar_length - filled_len)
    sys.stdout.write(f"\r|{bar}| {percent:6.2f}%")
    sys.stdout.flush()

def generate_uart_waveform(data, baud=115200, sample_freq=691200):
    samples_per_bit_exact = sample_freq/baud
    samples_per_bit = int(round(samples_per_bit_exact))

    waveform = []
    for byte in data:
        # start bit
        waveform.extend([0]*samples_per_bit)

        bits = byte_to_bits(byte)

        for b in bits:
            waveform.extend([b]*samples_per_bit)

        waveform.extend([1]*samples_per_bit)

    return waveform, samples_per_bit

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 uart_sim.py <baud> <samp_freq>")
        sys.exit(1)

    current_dir = Path(__file__).parent
    file_path_in = current_dir / ".." / "buildoutputs" / "uart_msg.txt"
    input_file = file_path_in.resolve()
    file_path_out = current_dir / ".." / "buildoutputs" / "captured"
    output_file = file_path_out.resolve()
    baud = int(sys.argv[1])
    samp_freq = int(sys.argv[2])

    samples_per_bit_exact = samp_freq/baud
    samples_per_bit = int(round(samples_per_bit_exact))

    total_size = os.path.getsize(input_file)
    processed=0

    with open(input_file, "r") as fin, open(output_file, "wb") as fout:
        total_samples=0
        chunk_size=1024

        print("Processing...")

        while True:
            chunk = fin.read(chunk_size)

            # XOR Encryption
            xor_key = 0x67
            data = encrypt_XOR(chunk, xor_key)            
            data = text_to_bytes(data)

            if not chunk:
                break

            # Progress
            processed += len(data)
            print_progress(processed, total_size)

            for byte in data:
                # Start bit 0
                fout.write(bytes([0]*samples_per_bit))
                total_samples += samples_per_bit

                # Data bits (LSB first)
                bits = byte_to_bits(byte)
                for bit in bits:
                    fout.write(bytes([bit]*samples_per_bit))
                    total_samples += samples_per_bit
                
                # Stop bit 1
                fout.write(bytes([1]*samples_per_bit))
                total_samples += samples_per_bit

    sys.stdout.write('\n')
    
    print(f"Generated {output_file} with {total_samples} total samples.")
    

