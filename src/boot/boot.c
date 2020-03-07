#include <sbi.h>

void boot_c() __attribute__((noreturn));

void boot_c() {
	shutdown();
}