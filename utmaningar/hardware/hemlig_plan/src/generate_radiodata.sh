#!/bin/bash

echo -n "MUSTpRot3ct8keyT" > ../buildoutputs/aes_key.bin
echo -n "initialvector371" > ../buildoutputs/aes_iv.bin
echo "Keys generated..."

echo -n "$(< flagspoilers/debug_info_p1.txt )" > ../buildoutputs/uart_msg.txt
echo "$(xxd -p ../buildoutputs/aes_key.bin)" >> ../buildoutputs/uart_msg.txt
echo "$(< flagspoilers/debug_info_p2.txt )" >> ../buildoutputs/uart_msg.txt
echo "UART msg generated..."

echo "$(< flagspoilers/radio_msg.txt )" > ../buildoutputs/plaintext.txt
echo $'\n' >> ../buildoutputs/plaintext.txt
echo "$(< flagspoilers/flag.txt )" >> ../buildoutputs/plaintext.txt
echo "$(< flagspoilers/radio_msg_end.txt )" >> ../buildoutputs/plaintext.txt
echo "Plaintext for radio generated..."

echo "Appying XOR Cipher"
python prepare_radiodata.py
echo "AES encrypting.."

openssl enc -aes-128-cbc -in ../buildoutputs/plaintext_xor -out ../buildoutputs/encrypted_raw -K $(xxd -p ../buildoutputs/aes_key.bin) -iv $(xxd -p ../buildoutputs/aes_iv.bin)

cat ../buildoutputs/aes_iv.bin ../buildoutputs/encrypted_raw > ../buildoutputs/encrypted_radio_msg

echo "Encrypted radio msg..."