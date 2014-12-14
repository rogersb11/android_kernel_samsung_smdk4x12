#!/bin/bash

RAMDISK="/home/brett/kern/usr/initramfs/ramdisk"
RAMDISK_OUT="/home/brett/kern/usr/initramfs/ramdisk.cpio"
RAMDISK_PATH=$PWD


echo "Making ramdisk..."
		cd ${RAMDISK}
		find . -not -name ".gitignore" | cpio -o -H newc > ${RAMDISK_OUT}

echo "Done!"

