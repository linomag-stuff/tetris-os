#!/bin/bash
set -e

echo "Doing some magic stuff..."
gcc -static -o initramfs_root/init init.c

echo "Even more coding magic..."
cd initramfs_root
find . | cpio -o -H newc | gzip > ../iso/isolinux/initramfs.cpio.gz
cd ..

echo "Tracking your location... (just kidding)"
xorriso -as mkisofs \
    -b isolinux/isolinux.bin \
    -c isolinux/boot.cat \
    -no-emul-boot \
    -boot-load-size 4 \
    -boot-info-table \
    -o output.iso iso/

echo "Done! Your TetrisOS is ready"
