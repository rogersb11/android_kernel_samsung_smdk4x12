cmd_arch/arm/mach-exynos/exynos4-smc.o := /home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/arm-cortex_a9-linux-gnueabihf-gcc -Wp,-MD,arch/arm/mach-exynos/.exynos4-smc.o.d  -nostdinc -isystem /home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/../lib/gcc/arm-cortex_a9-linux-gnueabihf/4.7.4/include -I/home/brett/shifted/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-exynos/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -DREQUIRES_SEC=1    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(exynos4_smc)"  -D"KBUILD_MODNAME=KBUILD_STR(exynos4_smc)" -c -o arch/arm/mach-exynos/.tmp_exynos4-smc.o arch/arm/mach-exynos/exynos4-smc.c

source_arch/arm/mach-exynos/exynos4-smc.o := arch/arm/mach-exynos/exynos4-smc.c

deps_arch/arm/mach-exynos/exynos4-smc.o := \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/brett/shifted/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /home/brett/shifted/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/brett/shifted/arch/arm/include/asm/posix_types.h \
  arch/arm/mach-exynos/include/mach/smc.h \

arch/arm/mach-exynos/exynos4-smc.o: $(deps_arch/arm/mach-exynos/exynos4-smc.o)

$(deps_arch/arm/mach-exynos/exynos4-smc.o):
