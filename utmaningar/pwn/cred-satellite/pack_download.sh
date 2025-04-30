#!/bin/bash

set -ex

rm -r ./download/*
cp ./src/* ./download/
cd ./download/
echo 'FLAG FOUND IN OUTER SPACE!' > ./flag.txt
echo 'qemu-system-x86_64 \
        -m 128M \
        -cpu kvm64,+smep,+smap \
        -kernel bzImage \
        -initrd initramfs.cpio.gz \
        -snapshot \
        -nographic \
        -monitor /dev/null \
        -no-reboot \
        -append "console=ttyS0 kaslr kpti=1 quiet panic=1"
' > ./run.sh
./decompress.sh
mv ./flag.txt ./initramfs
./compress.sh
cd ../
tar --remove-files -zcf cred-satellite.tar.gz ./download/*
mv cred-satellite.tar.gz ./download/

