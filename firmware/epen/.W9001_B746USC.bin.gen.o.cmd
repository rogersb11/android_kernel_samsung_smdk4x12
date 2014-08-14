cmd_firmware/epen/W9001_B746USC.bin.gen.o := /home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/arm-cortex_a9-linux-gnueabihf-gcc -Wp,-MD,firmware/epen/.W9001_B746USC.bin.gen.o.d  -nostdinc -isystem /home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/../lib/gcc/arm-cortex_a9-linux-gnueabihf/4.7.4/include -I/home/brett/shifted/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-exynos/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float        -c -o firmware/epen/W9001_B746USC.bin.gen.o firmware/epen/W9001_B746USC.bin.gen.S

source_firmware/epen/W9001_B746USC.bin.gen.o := firmware/epen/W9001_B746USC.bin.gen.S

deps_firmware/epen/W9001_B746USC.bin.gen.o := \
  /home/brett/shifted/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \

firmware/epen/W9001_B746USC.bin.gen.o: $(deps_firmware/epen/W9001_B746USC.bin.gen.o)

$(deps_firmware/epen/W9001_B746USC.bin.gen.o):
