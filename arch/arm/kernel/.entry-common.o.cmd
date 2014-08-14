cmd_arch/arm/kernel/entry-common.o := /home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/arm-cortex_a9-linux-gnueabihf-gcc -Wp,-MD,arch/arm/kernel/.entry-common.o.d  -nostdinc -isystem /home/brett/Desktop/toolchains/arm-cortex_a9-linux-gnueabihf-linaro_4.7.4-2014.01/bin/../lib/gcc/arm-cortex_a9-linux-gnueabihf/4.7.4/include -I/home/brett/shifted/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-exynos/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float        -c -o arch/arm/kernel/entry-common.o arch/arm/kernel/entry-common.S

source_arch/arm/kernel/entry-common.o := arch/arm/kernel/entry-common.S

deps_arch/arm/kernel/entry-common.o := \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/function/tracer.h) \
    $(wildcard include/config/old/mcount.h) \
    $(wildcard include/config/frame/pointer.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/dynamic/ftrace.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/oabi/compat.h) \
    $(wildcard include/config/arm/thumb.h) \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/aeabi.h) \
    $(wildcard include/config/alignment/trap.h) \
    $(wildcard include/config/seccomp.h) \
  /home/brett/shifted/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /home/brett/shifted/arch/arm/include/asm/unistd.h \
  /home/brett/shifted/arch/arm/include/asm/ftrace.h \
    $(wildcard include/config/arm/unwind.h) \
  arch/arm/mach-exynos/include/mach/entry-macro.S \
    $(wildcard include/config/arch/exynos4.h) \
    $(wildcard include/config/arm/trustzone.h) \
  arch/arm/mach-exynos/include/mach/hardware.h \
  /home/brett/shifted/arch/arm/include/asm/hardware/gic.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  arch/arm/mach-exynos/include/mach/map.h \
    $(wildcard include/config/arch/exynos5.h) \
  arch/arm/plat-samsung/include/plat/map-base.h \
    $(wildcard include/config/s3c/base/addr.h) \
    $(wildcard include/config/s3c/addr/base.h) \
  arch/arm/plat-s5p/include/plat/map-s5p.h \
  arch/arm/mach-exynos/include/mach/map-exynos4.h \
    $(wildcard include/config/cpu/exynos4210.h) \
    $(wildcard include/config/cpu/exynos4412.h) \
    $(wildcard include/config/mach/u1/na/spr.h) \
    $(wildcard include/config/mach/u1/na/uscc.h) \
  /home/brett/shifted/arch/arm/include/asm/unwind.h \
  arch/arm/kernel/entry-header.S \
    $(wildcard include/config/cpu/v6.h) \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/preempt.h) \
  include/linux/init.h \
    $(wildcard include/config/fast/resume.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/linkage.h \
  /home/brett/shifted/arch/arm/include/asm/linkage.h \
  /home/brett/shifted/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /home/brett/shifted/arch/arm/include/asm/ptrace.h \
  /home/brett/shifted/arch/arm/include/asm/hwcap.h \
  /home/brett/shifted/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
  /home/brett/shifted/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /home/brett/shifted/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  /home/brett/shifted/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/brett/shifted/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  arch/arm/kernel/calls.S \

arch/arm/kernel/entry-common.o: $(deps_arch/arm/kernel/entry-common.o)

$(deps_arch/arm/kernel/entry-common.o):
