#!/usr/bin/env python3

from Crypto.Cipher import AES

def decrypt_aes128_cbc(ciphertext: bytes, key: bytes, iv: bytes) -> bytes:
    """Decrypt data using AES-128 in CBC mode

    Args:
        ciphertext (bytes): msg to decrypt
        key (bytes): AES key
        iv (bytes): IV

    Returns:
        bytes: Decrypted text
    """
    ## ---- Type Checks ---
    if not isinstance(ciphertext, bytes):
        raise TypeError("ciphertext must be of type 'bytes'")
    if not isinstance(key, bytes):
        raise TypeError("key must be of type 'bytes'")
    if not isinstance(iv, bytes):
        raise TypeError("iv must be of type 'bytes'")
    
    ## ---- Length check ---
    if len(key) != 16:
        raise ValueError(f"AES-128 key must be 16 bytes, got {len(key)} bytes")
    if len(iv) != 16:
        raise ValueError(f"AES iv must be 16 bytes, got {len(iv)} bytes")

    ## Decrypt
    try:
        cipher = AES.new(key, AES.MODE_CBC, iv)
        decrypted_data = cipher.decrypt(ciphertext)
    except Exception as e:
        raise ValueError(f"Error during AES decryption: {e}")
    
    return decrypted_data
