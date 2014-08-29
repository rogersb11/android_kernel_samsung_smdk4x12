#!/bin/bash

TOOLCHAIN="/home/brett/Desktop/toolchains/LinaroGCC/bin/arm-eabi-"
STRIP="/home/brett/Desktop/toolchains/LinaroGCC/bin/arm-eabi-strip"
OUTDIR="/home/brett/Desktop/out"
CONFIG="cm_t0lte_defconfig"
INITRAMS_SOURCE="/home/brett/Desktop/stweaks"
MODULES=("/home/brett/shifted/arch/arm/mvp/commkm/commkm.ko" "/home/brett/shifted/arch/arm/mvp/mvpkm/mvpkm.ko" "/home/brett/shifted/arch/arm/mvp/pvtcpkm/pvtcpkm.ko" "drivers/interceptor/vpnclient.ko" "drivers/net/wireless/bcmdhd/dhd.ko" "drivers/new/wireless/btlock/btlock.ko" "drivers/scsi/scsi_wait_scan.ko" "/home/brett/shifted/fs/cifs/cifs.ko")
KERNEL_DIR="/home/brett/shifted"
MODULES_DIR="/home/brett/Desktop/out/lib/modules"
CURRENTDATE=$(date +"%m-%d")


# check xml-config for "STweaks"-app
XML2CHECK="/home/brett/Desktop/stweaks/res/customconfig/customconfig.xml";
xmllint --noout $XML2CHECK;
if [ $? == 1 ]; then
	echo "xml-Error: $XML2CHECK";
	exit 1;
fi;

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


