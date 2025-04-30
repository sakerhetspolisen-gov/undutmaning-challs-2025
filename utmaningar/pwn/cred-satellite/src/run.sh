#!/bin/bash

KERNEL_IMG=./bzImage
INITRD=./initramfs.cpio.gz

tmpdir=$(/usr/bin/mktemp -d)
cd $tmpdir

# Make a unique file system for each connection 
cp /home/ctf/decompress.sh .
cp /home/ctf/compress.sh .
cp /home/ctf/initramfs.cpio.gz .
cp /home/ctf/bzImage .
cp /home/ctf/flag.txt .

# Allow connections supply a file
echo "Enter a URL to your exploit binary:"
read -t 30 -p "" url

# Add the supplied file to the file system
curl --proto-default https --proto -all,https,+http --max-filesize 10M -o exploit "$url" >/dev/null
chmod 777 ./exploit >/dev/null 2>&1
sleep 1 >/dev/null 2>&1
./decompress.sh >/dev/null 2>&1
rm intramfs/exploit 2> /dev/null
cp ./exploit initramfs/ >/dev/null 2>&1 
./compress.sh > /dev/null 2>&1


# Start VM with a timeout
timeout --foreground 30s qemu-system-x86_64 \
        -m 128M \
        -cpu kvm64,+smep,+smap \
        -kernel $KERNEL_IMG \
        -initrd $INITRD \
        -snapshot \
        -nographic \
        -monitor /dev/null \
        -no-reboot \
        -append "console=ttyS0 kaslr kpti=1 quiet panic=1"

# Cleanup
cd ../
rm -rf $tmpdir
