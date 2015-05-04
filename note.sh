#!/bin/bash

TOOLCHAIN="/home/rogersb11/Desktop/toolchains/Linaro-a9-4.9.3/bin/arm-cortex_a9-linux-gnueabihf-"
STRIP="/home/rogersb11/Desktop/toolchains/Linaro-a9-4.9.3/bin/arm-cortex_a9-linux-gnueabihf-strip"
OUTDIR="/home/rogersb11/shifted/out"
BUILD="build"
CONFIG="cm_t0lte_defconfig"
KERNEL_DIR="/home/rogersb11/shifted"
CURRENTDATE=$(date +"%m-%d")


#echo "Cleaning..."
#		cd ${KERNEL_DIR}
#		make clean && make mrproper

	read -p "Clean working directory..(y/n)? : " achoice
	case "$achoice" in
		y|Y )
			rm -rf arch/arm/boot/zImage
			make clean && make mrproper
			echo "Working directory cleaned...";;
		n|N )
	esac

#echo "Making ramdisk..."
#		cd ${RAMDISK}
#		rm *.cpio
#		find . -not -name ".gitignore" | cpio -o -H newc > ${RAMDISK_OUT}

echo "Initial Build..."
		cd ${KERNEL_DIR}
		make ${CONFIG}
		make -j8 ARCH=arm CROSS_COMPILE=${TOOLCHAIN}


echo "Building Shift T0LTE Kernel..."
		cd ${KERNEL_DIR}
		make -j8 ARCH=arm CROSS_COMPILE=${TOOLCHAIN}
		cp arch/arm/boot/zImage ${BUILD}
		cd ${BUILD}
		echo "Compressing ramdisk..."
		# Make boot.img
		./mkbootimg --kernel zImage --ramdisk ramdisk.cpio.lzma --board smdk4x12 --base 0x10000000 --pagesize 2048 --ramdiskaddr 0x11000000 -o boot.img
		cp boot.img ${OUTDIR}
		cd ${OUTDIR}
		echo "Creating Shift CWM kernel zip..."
		zip -r Shift-3.9.zip ./ -x *.zip *.gitignore

echo "Done!"
