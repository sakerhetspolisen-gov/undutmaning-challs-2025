import argparse
import sys
from pathlib import Path

# Lägg till parent-katalogen till sys.path
sys.path.append(str(Path(__file__).resolve().parent.parent))

from crc16 import calculate_crc16

def main():
    parser = argparse.ArgumentParser(description="Beräkna CRC16-checksumma för en fil.")
    parser.add_argument("file", help="Sökvägen till filen vars CRC16-checksumma ska beräknas.")
    args = parser.parse_args()

    try:
        with open(args.file, 'rb') as f:
            file_data = f.read()
        # Beräkna CRC16 med XMODEM-polik
        checksum = calculate_crc16(file_data)
        if checksum:
            print(f"CRC16 checksumma för filen '{args.file}' är: {checksum}")

    except FileNotFoundError:
        print(f"Filen '{args.file}' kunde inte hittas.")
        return None
    except Exception as e:
        print(f"Ett fel inträffade: {e}")
        return None

if __name__ == "__main__":
    main()
