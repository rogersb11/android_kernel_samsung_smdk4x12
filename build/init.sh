#!/bin/bash

RAMDISK="/home/brett/shifted/build/ramdisk"
RAMDISK_OUT="/home/brett/shifted/build/ramdisk.cpio"
RAMDISK_PATH=$PWD


echo "Making ramdisk..."
		cd ${RAMDISK}
		find . -not -name ".gitignore" | cpio -o -H newc > ${RAMDISK_OUT}
		cd ${RAMDISK_PATH}
		rm ramdisk.cpio.lzma
		find . -not -name ".gitignore" | lzma ramdisk.cpio

echo "Done!"

