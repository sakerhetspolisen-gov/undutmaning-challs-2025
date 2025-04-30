from decrypt_data import *
from uart_decode import *
from pathlib import Path

if __name__ == "__main__":
    # Från den givna bilden får vi följande:
    baudrate     = 115200
    sps          = 691200 # samples per sec

    # Från databladet och beskrivningen förstår vi att det är data över UART som
    # har skickats
    current_dir  = Path(__file__).parent
    file_path    = current_dir / ".." / "download" / "captured"
    filename     = file_path.resolve()
    decoded_data = convert_raw_uart_to_data(filename, sps, baudrate)
    decoded_data = decoded_data.decode("utf-8")
    print("------------ UART output ------------")
    print(decoded_data)

    #  Vi ser också att datan är krypterad och nyckeln och krypteringsmetod fås fram
    #  med info från databladet, dekrypteras detta så ges info som ger en AES-nyckel.
    #  Infon som ges är debugginfo om enheten som har getts av att inspelningen sker 
    #  i debugmode
    xor_key = 0x67
    print("------------ UART output after XOR with XOR key ------------")
    text = decrypt_xor_cipher(decoded_data, xor_key)
    print(text)

    assert decoded_data != text, "xor decrypt did not work for UART decode" 

    # Med den funna AES-nyckeln kan vi dekryptera den andra givna datan och därmed få flaggan
    print("--------------- AES key -------------------- \n\n\n")
    aes_key_input = input("Write the AES Key: ") # Hittas i texten från tidigare meddelande
    aes_key_bytes = bytes.fromhex(aes_key_input)
    
    # Plocka ut IV och ciphertext ur radio_data
    file_path = current_dir / ".." / "download" / "encrypted_radio_msg"
    filename = file_path.resolve()
    with open(filename, "rb") as f:
        iv = f.read(16)
        ciphertext = f.read()

    xor_data = decrypt_aes128_cbc(ciphertext, aes_key_bytes, iv)
    print("------------ Decrypted AES before XOR ------------")
    print(xor_data.decode("utf-8"))

    # Extra steg pga XOR Cipher
    xor_data_decoded = xor_data.decode("utf-8")
    plaintext = decrypt_xor_cipher(xor_data_decoded, xor_key)
    assert plaintext != xor_data, "xor decrypt did not work" 

    print("--------------- Den hemliga planen är: --------------------")
    print(plaintext)

