import argparse
import os
import pyshark
import uuid
from mettle import *
from Crypto.Cipher import AES
'''
Based on the work of https://0xdf.gitlab.io/2023/02/04/htb-response.html#meterpreter-traffic-decryption
'''


AES_KEY = b''

def xor(data, key):
    return b"".join([bytes([b ^ key[idx % len(key)]]) for idx, b in enumerate(data)])



def extract_http_file_data(pcap, dump_path):
    print(f'[+] Parsing pcap: {pcap}')

    try:
        packets = pyshark.FileCapture(args.pcap, display_filter='http.file_data')
    except Exception as e:
        print(f'[!] Error opening pcap {pcap}: {e}')


    files = {}
    eof = True
    currentFile = ""
    for packet in packets:
        # Meterpreter data is in http payload (http.file_data)
        try:
            if hasattr(packet.http, 'file_data'):
                http_data = bytes.fromhex(packet.http.file_data.replace(":",""))
                
                # Parse mettle header
                xor_header = http_data[:32]
                xor_key = xor_header[:4]
                header = xor(xor_header, xor_key)
                
                session_guid = header[4:20]
                enc_flag = int.from_bytes(header[20:24], "big")
                packet_len = int.from_bytes(header[24:28], "big")
                packet_type = int.from_bytes(header[28:32], "big")

                print(f'Frame: {packet.frame_info.number:<4} - key: {xor_key.hex()}\t Type: {TLV_PACKET_TYPES[packet_type]:<4}\t packet_len: {packet_len:<8}\t http_data: {len(http_data):<8}\t enc={ENCODERS.get(enc_flag,enc_flag):<6}\t session={uuid.UUID(bytes=session_guid)}')

                '''
                Meterpreter packet structure (http.file_data):

                0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                |  xor_key  |        session_guid                            |
                |............................................................| 
                |           |    enc_type   |    length    |      type       |
                |............................................................| 
                |                         AES IV                             |
                |............................................................| 
                |  TLV_LEN  |    TLV_TYPE   |                                |
                |...........................|           TLV_VALUE            | 
                |                                                            |
                |                                                            |
                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                '''

                tlv_data = xor(http_data[32:], xor_key)
                if enc_flag == 1 and AES_KEY != b'':
                    aes_iv = tlv_data[:16]
                    cipher = AES.new(AES_KEY, AES.MODE_CBC, iv=aes_iv)
                    tlv_data = cipher.decrypt(tlv_data[16:])

                # Meterpreter order is actually LTV (Length - Type - Value)
                i = 0
                while i < len(tlv_data):
                    l = int.from_bytes(tlv_data[i:i+4], "big")
                    
                    if i + l > len(tlv_data) or l == 0:
                        break

                    t = int.from_bytes(tlv_data[i+4:i+8], "big")
                    t_verbose = tlv_types.get(t, "UKNOWN_TYPE: " + str(t))

                    if t_verbose == "TLV_TYPE_COMMAND_ID":
                        v = cmd_ids[int.from_bytes(tlv_data[i+8:i+12], 'big')]
                    else:
                        v = tlv_data[i+8:i+l]

                    print(f'\tTLV: l={l:<8}\t t={t_verbose:<24}\t v={v if len(v) <= 32 else v[:32]}')


                    #The shitty code below is to extract files.
                    if t_verbose == "TLV_TYPE_COMMAND_ID" and v == "COMMAND_ID_CORE_CHANNEL_OPEN":
                        eof = False
                    elif t_verbose == "TLV_TYPE_COMMAND_ID" and v == "COMMAND_ID_CORE_CHANNEL_CLOSE":
                        eof = True

                    if not eof and t_verbose == "TLV_TYPE_FILE_PATH":
                        currentFile = v.rstrip(b"\x00").decode('utf-8')

                    if not eof and TLV_PACKET_TYPES[packet_type] == "RESP" and t_verbose == "TLV_TYPE_CHANNEL_DATA" and currentFile:
                        if currentFile in files:
                            old_data = files[currentFile]
                            files[currentFile] = old_data + v
                        else:
                            files[currentFile] = v

                    i += l

        except AttributeError:
            continue
    
    #Dump the files
    if dump_path and files:
        print(f'[+] Dumping {len(files)} file(s) found in pcap:')
        for fname, fdata in files.items():
            print(f'{fname}')
            output_path = os.path.join(dump_path,fname)
            with open(output_path, 'wb') as f:
                f.write(fdata)

    


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Meterpreter traffic decryptor")

    parser.add_argument(
        '--pcap',
        help="File containing sliver network traffic",
        required=True
    )

    parser.add_argument(
        '--aes',
        help="AES key from meterpreter process",
        required=False
    )

    parser.add_argument(
        '--dump',
        help="Extract files to path",
        required=False,
    )

    args = parser.parse_args()

    if args.dump:
        if not os.path.exists(args.dump):
            try:
                os.makedirs(args.dump)
                print(f'[+] Created output directory {args.dump}')
            except Exception as e:
                print(f'[!] Error creating output directory {args.dump}: {e}')
                exit(1)
        elif not os.path.isdir(args.dump):
            print(f'[!] Provided dump path {args.dump} is not a directory!')
            exit(1)


    if args.aes:
        AES_KEY = bytes.fromhex(args.aes)

    if args.pcap:
        extract_http_file_data(args.pcap, args.dump)

