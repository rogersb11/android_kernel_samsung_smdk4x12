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
	{ 0x202c73d0, "kobject_put" },
	{ 0xf5213f4f, "kmalloc_caches" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x4e10f1fb, "put_pid" },
	{ 0xdfd4df13, "CommSvc_Zombify" },
	{ 0x27ff1a8f, "kernel_sendmsg" },
	{ 0x311b7963, "_raw_spin_unlock" },
	{ 0x777f747d, "CommSvc_Unlock" },
	{ 0x97255bdf, "strlen" },
	{ 0xdcf578a, "__alloc_workqueue_key" },
	{ 0xf19e9355, "cpu_online_mask" },
	{ 0x3158c53e, "CommSvc_Alloc" },
	{ 0xb9f3a2b4, "sock_release" },
	{ 0xd3f57a2, "_find_next_bit_le" },
	{ 0xe2fae716, "kmemdup" },
	{ 0x86cb7b28, "init_timer_key" },
	{ 0x6b011125, "sock_create_kern" },
	{ 0x6baae653, "cancel_delayed_work_sync" },
	{ 0xda2e7ffd, "mutex_unlock" },
	{ 0xe84dd843, "kobject_del" },
	{ 0x999e8297, "vfree" },
	{ 0x6446d5c3, "kernel_listen" },
	{ 0x7a27321f, "__put_net" },
	{ 0x7d11c268, "jiffies" },
	{ 0x343a1a8, "__list_add" },
	{ 0x6bcb6e07, "__might_sleep" },
	{ 0x35df4bd9, "mutex_trylock" },
	{ 0x19e6b69b, "kernel_sock_ioctl" },
	{ 0x810b3618, "param_ops_string" },
	{ 0xf412c9ca, "CommSvc_Write" },
	{ 0x7b1010cc, "Mvpkm_vmwareUid" },
	{ 0xfe7c4287, "nr_cpu_ids" },
	{ 0x85dd9c15, "kernel_setsockopt" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x5f754e5a, "memset" },
	{ 0xb0d31652, "kernel_connect" },
	{ 0xb86e4ab9, "random32" },
	{ 0x37befc70, "jiffies_to_msecs" },
	{ 0x922260b3, "CommSvc_DispatchUnlock" },
	{ 0xec05d2d7, "mutex_lock_interruptible" },
	{ 0x4fb326f8, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0x71c90087, "memcmp" },
	{ 0x7eed8d81, "kobject_init_and_add" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x4a0aeb80, "mutex_lock" },
	{ 0x3b9e691, "destroy_workqueue" },
	{ 0x72ea47c3, "kernel_sock_shutdown" },
	{ 0x521445b, "list_del" },
	{ 0x7f7ad647, "sk_free" },
	{ 0x38a00d31, "kernel_getsockname" },
	{ 0xa19b0ef5, "kernel_getpeername" },
	{ 0x2469810f, "__rcu_read_unlock" },
	{ 0x2eb3c64f, "CommSvc_Lock" },
	{ 0x24459096, "pid_task" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x10770dad, "init_net" },
	{ 0x2e8a5770, "nf_unregister_hooks" },
	{ 0xfc687332, "flush_workqueue" },
	{ 0xf6b85a83, "CommSvc_RegisterImpl" },
	{ 0x74cc1cbe, "unregister_cpu_notifier" },
	{ 0x6cc67b46, "module_put" },
	{ 0x4a9470d0, "kernel_getsockopt" },
	{ 0xe21b86cd, "kmem_cache_alloc" },
	{ 0x4550ba8a, "register_cpu_notifier" },
	{ 0xb00c9cb, "queue_delayed_work_on" },
	{ 0xd3e6f60d, "cpu_possible_mask" },
	{ 0xa6c5fbea, "CommSvc_GetState" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xd7d79132, "put_online_cpus" },
	{ 0xe49775f9, "flush_delayed_work" },
	{ 0xc27487dd, "__bug" },
	{ 0x3efb35c9, "get_online_cpus" },
	{ 0xc2161e33, "_raw_spin_lock" },
	{ 0x341dbfa3, "__per_cpu_offset" },
	{ 0x1cd987a4, "kernel_recvmsg" },
	{ 0x8da329ab, "kernel_accept" },
	{ 0xe8af60b, "Mvpkm_vmwareGid" },
	{ 0x28b8bfa8, "find_get_pid" },
	{ 0x26477c07, "__vmalloc" },
	{ 0x37a0cba, "kfree" },
	{ 0x5b38a5ba, "nf_register_hooks" },
	{ 0xfd12932f, "CommSvc_ScheduleAIOWork" },
	{ 0x246b292b, "kernel_bind" },
	{ 0x38e8378d, "pgprot_kernel" },
	{ 0x701d0ebd, "snprintf" },
	{ 0x8d522714, "__rcu_read_lock" },
	{ 0x58fa30, "CommSvc_UnregisterImpl" },
	{ 0x6e04b501, "CommSvc_GetTranspInitArgs" },
	{ 0xd2e090d9, "queue_delayed_work" },
	{ 0x8469b626, "CommSvc_WriteVec" },
	{ 0xe6b5d61, "Mvpkm_FindVMNamedKSet" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=commkm,mvpkm";


MODULE_INFO(srcversion, "3B641FBC991A10F5F00450F");
