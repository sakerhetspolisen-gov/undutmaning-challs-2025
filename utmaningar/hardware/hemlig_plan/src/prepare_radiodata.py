# Apply the XOR Cipher on plaintext radiodata (before AES)
from uart_sim import encrypt_XOR
from pathlib import Path

def prepare():
    current_dir = Path(__file__).parent
    file_path_in = current_dir / ".." / "buildoutputs" / "plaintext.txt"
    plaintext_file = file_path_in.resolve()

    with open(plaintext_file, "r") as plaintext:
        plaintext_str = plaintext.read()

    xor_key = 0x67
    xor_plaintext = encrypt_XOR(plaintext_str, xor_key)

    return xor_plaintext

if __name__ == "__main__":
    xor_plaintext = prepare()
    current_dir = Path(__file__).parent
    file_path_out = current_dir / ".." / "buildoutputs" / "plaintext_xor"
    xor_plaintext_file = file_path_out.resolve()

    with open(xor_plaintext_file, "w") as fout:
        fout.write(xor_plaintext)