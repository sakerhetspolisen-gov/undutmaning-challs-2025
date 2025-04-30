#!/bin/sh
set -e

# Pack initramfs 
cd initramfs/
find . -print0 \
| cpio --null -ov --format=newc \
| gzip -9 > initramfs.cpio.gz
mv initramfs.cpio.gz ../
cd ..
rm -r initramfs
