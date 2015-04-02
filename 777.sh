#!/bin/bash

TOOLCHAIN="/home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/arm-cortex_a9-linux-gnueabihf-"
STRIP="/home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/arm-gnueabi-strip"
OUTDIR="out2"
CONFIG="cyanogenmod_i777_defconfig"
LP_INITRAMFS_SOURCE="/home/brett/shifted/usr/initramfs/i777.list"
RAMDISK="/home/brett/shifted/ramdisk"
RAMDISK_OUT="/home/brett/shifted/usr/initramfs/ramdisk.cpio"
MODULES=("/home/brett/shifted/net/sunrpc/auth_gss/auth_rpcgss.ko" "/home/brett/shifted/fs/cifs/cifs.ko" "drivers/net/wireless/bcmdhd/dhd.ko" "/home/brett/shifted/fs/lockd/lockd.ko" "/home/brett/shifted/fs/nfs/nfs.ko" "/home/brett/shifted/net/sunrpc/auth_gss/rpcsec_gss_krb5.ko" "drivers/scsi/scsi_wait_scan.ko" "drivers/samsung/fm_si4709/Si4709_driver.ko" "/home/brett/shifted/net/sunrpc/sunrpc.ko")
KERNEL_DIR="/home/brett/shifted"
MODULES_DIR="/home/brett/shifted/usr/galaxys2_initramfs_files/modules"
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
		make -j8 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${LP_INITRAMFS_SOURCE}
		cp arch/arm/boot/zImage ${OUTDIR}
		cd ${OUTDIR}
		echo "Creating Shift CWM kernel zip..."
		zip -r Shift-ETERNAL.zip ./ -x *.zip *.gitignore

#echo "Building TWRP Kernel..."
#		cd ${KERNEL_DIR}
#		make -j8 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${KK_TWRP_INITRAMFS_SOURCE}
#		cp arch/arm/boot/zImage ${OUTDIR}
#		cd ${OUTDIR}
#		echo "Creating Shift TWRP kernel zip..."
#		zip -r Shift-4.1-TWRP.zip ./ -x *.zip *.gitignore

#echo "Building Slim Kernel..."
#		cd ${KERNEL_DIR}
#		make -j8 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${SK_TWRP_INITRAMS_SOURCE}
#		cp arch/arm/boot/zImage ${OUTDIR}
#		cd ${OUTDIR}
#		echo "Creating Slim TWRP kernel zip..."
#		zip -r Shift-4.8-Slim.zip ./ -x *.zip *.gitignore

echo "Done!"
