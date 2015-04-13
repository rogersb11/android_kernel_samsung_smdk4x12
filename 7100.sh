#!/bin/bash

TOOLCHAIN="/home/rogersb11/Desktop/toolchains/linaro-4.9.3/bin/arm-eabi-"
STRIP="/home/rogersb11/Desktop/toolchains/linaro-4.9.3/bin/arm-eabi-strip"
OUTDIR="/home/rogersb11/shifted/out2"
CONFIG="cyanogenmod_n7100_defconfig"
MODULES=("/home/rogersb11/shifted/arch/arm/mvp/commkm/commkm.ko" "/home/rogersb11/shifted/arch/arm/mvp/mvpkm/mvpkm.ko" "/home/rogersb11/shifted/arch/arm/mvp/pvtcpkm/pvtcpkm.ko" "drivers/net/wireless/bcmdhd/dhd.ko" "drivers/scsi/scsi_wait_scan.ko" "/home/rogersb11/shifted/fs/cifs/cifs.ko")
KERNEL_DIR="/home/rogersb11/shifted"
MODULES_DIR="/home/rogersb11/shifted/out2/system/lib/modules"
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

echo "Building Modules..."
		make -j8 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} modules

	for module in "${MODULES[@]}" ; do
			cp "${module}" ${MODULES_DIR}
			${STRIP} --strip-unneeded ${MODULES_DIR}/*
	done

echo "Building CWM Kernel..."
		cd ${KERNEL_DIR}
		make -j8 ARCH=arm CROSS_COMPILE=${TOOLCHAIN}
		cp arch/arm/boot/zImage ${OUTDIR}
		cd ${OUTDIR}
		echo "Creating Shift CWM kernel zip..."
		zip -r Shift-LP-5.2-N7100.zip ./ -x *.zip *.gitignore

echo "Done!"
