#!/bin/bash

TOOLCHAIN="/home/brett/Desktop/toolchains/LinaroGCC/bin/arm-eabi-"
STRIP="/home/brett/Desktop/toolchains/LinaroGCC/bin/arm-eabi-strip"
OUTDIR="/home/brett/Desktop/out"
CONFIG="cm_t0ltecdma_defconfig"
MODULES=("/home/brett/shifted/arch/arm/mvp/commkm/commkm.ko" "/home/brett/shifted/arch/arm/mvp/mvpkm/mvpkm.ko" "/home/brett/shifted/arch/arm/mvp/pvtcpkm/pvtcpkm.ko" "drivers/interceptor/vpnclient.ko" "drivers/net/wireless/bcmdhd/dhd.ko" "drivers/new/wireless/btlock/btlock.ko" "drivers/scsi/scsi_wait_scan.ko" "/home/brett/shifted/fs/cifs/cifs.ko")
KERNEL_DIR="/home/brett/shifted"
MODULES_DIR="/home/brett/Desktop/out/lib/modules"
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
		zip -r Shift-4.8-CM.zip ./ -x *.zip *.gitignore

echo "Done!"
