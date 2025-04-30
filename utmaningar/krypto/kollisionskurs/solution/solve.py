import argparse
import itertools
import time
import sys
from pathlib import Path

# Lägg till parent-katalogen till sys.path
sys.path.append(str(Path(__file__).resolve().parent.parent))

from crc16 import calculate_crc16

def generate_colliding_script(target_checksum, commands, output_file="colliding_script.sh",max_padding=10):
    """
    Generera ett shellscript som har samma CRC16-checksumma som ett mål.
    
    :param target_checksum: CRC16 checksumman vi vill matcha.
    :param commands: Kommandon som ska köras i det genererade skriptet.
    :param output_file: Namn på den genererade filen.
    """
    base_script = "#!/bin/bash\n" + "\n".join(commands)
    readable_chars = ''.join(chr(c) for c in range(32, 127))  # ASCII läsbara tecken (32-126)

    print(f"Försöker generera skript matchande: {target_checksum}")

    start_time = time.time()

    for length in range(1, max_padding):  # Testa olika längder för paddingen
        print(f"Försöker med padding av längd {length}...")
        for padding_tuple in itertools.product(readable_chars, repeat=length):
            # Generera paddingen som en sträng
            padding = ''.join(padding_tuple)

            test_script = base_script + "\n# Padding: " + padding
            
            # Beräkna checksumma
            crc = calculate_crc16(test_script)
            
            if crc == target_checksum:
                # Spara det genererade scriptet
                with open(output_file, "w") as f:
                    f.write(test_script)
                print(f"Matchande script genererat och sparat som {output_file}")
                print(f"Padding använd: {padding}")
                end_time = time.time()  # Sluta tidsräknaren
                print(f"Tid: {end_time - start_time:.2f} sekunder.")
                return
            
    print("Kunde inte generera ett script med matchande checksumma.")
    end_time = time.time()  # Sluta tidsräknaren
    print(f"Tid: {end_time - start_time:.2f} sekunder.")

def main():
    parser = argparse.ArgumentParser(description="Generera ett shellscript som matchar en given CRC16-checksumma.")
    parser.add_argument(
        "-c", "--checksum",
        help="CRC16-checksumma som det genererade scriptet ska matcha.",
        type=str
    )
    parser.add_argument(
        "-f", "--file",
        help="Fil vars CRC16-checksumma ska matchas.",
        type=str
    )
    parser.add_argument(
        "-o", "--output",
        help="Filnamn för det genererade scriptet (standard: colliding_script.sh).",
        default="colliding_script.sh",
        type=str
    )
    parser.add_argument(
        "-m", "--max-padding",
        help="Maximal längd för paddingen (standard: 64).",
        default=64,
        type=int
    )
    parser.add_argument(
        "commands",
        nargs="+",
        help="Kommandon att inkludera i det genererade scriptet."
    )

    args = parser.parse_args()

    # Kontrollera om antingen checksumma eller fil är angiven
    if not args.checksum and not args.file:
        parser.error("Du måste ange antingen --checksum eller --file.")

    # Beräkna checksumma från fil om en fil är angiven
    if args.file:
        with open(args.file, "rb") as f:
            target_checksum = calculate_crc16(f.read())
    else:
        target_checksum = args.checksum

    # Generera det matchande scriptet
    generate_colliding_script(target_checksum, args.commands, args.output, args.max_padding)


if __name__ == "__main__":
    main()
