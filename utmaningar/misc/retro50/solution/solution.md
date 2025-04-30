Install fuse-emulator to emulate ZX Spectrum computer (hinted by Clive Sinclair).

Start emulator, click "File" and "Open" challenge.wav (will read as if it was a cassette tape).

Press enter to load it, should now display a program in BASIC.

In the emulator, press "R" and "ENTER" to run the BASIC program.

It will print numbers, 16-bit numbers (not ASCII).

Copy these numbers.


numbers: [21174, 8720, 37172, 20200, 15160, 31221, 5240, 14960, 1623, 2325, 13421, 30628, 859, 8003, 13001, 32003, 24165, 1470, 54077, 59188]

Hint "Ken Olsen", this is 16-bit DEC Radix-50 (base 40) encoding instead of ascii https://en.wikipedia.org/wiki/DEC_RADIX_50#16-bit_systems

The alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ$.%0123456789"

```py
def decode_radix50(integers):
    """
    Decodes a list of 16-bit integers using DEC RADIX 50 to a string.

    Parameters:
    integers (list): A list of 16-bit integers to be decoded.

    Returns:
    str: The decoded string.
    """
    alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ$.%0123456789"
    decoded_string = ""

    for integer in integers:
        # Extract the three characters from the integer
        char1 = integer // 40**2
        char2 = (integer % 40**2) // 40
        char3 = integer % 40

        # Append the characters to the decoded string
        decoded_string += alphabet[char1] + alphabet[char2] + alphabet[char3]

    # Remove trailing spaces
    decoded_string = decoded_string.rstrip()

    return decoded_string

# Run code:
integers = [21174, 8720, 37172, 20200, 15160, 31221, 5240, 14960, 1623, 2325, 13421, 30628, 859, 8003, 13001, 32003, 24165, 1470, 54077, 59188]
print(decode_radix50(integers))
```

Flag: "MINER WILLY IS STUCK IN A WAREHOUSE. USE CHEAT CODE 6031769."
