#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x7b3685fa, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe2bf6eda, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x8c645f3a, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0x9ed554b3, __VMLINUX_SYMBOL_STR(unregister_keyboard_notifier) },
	{ 0x96554810, __VMLINUX_SYMBOL_STR(register_keyboard_notifier) },
	{ 0xef5a3551, __VMLINUX_SYMBOL_STR(debugfs_remove_recursive) },
	{ 0xbed6ee63, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x40bcb387, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0x327c065d, __VMLINUX_SYMBOL_STR(sock_create) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x44b1d426, __VMLINUX_SYMBOL_STR(__dynamic_pr_debug) },
	{ 0xb6ed1e53, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xd0d8621b, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x35f6f57e, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0x139b504, __VMLINUX_SYMBOL_STR(cpu_current_top_of_stack) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x528c709d, __VMLINUX_SYMBOL_STR(simple_read_from_buffer) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "92F4BA5FE4F546649218DDE");
