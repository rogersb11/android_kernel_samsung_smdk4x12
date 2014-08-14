cmd_arch/arm/mvp/mvpkm/vfp_switch.o := /home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/arm-cortex_a9-linux-gnueabihf-gcc -Wp,-MD,arch/arm/mvp/mvpkm/.vfp_switch.o.d  -nostdinc -isystem /home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/../lib/gcc/arm-cortex_a9-linux-gnueabihf/4.7.4/include -I/home/brett/shifted/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-exynos/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float     -mfpu=neon -DLIB_ARM_VERSION=7 -DIN_MODULE -DGPLED_CODE -mfloat-abi=softfp   -DMODULE  -c -o arch/arm/mvp/mvpkm/vfp_switch.o arch/arm/mvp/mvpkm/vfp_switch.S

source_arch/arm/mvp/mvpkm/vfp_switch.o := arch/arm/mvp/mvpkm/vfp_switch.S

deps_arch/arm/mvp/mvpkm/vfp_switch.o := \
  /home/brett/shifted/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  arch/arm/mvp/mvpkm/arm_defs.h \
  arch/arm/mvp/mvpkm/include_check.h \
  arch/arm/mvp/mvpkm/coproc_defs.h \
  arch/arm/mvp/mvpkm/exc_defs.h \
  arch/arm/mvp/mvpkm/instr_defs.h \
  arch/arm/mvp/mvpkm/utils.h \
  arch/arm/mvp/mvpkm/mmu_defs.h \
  arch/arm/mvp/mvpkm/lpae_defs.h \
  arch/arm/mvp/mvpkm/ve_defs.h \
  arch/arm/mvp/mvpkm/psr_defs.h \
  arch/arm/mvp/mvpkm/platdefx.h \
  arch/arm/mvp/mvpkm/arm_as_macros.h \

arch/arm/mvp/mvpkm/vfp_switch.o: $(deps_arch/arm/mvp/mvpkm/vfp_switch.o)

$(deps_arch/arm/mvp/mvpkm/vfp_switch.o):
