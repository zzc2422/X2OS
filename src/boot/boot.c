#include <sbi.h>

static void _print_and_shutdown(const u8 str_a[]) __attribute__((noreturn));

static void _print_and_shutdown(const u8 str_a[]) {
	print_str(str_a);
	shutdown();
}

void boot_c() __attribute__((noreturn));

void boot_c() {
	_print_and_shutdown("Exit!\n");
}