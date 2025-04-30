#!/bin/sh
set -e

mkdir initramfs
cd initramfs
cp ../initramfs.cpio.gz .
gunzip ./initramfs.cpio.gz > /dev/null
cpio -idm < ./initramfs.cpio > /dev/null
rm initramfs.cpio
