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
	{ 0xf5213f4f, "kmalloc_caches" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x87be76bf, "QP_DequeueReset" },
	{ 0x27ff1a8f, "kernel_sendmsg" },
	{ 0x311b7963, "_raw_spin_unlock" },
	{ 0x79ee379d, "QP_RegisterListener" },
	{ 0xdcf578a, "__alloc_workqueue_key" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xf19e9355, "cpu_online_mask" },
	{ 0x54983252, "QP_DequeueSpace" },
	{ 0xb9f3a2b4, "sock_release" },
	{ 0x8bd94317, "_raw_spin_lock_bh" },
	{ 0xd3f57a2, "_find_next_bit_le" },
	{ 0x86cb7b28, "init_timer_key" },
	{ 0x6b011125, "sock_create_kern" },
	{ 0x7b8e14b0, "QP_DequeueCommit" },
	{ 0x6baae653, "cancel_delayed_work_sync" },
	{ 0x789f40c2, "QP_EnqueueCommit" },
	{ 0xda2e7ffd, "mutex_unlock" },
	{ 0x2ae6f180, "QP_DequeueSegment" },
	{ 0x7d11c268, "jiffies" },
	{ 0x6bcb6e07, "__might_sleep" },
	{ 0x35df4bd9, "mutex_trylock" },
	{ 0x810b3618, "param_ops_string" },
	{ 0x41e92619, "__init_waitqueue_head" },
	{ 0xfe7c4287, "nr_cpu_ids" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x37befc70, "jiffies_to_msecs" },
	{ 0xec05d2d7, "mutex_lock_interruptible" },
	{ 0x4fb326f8, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0x71c90087, "memcmp" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x3b9e691, "destroy_workqueue" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0xfc687332, "flush_workqueue" },
	{ 0xa4b01c6f, "Mvpkm_CommEvRegisterProcessCB" },
	{ 0x74cc1cbe, "unregister_cpu_notifier" },
	{ 0x6cc67b46, "module_put" },
	{ 0xe21b86cd, "kmem_cache_alloc" },
	{ 0x4550ba8a, "register_cpu_notifier" },
	{ 0x5fe6c44c, "Mvpkm_CommEvUnregisterProcessCB" },
	{ 0xb368ec89, "_raw_spin_unlock_bh" },
	{ 0xb00c9cb, "queue_delayed_work_on" },
	{ 0xd3e6f60d, "cpu_possible_mask" },
	{ 0x2008083d, "QP_EnqueueReset" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0xd7d79132, "put_online_cpus" },
	{ 0xe49775f9, "flush_delayed_work" },
	{ 0xc27487dd, "__bug" },
	{ 0x3efb35c9, "get_online_cpus" },
	{ 0xc2161e33, "_raw_spin_lock" },
	{ 0x341dbfa3, "__per_cpu_offset" },
	{ 0x72542c85, "__wake_up" },
	{ 0x669d57c5, "QP_UnregisterListener" },
	{ 0xc35addb3, "QP_RegisterDetachCB" },
	{ 0x9fc7ec7, "QP_EnqueueSegment" },
	{ 0x58dcfc29, "QP_Detach" },
	{ 0x2f103932, "QP_Notify" },
	{ 0x37a0cba, "kfree" },
	{ 0x32f80ea9, "prepare_to_wait" },
	{ 0xf32e4cd0, "QP_EnqueueSpace" },
	{ 0x246b292b, "kernel_bind" },
	{ 0xf83178bd, "finish_wait" },
	{ 0xd2e090d9, "queue_delayed_work" },
	{ 0x22ad05a0, "QP_Attach" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mvpkm";


MODULE_INFO(srcversion, "16EA81F257149D62C659C10");
