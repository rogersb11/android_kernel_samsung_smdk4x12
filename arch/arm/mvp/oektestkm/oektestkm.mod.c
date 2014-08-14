#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbb31cd35, "module_layout" },
	{ 0x42771432, "remove_proc_entry" },
	{ 0xda2e7ffd, "mutex_unlock" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x7d11c268, "jiffies" },
	{ 0x511868b3, "input_event" },
	{ 0xf7b574c2, "del_timer_sync" },
	{ 0x37a940bb, "proc_mkdir" },
	{ 0x27e1a049, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0x4a0aeb80, "mutex_lock" },
	{ 0x983d7206, "boot_tvec_bases" },
	{ 0x77edf722, "schedule_delayed_work" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xedcb17e0, "input_register_device" },
	{ 0x440b93fc, "input_free_device" },
	{ 0x69a6cbb2, "create_proc_entry" },
	{ 0x300710ab, "input_unregister_device" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x4508b946, "input_allocate_device" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

